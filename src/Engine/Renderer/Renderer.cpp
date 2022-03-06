#include "Renderer.h"

#include <iostream>
#include <sstream>

void GLClearError()
{
	while (!glGetError != GL_NO_ERROR); // "resets / clears" the error "list"
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::string logString;
		if (error == GL_INVALID_ENUM) {
			logString = "GL_INVALID_ENUM";
		}
		else if (error == GL_INVALID_VALUE) {
			logString = "GL_INVALID_VALUE";
		}
		else {
			logString = "GL_INVALID_OPERATION";
		}
		std::stringstream ss;
		ss << "0x0" << std::hex << error;
		std::cout <<
			"[OpenGL Error] (" << error << "/" << ss.str() << "): " << logString << "\n" <<
			"	  - Function: " << function << "\n" <<
			"	  - File: " << file << "\n" <<
			"	  - Line: " << line << std::endl;

		return false;
	}
	return true;
}