#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "Engine/Renderer/Renderer.h"
#include "Engine/Buffers/IndexBuffer.h"
#include "Engine/Buffers/VertexBuffer.h"

#define GAME_TITLE "OpenGL"
#define GAME_RES_WIDTH 1152
#define GAME_RES_HEIGHT 648
// https://pacoup.com/2011/06/12/list-of-true-169-resolutions/

#define ERR_OK 0
#define ERR_UNIDENTIFINED -1
#define ERR_GLFWINIT -10
#define ERR_GLEWINIT -11
#define ERR_WIN_CREATION_FAIL -20

typedef unsigned int uint;

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{ 
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, 
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader" ) != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				//set the mode to vertex
				type = ShaderType::VERTEX;

			else if (line.find("fragment") != std::string::npos)
				//set the mode to fragment
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << std::endl;
		}
	}
	return {
		ss[0].str(), ss[1].str()
	};
}

static uint CompileShader(uint type, const std::string& source)
{ 
	uint id = glCreateShader(type);
	const char* src = source.c_str(); 
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile the " << (type == GL_VERTEX_SHADER ? "VERTEX SHADER" : "FRAGMENT SHADER" ) << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

static uint CreateShader(const std::string& vertexShader, const std::string& fragmentShader) 
{ 
	uint program = glCreateProgram();
	uint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	uint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	// TODO : Syntax errors / error handling
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main(void)
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return ERR_GLFWINIT;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(GAME_RES_WIDTH, GAME_RES_HEIGHT, GAME_TITLE, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return ERR_WIN_CREATION_FAIL;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	/* Center the window of the screen asuming the user has a 1080p resolution */
	glfwSetWindowPos(window, 1920/ 2 - GAME_RES_WIDTH / 2, 1080 / 2 - GAME_RES_HEIGHT / 2);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error! Code: " << ERR_GLEWINIT << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		float positions[] = {
			-0.5f, -0.5f, // 0
			 0.5f, -0.5f, // 1
			 0.5f,  0.5f, // 2
			-0.5f,  0.5f  // 3
		};

		uint indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		uint vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));


		VertexBuffer vb(positions, 4 * 2 * sizeof(float));

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

		IndexBuffer ib(indices, 6);

		ShaderProgramSource source = ParseShader("res/shaders/shader.shader");
		uint shader = CreateShader(source.VertexSource, source.FragmentSource);
		GLCall(glUseProgram(shader));

		GLCall(glUniform4f(glGetUniformLocation(shader, "u_Color"), 0.2, 0.6f, 0.8f, 1));

		GLCall(glBindVertexArray(0));
		GLCall(glUseProgram(0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT));
			GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));

			GLCall(glUseProgram(shader));
			GLCall(glUniform4f(glGetUniformLocation(shader, "u_Color"), 0.5, 0.5f, 0.7f, 1.0f));

			GLCall(glBindVertexArray(vao));
			ib.Bind();
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));



			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());
		}

		glDeleteProgram(shader);
	}
	
	glfwTerminate();
	
	return ERR_OK;
}
