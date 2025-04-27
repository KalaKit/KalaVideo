# KalaVideo

[![License](https://img.shields.io/badge/license-Zlib-blue)](LICENSE.md)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-brightgreen)
![Development Stage](https://img.shields.io/badge/development-Alpha-yellow)

![Logo](logo.png)

KalaVideo is a lightweight C++20 video editor and player for Windows and Linux, designed primarily for trimming videos. Additional editing features may be added in future updates. KalaVideo includes [KalaCrashHandler](https://github.com/KalaKit/KalaCrashHandler) for handy crash reports and uses [KalaWindow](https://github.com/KalaKit/KalaWindow) as its backend for window, input and OpenGL mechanics.

External libraries included in this library:

- [ImGui](https://github.com/ocornut/imgui) – UI for KalaVideo  
- [FFmpeg](https://ffmpeg.org) – video and audio edit and export  
- [Stb_image](https://github.com/nothings/stb) – image import
- [miniaudio](https://github.com/mackron/miniaudio) – audio playback

---

## Video Codec & Format Support

KalaVideo uses FFmpeg under the hood for decoding, editing, and exporting media. The following codecs and containers are supported out of the box:

- **H.264 (`libx264`)**  
  Universal, fast, and hardware-friendly. Common in `.mp4`, `.mkv`, `.mov`, `.ts`.

- **H.265 / HEVC (`libx265`)**  
  High-efficiency video (~30–50% smaller than H.264). Common in `.mp4`, `.mkv`, `.ts`.

- **AV1 (`libaom`)**  
  Royalty-free, excellent compression, used by YouTube. Found in `.webm`, `.mkv`.

- **Supported Video Containers:**  
  `.mp4`, `.mkv`, `.mov`, `.avi`, `.flv`, `.ts`, `.webm`

---

## Audio Codec & Format Support

- **AAC (`libfdk-aac`)**  
  High-quality audio for `.mp4`, `.mkv`, `.mov`, `.ts`.

- **MP3 (`libmp3lame`)**  
  Widely supported format used in `.mp3`, `.mp4`, `.mkv`.

- **Supported Audio Containers:**  
  `.mp3`, `.aac`, `.wav`, `.ogg`, `.flac`, `.webm`, `.mkv`, `.mp4`

---

## Prerequisites (when compiling from source code)

### Windows

> Read Windows_prerequisites.txt and use Windows_prerequisites.zip

### Linux

> Read Linux_prerequisites.txt
