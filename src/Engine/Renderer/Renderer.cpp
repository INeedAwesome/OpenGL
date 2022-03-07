#include "Renderer.h"

#include <iostream>
#include <sstream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR); // "resets / clears" the error "list"
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

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0, 0, 0, 1.0f));
}

void Renderer::Draw(VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{ 
	shader.Bind();
	va.Bind();
	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}
