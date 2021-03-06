#pragma once

#include "targetver.h"
#include <stdio.h>

#include <string>
#include <iostream>
#include <sstream>
#include <tchar.h>

#include <memory>

#include <vector>
#include <experimental/vector>
#include <unordered_map>
#include <map>
#include <algorithm>

//DEFAULT INCLUDES//
#include "Const.h"
#include "Structs.h"
#include "Chrono.h"
#include "Singleton.h"
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