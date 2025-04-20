//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

//kalavideo
#include "core/core.hpp"

using Core::KalaVideo;

int main()
{
	KalaVideo::Initialize();
	KalaVideo::Update();
	KalaVideo::Shutdown();
	
	return 0;
}