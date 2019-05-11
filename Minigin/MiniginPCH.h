#pragma once

#include "targetver.h"
#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>
#include <thread>


#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")

#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")

#pragma comment(lib, "SDL2_image.lib")  
#pragma comment(lib, "SDL2_ttf.lib") 

#pragma comment(lib, "SDL2_mixer.lib")

//#pragma comment(lib, "sdlgfx.lib")

#include <SDL_mixer.h>

#include <SDL.h>
//#include <SDL_gfxPrimitives.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Log.h" // Various logging functions
#include "SomeStructs.h"
#include "Time.h"
#include "PoolManager.h"