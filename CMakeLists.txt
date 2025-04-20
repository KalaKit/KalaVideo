cmake_minimum_required(VERSION 3.30.3)

# Specify the compiler for Linux builds
if (UNIX)
    set(CMAKE_C_COMPILER "/usr/bin/gcc")
    set(CMAKE_CXX_COMPILER "/usr/bin/g++")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_MAJOR_VERSION 1)
set(PROJECT_MINOR_VERSION 0)
set(PROJECT_PATCH_VERSION 0)
set(PROJECT_VERSION "${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}.${PROJECT_PATCH_VERSION}")

project("KalaVideo" VERSION ${PROJECT_VERSION})

add_executable(KalaVideo "")

# Set OS global type
if (WIN32)
    set(KALAKIT_WINDOWS TRUE)
    target_compile_definitions(KalaVideo PRIVATE KALAKIT_WINDOWS)
elseif(UNIX)
    find_package(X11 QUIET)
    find_package(OpenGL REQUIRED)

	message(STATUS "[KALAKIT] X11_FOUND = ${X11_FOUND}")
	message(STATUS "[KALAKIT] OpenGL_FOUND: ${OpenGL_FOUND}")

    if (X11_FOUND)
		set(KALAKIT_X11 TRUE)
		message(STATUS "[KALAKIT] Using X11 backend")
		target_compile_definitions(KalaVideo PRIVATE KALAKIT_X11)
	else()
		message(FATAL_ERROR "[KALAKIT] No valid backend found! Must support X11.")
	endif()
else()
	message(FATAL_ERROR "[KALAKIT] Unsupported platform version! Must be WIN32 or UNIX!")
endif()

# Set build global type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(KALAKIT_DEBUG TRUE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	set(KALAKIT_RELEASE TRUE)
else()
	message(FATAL_ERROR "Unknown CMAKE_BUILD_TYPE: '${CMAKE_BUILD_TYPE}'! Must be Debug, Release, or RelWithDebInfo.")
endif()

if (MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
    else()
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    endif()
endif()

# Specify resource file for Windows
if (KALAKIT_WINDOWS)
    set(RESOURCE_FILE "${CMAKE_SOURCE_DIR}/files/icon.rc")
endif()

# Project files
set(CORE_DIR "${CMAKE_SOURCE_DIR}/include/core")
set(GRAPHICS_DIR "${CMAKE_SOURCE_DIR}/include/graphics")
set(UI_DIR "${CMAKE_SOURCE_DIR}/include/ui")

# External files
set(EXT_WINDOW_DIR "${CMAKE_SOURCE_DIR}/_external_shared/KalaWindow")
set(EXT_CRASH_DIR "${CMAKE_SOURCE_DIR}/_external_shared/KalaCrashHandler")
set(EXT_IMGUI_DIR "${CMAKE_SOURCE_DIR}/_external_shared/ImGui")

# Add KalaWindow
if (KALAKIT_WINDOWS)
	if(KALAKIT_RELEASE)
		set(WINDOW_LIBRARY_PATH "${EXT_WINDOW_DIR}/release/KalaWindow.lib")
	else()
		set(WINDOW_LIBRARY_PATH "${EXT_WINDOW_DIR}/debug/KalaWindowD.lib")
	endif()
else()
	if(KALAKIT_RELEASE)
		set(WINDOW_LIBRARY_PATH "${EXT_WINDOW_DIR}/release/libKalaWindow.so")
	else()
		set(WINDOW_LIBRARY_PATH "${EXT_WINDOW_DIR}/debug/libKalaWindowD.so")
	endif()
endif()

# Add KalaCrashHandler
if (KALAKIT_WINDOWS)
	if(KALAKIT_RELEASE)
		set(CRASH_LIBRARY_PATH "${EXT_CRASH_DIR}/release/KalaCrashHandler.lib")
	else()
		set(CRASH_LIBRARY_PATH "${EXT_CRASH_DIR}/debug/KalaCrashHandlerD.lib")
	endif()
else()
	if(KALAKIT_RELEASE)
		set(CRASH_LIBRARY_PATH "${EXT_CRASH_DIR}/release/libKalaCrashHandler.so")
	else()
		set(CRASH_LIBRARY_PATH "${EXT_CRASH_DIR}/debug/libKalaCrashHandlerD.so")
	endif()
endif()

# Add your source files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
	${CMAKE_SOURCE_DIR}/src/*.cpp
	${CMAKE_SOURCE_DIR}/src/*/*.cpp
	
	# External source files
	${EXT_IMGUI_DIR}/imgui.cpp
	${EXT_IMGUI_DIR}/imgui_draw.cpp
	${EXT_IMGUI_DIR}/imgui_tables.cpp
	${EXT_IMGUI_DIR}/imgui_widgets.cpp
	${EXT_IMGUI_DIR}/backends/imgui_impl_win32.cpp
	${EXT_IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Build as Project executable
target_sources(KalaVideo PRIVATE ${SOURCE_FILES})

if (KALAKIT_WINDOWS)
	set_source_files_properties(${RESOURCE_FILE} PROPERTIES LANGUAGE RC)
	target_sources(KalaVideo PRIVATE ${RESOURCE_FILE})
endif()

# Forces the name to be KalaVideo
set_target_properties(KalaVideo PROPERTIES OUTPUT_NAME "KalaVideo")

target_compile_features(KalaVideo PRIVATE cxx_std_20)

target_include_directories(KalaVideo PRIVATE
	${CORE_DIR}
	${GRAPHICS_DIR}
	${UI_DIR}

	#External headers
	${EXT_WINDOW_DIR}
	${EXT_CRASH_DIR}
	${EXT_IMGUI_DIR}
	${EXT_IMGUI_DIR}/backends
)
if(KALAKIT_X11)
	target_include_directories(KalaVideo PRIVATE)
endif()

if (KALAKIT_WINDOWS)
	target_link_libraries(KalaVideo PRIVATE
		opengl32
		${CRASH_LIBRARY_PATH}
		${WINDOW_LIBRARY_PATH}
	)
else()
	target_link_libraries(KalaVideo PRIVATE
		OpenGL::GL
		${WINDOW_LIBRARY_PATH}
		${CRASH_LIBRARY_PATH}
		${X11_LIBRARIES}
	)
endif()

if(KALAKIT_RELEASE)
# Set the subsystem to WINDOWS
	set_target_properties(KalaVideo PROPERTIES
		WIN32_EXECUTABLE TRUE
	)

# Set the entry point (MSVC-specific)
	if (MSVC)
		set_target_properties(KalaVideo PROPERTIES
		LINK_FLAGS "/ENTRY:mainCRTStartup"
		)
	endif()
endif()

# Set the folder inside the install folder where the exe will be placed for this project
set(CMAKE_INSTALL_BINDIR bin)
install(TARGETS KalaVideo DESTINATION ${CMAKE_INSTALL_BINDIR})

# Copy "files" directory to the install directory after build
add_custom_command(TARGET KalaVideo POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E remove_directory
		"$<TARGET_FILE_DIR:KalaVideo>/files"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_SOURCE_DIR}/files"
		"$<TARGET_FILE_DIR:KalaVideo>/files"
)

# Copy all DLLs to the install directory after build
if(KALAKIT_RELEASE)
	set(DLL_ORIGIN_DIR "${CMAKE_SOURCE_DIR}/files/external dlls/release")
else()
	set(DLL_ORIGIN_DIR "${CMAKE_SOURCE_DIR}/files/external dlls/debug")
endif()
set(DLL_TARGET_DIR "$<TARGET_FILE_DIR:KalaVideo>")

file(GLOB DLL_FILES "${DLL_ORIGIN_DIR}/*")

foreach(DLL_FILE ${DLL_FILES})
    get_filename_component(DLL_NAME ${DLL_FILE} NAME)
    add_custom_command(TARGET KalaVideo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${DLL_FILE}"
            "${DLL_TARGET_DIR}/${DLL_NAME}"
    )
endforeach()

set(COPY_TARGETS LICENSE.md LIBRARIES.md)
foreach(FILE ${COPY_TARGETS})
  add_custom_command(TARGET KalaVideo POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E remove
		"$<TARGET_FILE_DIR:KalaVideo>/${FILE}"
	COMMAND ${CMAKE_COMMAND} -E copy
		"${CMAKE_SOURCE_DIR}/${FILE}"
		"$<TARGET_FILE_DIR:KalaVideo>/${FILE}"
  )
endforeach()

# Include CPack to enable packaging
include(CPack)
