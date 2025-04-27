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
		/// <summary>
		/// The main video render loop.
		/// </summary>
		/// <param name="video"></param>
		/// <param name="textureID"></param>
		static void RenderVideoFrame(const string& video, unsigned int textureID);
	
		/// <summary>
		/// Start playing current video from the beginning.
		/// </summary>
		/// <param name="video"></param>
		static void Play(const string& video);
		/// <summary>
		/// Pause currently playing video.
		/// </summary>
		static void Pause(const string& video);
		/// <summary>
		/// Completely stop currently playing video.
		/// </summary>
		static void Stop(const string& video);
		/// <summary>
		/// Stop and start current video from the beginning.
		/// </summary>
		static void Restart(const string& video);

		/// <summary>
		/// If set to true, then the video will restart after it finishes.
		/// </summary>
		static void SetLoopState(const string& video, bool state);
		/// <summary>
		/// Set where video should continue playing from.
		/// </summary>
		static void SetPlaybackPosition(const string& video, double seconds);
		/// <summary>
		/// Force specific video playback speed.
		/// </summary>
		static void SetVideoCustomFramerate(const string& video, float framerate);
		/// <summary>
		/// Set video average playback speed (based off of average between frames).
		/// </summary>
		static void SetVideoDefaultFramerate(const string& video);

		/// <summary>
		/// Returns true if video is currently playing.
		/// </summary>
		static bool IsPlaying(const string& video);
		/// <summary>
		/// Returns true if video is currently paused.
		/// </summary>
		static bool IsPaused(const string& video);
		/// <summary>
		/// Returns true if video has finished playing.
		/// </summary>
		static bool IsFinished(const string& video);
		/// <summary>
		/// Returns current position of video.
		/// </summary>
		static double GetPlaybackPosition(const string& video);
		/// <summary>
		/// Returns total video length.
		/// </summary>
		static double GetVideoDuration(const string& video);
		/// <summary>
		/// Returns video current framerate.
		/// </summary>
		static float GetVideoFramerate(const string& video);
	private:
		static inline unsigned int currentWidth = 0;
		static inline unsigned int currentHeight = 0;

		static void VideoEndCheck(const string& video);
	};
}