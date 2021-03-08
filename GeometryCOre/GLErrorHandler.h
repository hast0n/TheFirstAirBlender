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

