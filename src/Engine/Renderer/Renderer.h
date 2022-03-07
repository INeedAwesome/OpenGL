#pragma once

#include <GL/glew.h>

#include "Engine/Buffers/IndexBuffer.h"
#include "Engine/Buffers/VertexArray.h"
#include "Engine/Shader/Shader.h"

#include "imgui/imgui.h"


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Clear() const;
	void Draw(VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

private:

};

