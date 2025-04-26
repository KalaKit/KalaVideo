@echo off

set "PROJECT_NAME=KalaVideo"

echo Starting to copy %PROJECT_NAME%...
echo.

set "PROJECT_ROOT=%~dp0"

set "CRASH_RELEASE_DLL_ORIGIN=%PROJECT_ROOT%\KalaCrashHandler\release\KalaCrashHandler.dll"
set "CRASH_DEBUG_DLL_ORIGIN=%PROJECT_ROOT%\KalaCrashHandler\debug\KalaCrashHandlerD.dll"

set "WINDOW_RELEASE_DLL_ORIGIN=%PROJECT_ROOT%\KalaWindow\release\KalaWindow.dll"
set "WINDOW_DEBUG_DLL_ORIGIN=%PROJECT_ROOT%\KalaWindow\debug\KalaWindowD.dll"

set "FFMPEG_RELEASE_DLL_ORIGIN_1=%PROJECT_ROOT%\ffmpeg\release\avcodec-61.dll"
set "FFMPEG_RELEASE_DLL_ORIGIN_2=%PROJECT_ROOT%\ffmpeg\release\avdevice-61.dll"
set "FFMPEG_RELEASE_DLL_ORIGIN_3=%PROJECT_ROOT%\ffmpeg\release\avfilter-10.dll"
set "FFMPEG_RELEASE_DLL_ORIGIN_4=%PROJECT_ROOT%\ffmpeg\release\avformat-61.dll"
set "FFMPEG_RELEASE_DLL_ORIGIN_5=%PROJECT_ROOT%\ffmpeg\release\avutil-59.dll"
set "FFMPEG_RELEASE_DLL_ORIGIN_6=%PROJECT_ROOT%\ffmpeg\release\postproc-58.dll"
set "FFMPEG_RELEASE_DLL_ORIGIN_7=%PROJECT_ROOT%\ffmpeg\release\swresample-5.dll"
set "FFMPEG_RELEASE_DLL_ORIGIN_8=%PROJECT_ROOT%\ffmpeg\release\swscale-8.dll"
set "FFMPEG_DEBUG_DLL_ORIGIN_1=%PROJECT_ROOT%\ffmpeg\debug\avcodec-61.dll"
set "FFMPEG_DEBUG_DLL_ORIGIN_2=%PROJECT_ROOT%\ffmpeg\debug\avdevice-61.dll"
set "FFMPEG_DEBUG_DLL_ORIGIN_3=%PROJECT_ROOT%\ffmpeg\debug\avfilter-10.dll"
set "FFMPEG_DEBUG_DLL_ORIGIN_4=%PROJECT_ROOT%\ffmpeg\debug\avformat-61.dll"
set "FFMPEG_DEBUG_DLL_ORIGIN_5=%PROJECT_ROOT%\ffmpeg\debug\avutil-59.dll"
set "FFMPEG_DEBUG_DLL_ORIGIN_6=%PROJECT_ROOT%\ffmpeg\debug\postproc-58.dll"
set "FFMPEG_DEBUG_DLL_ORIGIN_7=%PROJECT_ROOT%\ffmpeg\debug\swresample-5.dll"
set "FFMPEG_DEBUG_DLL_ORIGIN_8=%PROJECT_ROOT%\ffmpeg\debug\swscale-8.dll"

set "TARGET_ROOT=%PROJECT_ROOT%..\files\external dlls"

if not exist "%TARGET_ROOT%" (
	echo Failed to find target root from '%TARGET_ROOT%'!
	pause
	exit /b 1
)

if not exist "%TARGET_ROOT%\release" mkdir "%TARGET_ROOT%\release"
if not exist "%TARGET_ROOT%\debug" mkdir "%TARGET_ROOT%\debug"

set "CRASH_RELEASE_DLL_TARGET=%TARGET_ROOT%\release\KalaCrashHandler.dll"
set "CRASH_DEBUG_DLL_TARGET=%TARGET_ROOT%\debug\KalaCrashHandlerD.dll"

set "WINDOW_RELEASE_DLL_TARGET=%TARGET_ROOT%\release\KalaWindow.dll"
set "WINDOW_DEBUG_DLL_TARGET=%TARGET_ROOT%\debug\KalaWindowD.dll"

set "FFMPEG_RELEASE_DLL_TARGET_1=%TARGET_ROOT%\release\avcodec-61.dll"
set "FFMPEG_RELEASE_DLL_TARGET_2=%TARGET_ROOT%\release\avdevice-61.dll"
set "FFMPEG_RELEASE_DLL_TARGET_3=%TARGET_ROOT%\release\avfilter-10.dll"
set "FFMPEG_RELEASE_DLL_TARGET_4=%TARGET_ROOT%\release\avformat-61.dll"
set "FFMPEG_RELEASE_DLL_TARGET_5=%TARGET_ROOT%\release\avutil-59.dll"
set "FFMPEG_RELEASE_DLL_TARGET_6=%TARGET_ROOT%\release\postproc-58.dll"
set "FFMPEG_RELEASE_DLL_TARGET_7=%TARGET_ROOT%\release\swresample-5.dll"
set "FFMPEG_RELEASE_DLL_TARGET_8=%TARGET_ROOT%\release\swscale-8.dll"
set "FFMPEG_DEBUG_DLL_TARGET_1=%TARGET_ROOT%\debug\avcodec-61.dll"
set "FFMPEG_DEBUG_DLL_TARGET_2=%TARGET_ROOT%\debug\avdevice-61.dll"
set "FFMPEG_DEBUG_DLL_TARGET_3=%TARGET_ROOT%\debug\avfilter-10.dll"
set "FFMPEG_DEBUG_DLL_TARGET_4=%TARGET_ROOT%\debug\avformat-61.dll"
set "FFMPEG_DEBUG_DLL_TARGET_5=%TARGET_ROOT%\debug\avutil-59.dll"
set "FFMPEG_DEBUG_DLL_TARGET_6=%TARGET_ROOT%\debug\postproc-58.dll"
set "FFMPEG_DEBUG_DLL_TARGET_7=%TARGET_ROOT%\debug\swresample-5.dll"
set "FFMPEG_DEBUG_DLL_TARGET_8=%TARGET_ROOT%\debug\swscale-8.dll"

:: Copy dll to target path
copy /Y "%CRASH_RELEASE_DLL_ORIGIN%" "%CRASH_RELEASE_DLL_TARGET%"
copy /Y "%CRASH_DEBUG_DLL_ORIGIN%" "%CRASH_DEBUG_DLL_TARGET%"

copy /Y "%WINDOW_RELEASE_DLL_ORIGIN%" "%WINDOW_RELEASE_DLL_TARGET%"
copy /Y "%WINDOW_DEBUG_DLL_ORIGIN%" "%WINDOW_DEBUG_DLL_TARGET%"

copy /Y "%FFMPEG_RELEASE_DLL_ORIGIN_1%" "%FFMPEG_RELEASE_DLL_TARGET_1%"
copy /Y "%FFMPEG_RELEASE_DLL_ORIGIN_2%" "%FFMPEG_RELEASE_DLL_TARGET_2%"
copy /Y "%FFMPEG_RELEASE_DLL_ORIGIN_3%" "%FFMPEG_RELEASE_DLL_TARGET_3%"
copy /Y "%FFMPEG_RELEASE_DLL_ORIGIN_4%" "%FFMPEG_RELEASE_DLL_TARGET_4%"
copy /Y "%FFMPEG_RELEASE_DLL_ORIGIN_5%" "%FFMPEG_RELEASE_DLL_TARGET_5%"
copy /Y "%FFMPEG_RELEASE_DLL_ORIGIN_6%" "%FFMPEG_RELEASE_DLL_TARGET_6%"
copy /Y "%FFMPEG_RELEASE_DLL_ORIGIN_7%" "%FFMPEG_RELEASE_DLL_TARGET_7%"
copy /Y "%FFMPEG_RELEASE_DLL_ORIGIN_8%" "%FFMPEG_RELEASE_DLL_TARGET_8%"
copy /Y "%FFMPEG_DEBUG_DLL_ORIGIN_1%" "%FFMPEG_DEBUG_DLL_TARGET_1%"
copy /Y "%FFMPEG_DEBUG_DLL_ORIGIN_2%" "%FFMPEG_DEBUG_DLL_TARGET_2%"
copy /Y "%FFMPEG_DEBUG_DLL_ORIGIN_3%" "%FFMPEG_DEBUG_DLL_TARGET_3%"
copy /Y "%FFMPEG_DEBUG_DLL_ORIGIN_4%" "%FFMPEG_DEBUG_DLL_TARGET_4%"
copy /Y "%FFMPEG_DEBUG_DLL_ORIGIN_5%" "%FFMPEG_DEBUG_DLL_TARGET_5%"
copy /Y "%FFMPEG_DEBUG_DLL_ORIGIN_6%" "%FFMPEG_DEBUG_DLL_TARGET_6%"
copy /Y "%FFMPEG_DEBUG_DLL_ORIGIN_7%" "%FFMPEG_DEBUG_DLL_TARGET_7%"
copy /Y "%FFMPEG_DEBUG_DLL_ORIGIN_8%" "%FFMPEG_DEBUG_DLL_TARGET_8%"

echo.
echo Finished copying %PROJECT_NAME% DLLs!

pause
exit /b 0
