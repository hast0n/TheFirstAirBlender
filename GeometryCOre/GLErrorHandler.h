#pragma once
#include "glut.h"
#include "Logger.h"
#include <iostream>


class GLErrorHandler
{
public:
	static void ClearErrors();

	static bool CheckErrors();
};

// specific to MSVC
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) x;\
	ASSERT(GLErrorHandler::CheckErrors());

//GLErrorHandler::ClearErrors();\