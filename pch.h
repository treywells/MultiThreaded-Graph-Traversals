// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define CONNECT 0
#define DISCONNECT 1
#define MOVE 2
#define FAILURE 0
#define SUCCESS 1 


// add headers that you want to pre-compile here
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <string>
#include <iostream>

// user-defined files
#include "CommandResponseClasses.h"
#include "Pipe.h"
#include "Discovered.h"
#include "UnexploredRoom.h"
#include "Ubase.h"
#include "Ubreadth.h"
#include "Udepth.h"
#include "Ubest.h"
#include "Astar.h"
#include "Search.h"

#endif //PCH_H
