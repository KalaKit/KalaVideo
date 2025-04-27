//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#pragma once

#include <string>
#include <unordered_map>

namespace Video
{
	using std::string;
	using std::unordered_map;

	struct VideoFile
	{
		bool canLoop = false;
		void* formatCtx = nullptr; // AVFormatContext*
		void* codecCtx = nullptr;  // AVCodecContext*
		int videoStreamIndex = -1;
		float framerate = 60.0f;
	};

	class VideoImport
	{
	public:
		static inline string failReason;
		static inline unordered_map<string, VideoFile> importedVideos;

		static bool ImportVideo(const string& filePath);
		static bool OpenVideoFile(
			const char* filePath,
			void*& outFormatCtx, 
			void*& outCodecCtx,
			int& outVideoStreamIndex);

		static void RemoveImportedVideo(const string& filePath);

		static void Shutdown();
	};
}