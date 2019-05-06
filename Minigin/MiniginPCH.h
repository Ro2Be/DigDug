#pragma once

#include "targetver.h"

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>
#include <algorithm>

//DEFAULT INCLUDES//
#include "Const.h"
#include "Structs.h"
#include "Chrono.h"
#include "GameObject.h"
#include "Component.h"
//----------------//

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Log.h" // Various logging functions

#pragma comment(lib,"xinput.lib")
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "SDL.h"