//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#pragma once

#include <string>

namespace Video
{
	using std::string;

	class VideoPlayer
	{
	public:
		static void RenderVideoFrame(const string& video, unsigned int textureID);
	
		static void Play(const string& video);
		static void Pause(const string& video);
		static void Stop(const string& video);
		static void Restart(const string& video);

		static void SetLoopState(const string& video, bool state);
		static void SetPlaybackPosition(const string& video, double seconds);

		static bool IsPlaying(const string& video);
		static bool IsPaused(const string& video);
		static bool IsFinished(const string& video);
		static double GetPlaybackPosition(const string& video);
		static double GetVideoDuration(const string& video);
	private:
		static void VideoEndCheck(const string& video);
	};
}