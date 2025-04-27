//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <iostream>
#include <unordered_map>

//external
extern "C" 
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
}
#include "opengl_loader.hpp"

//kalavideo
#include "video/video_player.hpp"
#include "video/video_import.hpp"
#include "ui/ui_video.hpp"
#include "graphics/quad.hpp"

using std::cout;
using std::unordered_map;

using Video::VideoFile;
using KalaKit::OpenGLLoader;
using Graphics::Quad;
using UI::UI_Video;

namespace Video
{
	enum class VideoState
	{
		VIDEO_STOPPED,
		VIDEO_PLAYING,
		VIDEO_PAUSED,
		VIDEO_FINISHED
	};

	static unordered_map<string, AVFrame*> rgbFrames;
	static unordered_map<string, SwsContext*> swsContexts;
	static unordered_map<string, AVPacket*> packets;
	static unordered_map<string, uint8_t*> buffers;
	static unordered_map<string, int64_t> lastDecodedPTS;
	static unordered_map<string, VideoState> videoStates;

	void VideoPlayer::RenderVideoFrame(const string& video, unsigned int textureID)
	{
		auto it = VideoImport::importedVideos.find(video);
		if (it == VideoImport::importedVideos.end())
		{
			return;
		}

		auto stateIt = videoStates.find(video);
		if (stateIt == videoStates.end())
		{
			videoStates[video] = VideoState::VIDEO_PLAYING;
		}
		else if (stateIt->second != VideoState::VIDEO_PLAYING)
		{
			return;
		}

		VideoFile& vf = it->second;
		AVFormatContext* formatCtx = static_cast<AVFormatContext*>(vf.formatCtx);
		AVCodecContext* codecCtx = static_cast<AVCodecContext*>(vf.codecCtx);

		if (!formatCtx || !codecCtx) return;

		int width = codecCtx->width;
		int height = codecCtx->height;

		//initialize per-video stuff
		if (rgbFrames.find(video) == rgbFrames.end())
		{
			AVFrame* rgbFrame = av_frame_alloc();
			int numBytes = av_image_get_buffer_size(
				AV_PIX_FMT_RGB24, 
				width, 
				height, 
				1
			);
			uint8_t* buffer = (uint8_t*)av_malloc(numBytes);
			av_image_fill_arrays(
				rgbFrame->data,
				rgbFrame->linesize,
				buffer,
				AV_PIX_FMT_RGB24,
				width,
				height,
				1
			);

			SwsContext* swsCtx = sws_getContext(
				width,
				height,
				codecCtx->pix_fmt,
				width,
				height,
				AV_PIX_FMT_RGB24,
				SWS_BILINEAR,
				nullptr,
				nullptr,
				nullptr
			);
			AVPacket* packet = av_packet_alloc();

			rgbFrames[video] = rgbFrame;
			swsContexts[video] = swsCtx;
			packets[video] = packet;
			buffers[video] = buffer;
		}

		AVFrame* rgbFrame = rgbFrames[video];
		SwsContext* swsCtx = swsContexts[video];
		AVPacket* packet = packets[video];

		//read frames
		bool frameDecoded = false;
		while (av_read_frame(formatCtx, packet) >= 0)
		{
			if (packet->stream_index == vf.videoStreamIndex)
			{
				if (avcodec_send_packet(codecCtx, packet) == 0)
				{
					AVFrame* frame = av_frame_alloc();
					if (avcodec_receive_frame(codecCtx, frame) == 0)
					{
						//convert YUV -> RGB
						sws_scale(
							swsCtx,
							frame->data,
							frame->linesize,
							0,
							height,
							rgbFrame->data,
							rgbFrame->linesize
						);

						OpenGLLoader::glBindTexture(GL_TEXTURE_2D, textureID);

						if (currentWidth != UI_Video::framebufferWidth
							|| currentHeight != UI_Video::framebufferHeight)
						{
							//reallocate texture if size changes
							OpenGLLoader::glTexImage2D(
								GL_TEXTURE_2D,
								0,
								GL_RGB,
								width,
								height,
								0,
								GL_RGB,
								GL_UNSIGNED_BYTE,
								nullptr
							);

							currentWidth = UI_Video::framebufferWidth;
							currentHeight = UI_Video::framebufferHeight;
						}

						//upload to opengl
						OpenGLLoader::glTexSubImage2D(
							GL_TEXTURE_2D,
							0,
							0,
							0,
							width,
							height,
							GL_RGB,
							GL_UNSIGNED_BYTE,
							rgbFrame->data[0]
						);

						lastDecodedPTS[video] = frame->pts;

						frameDecoded = true;
						av_frame_free(&frame);
						av_packet_unref(packet);
						break;
					}
					av_frame_free(&frame);
				}
			}
			av_packet_unref(packet);
		}

		if (!frameDecoded) VideoEndCheck(video);
	}

	void VideoPlayer::Play(const string& video)
	{
		videoStates[video] = VideoState::VIDEO_PLAYING;
	}
	void VideoPlayer::Pause(const string& video)
	{
		videoStates[video] = VideoState::VIDEO_PAUSED;

		OpenGLLoader::glBindTexture(GL_TEXTURE_2D, Quad::textureID);
		OpenGLLoader::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		OpenGLLoader::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 3);
		OpenGLLoader::glGenerateMipmap(GL_TEXTURE_2D);
	}
	void VideoPlayer::Stop(const string& video)
	{
		videoStates[video] = VideoState::VIDEO_STOPPED;

		auto it = VideoImport::importedVideos.find(video);
		if (it != VideoImport::importedVideos.end())
		{
			VideoFile& vf = it->second;
			AVFormatContext* formatCtx = static_cast<AVFormatContext*>(vf.formatCtx);
			if (formatCtx)
			{
				av_seek_frame(formatCtx, vf.videoStreamIndex, 0, AVSEEK_FLAG_BACKWARD);

				OpenGLLoader::glBindTexture(GL_TEXTURE_2D, Quad::textureID);
				OpenGLLoader::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
				OpenGLLoader::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 3);
				OpenGLLoader::glGenerateMipmap(GL_TEXTURE_2D);
			}
		}
	}
	void VideoPlayer::Restart(const string& video)
	{
		Stop(video);
		Play(video);
	}

	void VideoPlayer::SetLoopState(const string& video, bool state)
	{
		auto it = VideoImport::importedVideos.find(video);
		if (it != VideoImport::importedVideos.end())
		{
			it->second.canLoop = state;
		}
	}
	void VideoPlayer::SetPlaybackPosition(const string& video, double seconds)
	{
		auto it = VideoImport::importedVideos.find(video);
		if (it != VideoImport::importedVideos.end())
		{
			VideoFile& vf = it->second;
			AVFormatContext* formatCtx = static_cast<AVFormatContext*>(vf.formatCtx);
			if (formatCtx)
			{
				int64_t targetTimestamp = static_cast<int64_t>(seconds * AV_TIME_BASE);
				av_seek_frame(
					formatCtx, 
					vf.videoStreamIndex, 
					targetTimestamp, 
					AVSEEK_FLAG_BACKWARD);

				AVCodecContext* codecCtx = static_cast<AVCodecContext*>(vf.codecCtx);
				if (codecCtx)
				{
					avcodec_flush_buffers(codecCtx);
				}

				videoStates[video] = VideoState::VIDEO_PLAYING;
			}
		}
	}
	void VideoPlayer::SetVideoCustomFramerate(const string& video, float framerate)
	{
		auto it = VideoImport::importedVideos.find(video);
		if (it != VideoImport::importedVideos.end())
		{
			VideoFile& vf = it->second;
			vf.framerate = framerate;
		}
	}
	void VideoPlayer::SetVideoDefaultFramerate(const string& video)
	{
		auto it = VideoImport::importedVideos.find(video);
		if (it != VideoImport::importedVideos.end())
		{
			VideoFile& vf = it->second;
			AVFormatContext* formatCtx = static_cast<AVFormatContext*>(vf.formatCtx);
			if (formatCtx)
			{
				AVStream* stream = formatCtx->streams[vf.videoStreamIndex];
				if (stream)
				{
					AVRational fr = stream->avg_frame_rate;
					if (fr.num != 0
						&& fr.den != 0)
					{
						vf.framerate =
							static_cast<float>(fr.num)
							/ static_cast<float>(fr.den);
					}
					//fallback if avg_frame_rate is invalid
					else vf.framerate = 60.0f;
				}
			}
		}
	}

	bool VideoPlayer::IsPlaying(const string& video)
	{
		auto it = videoStates.find(video);
		if (it != videoStates.end())
		{
			return it->second == VideoState::VIDEO_PLAYING;
		}
		return false;
	}
	bool VideoPlayer::IsPaused(const string& video)
	{
		auto it = videoStates.find(video);
		if (it != videoStates.end())
		{
			return it->second == VideoState::VIDEO_PAUSED;
		}
		return false;
	}
	bool VideoPlayer::IsFinished(const string& video)
	{
		auto it = videoStates.find(video);
		if (it != videoStates.end())
		{
			return it->second == VideoState::VIDEO_FINISHED;
		}
		return false;
	}
	double VideoPlayer::GetPlaybackPosition(const string& video)
	{
		auto it = lastDecodedPTS.find(video);
		if (it != lastDecodedPTS.end())
		{
			auto videoIt = VideoImport::importedVideos.find(video);
			if (videoIt != VideoImport::importedVideos.end())
			{
				VideoFile& vf = videoIt->second;
				AVFormatContext* formatCtx = static_cast<AVFormatContext*>(vf.formatCtx);
				if (formatCtx)
				{
					AVStream* stream = formatCtx->streams[vf.videoStreamIndex];
					return static_cast<double>(it->second) * stream->time_base.num / stream->time_base.den;
				}
			}
		}
		return 0.0;

	}
	double VideoPlayer::GetVideoDuration(const string& video)
	{
		auto it = VideoImport::importedVideos.find(video);
		if (it != VideoImport::importedVideos.end())
		{
			VideoFile& vf = it->second;
			AVFormatContext* formatCtx = static_cast<AVFormatContext*>(vf.formatCtx);
			if (formatCtx)
			{
				if (formatCtx->duration != AV_NOPTS_VALUE)
				{
					return static_cast<double>(formatCtx->duration) / AV_TIME_BASE;
				}
			}
		}
		return 0.0;
	}
	float VideoPlayer::GetVideoFramerate(const string& video)
	{
		auto it = VideoImport::importedVideos.find(video);
		if (it != VideoImport::importedVideos.end())
		{
			VideoFile& vf = it->second;
			return vf.framerate;
		}

		return 0.0f;
	}

	void VideoPlayer::VideoEndCheck(const string& video)
	{
		auto it = VideoImport::importedVideos.find(video);
		if (it != VideoImport::importedVideos.end()
			&& it->second.canLoop)
		{
			Restart(video);
		}
		else
		{
			videoStates[video] = VideoState::VIDEO_FINISHED;
		}
	}
}