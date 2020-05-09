#pragma once
#ifdef MINIGIN_EXPORT
#define MINIGIN_ENTRYPOINT  __declspec(dllexport)
#else
#define MINIGIN_ENTRYPOINT __declspec(dllimport)
#endif


#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
