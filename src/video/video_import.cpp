//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <iostream>
#include <filesystem>

//external
extern "C"
{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
}

//kalavideo
#include "video/video_import.hpp"

using std::filesystem::path;
using std::cout;

namespace Video
{
	bool VideoImport::ImportVideo(const string& filePath)
	{
		void* formatCtx = nullptr;
		void* codecCtx = nullptr;
		int videoStreamIndex = -1;

		if (!OpenVideoFile(
			filePath.c_str(),
			formatCtx,
			codecCtx,
			videoStreamIndex))
		{
			return false;
		}

		VideoFile videoFile;
		videoFile.formatCtx = formatCtx;
		videoFile.codecCtx = codecCtx;
		videoFile.videoStreamIndex = videoStreamIndex;

		importedVideos[filePath] = videoFile;

		return true;
	}

	bool VideoImport::OpenVideoFile(
		const char* filePath,
		void*& outFormatCtx,
		void*& outCodecCtx,
		int& outVideoStreamIndex)
	{
		AVFormatContext* formatCtx = nullptr;
		AVCodecContext* codecCtx = nullptr;
		int videoStreamIndex = -1;
		string filePathString = filePath;
		string fileName = path(filePathString).filename().string();

		if (avformat_open_input(&formatCtx, filePath, nullptr, nullptr) != 0)
		{
			failReason = "Failed to open video file: " + fileName;
			return false;
		}

		if (avformat_find_stream_info(formatCtx, nullptr) < 0)
		{
			failReason = "Failed to find stream info for video file: " + fileName;
			avformat_close_input(&formatCtx);
			return false;
		}

		for (unsigned int i = 0; i < formatCtx->nb_streams; ++i)
		{
			if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
			{
				videoStreamIndex = static_cast<int>(i);
				break;
			}
		}
		if (videoStreamIndex == -1)
		{
			failReason = "Failed to find a video stream for video file: " + fileName;
			avformat_close_input(&formatCtx);
			return false;
		}

		AVCodecParameters* codecPar = formatCtx->streams[videoStreamIndex]->codecpar;
		const AVCodec* codec = avcodec_find_decoder(codecPar->codec_id);
		if (!codec)
		{
			failReason = "Failed to find decoder for video file: " + fileName;
			avformat_close_input(&formatCtx);
			return false;
		}

		codecCtx = avcodec_alloc_context3(codec);
		if (!codecCtx)
		{
			failReason = "Failed to allocate codec context for video file: " + fileName;
			avformat_close_input(&formatCtx);
			return false;
		}

		if (avcodec_parameters_to_context(codecCtx, codecPar) < 0)
		{
			failReason = "Failed to copy coded parameters for video file: " + fileName;
			avcodec_free_context(&codecCtx);
			avformat_close_input(&formatCtx);
			return false;
		}

		if (avcodec_open2(codecCtx, codec, nullptr) < 0)
		{
			failReason = "Failed to open codec for video file: " + fileName;
			avcodec_free_context(&codecCtx);
			avformat_close_input(&formatCtx);
			return false;
		}

		outFormatCtx = formatCtx;
		outCodecCtx = codecCtx;
		outVideoStreamIndex = videoStreamIndex;

		cout << "Successfully imported video file '" << fileName << "'!\n";
		failReason = "";

		return true;
	}

	void VideoImport::RemoveImportedVideo(const string& filePath)
	{
		auto it = importedVideos.find(filePath);
		if (it != importedVideos.end())
		{
			VideoFile& videoFile = it->second;

			//free codec context
			if (videoFile.codecCtx)
			{
				avcodec_free_context(reinterpret_cast<AVCodecContext**>(&videoFile.codecCtx));
				videoFile.codecCtx = nullptr;
			}

			//free format context
			if (videoFile.formatCtx)
			{
				avformat_close_input(reinterpret_cast<AVFormatContext**>(&videoFile.formatCtx));
				videoFile.formatCtx = nullptr;
			}

			videoFile.videoStreamIndex = -1;

			importedVideos.erase(it);

			cout << "Removed imported video: " << filePath << "\n";
		}
	}

	void VideoImport::Shutdown()
	{
		while (!importedVideos.empty())
		{
			string filePath = importedVideos.begin()->first;
			RemoveImportedVideo(filePath);
		}

		cout << "Successfully shut down Ffmpeg!\n";
	}
}