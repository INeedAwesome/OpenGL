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
#include "Engine/Buffers/VertexArray.h"
#include "Engine/Shaders/Shader.h"

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

	//Begining of a new scope
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

		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		Shader shader("res/shaders/shader.shader");
		shader.Bind();


		shader.SetUniform4f("u_Color", 0.2, 0.6f, 0.8f, 1);

		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT));
			GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));

			shader.Bind();
			
			shader.SetUniform4f( "u_Color", 0.5, 0.5f, 0.7f, 1.0f);

			va.Bind();
			ib.Bind();
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));



			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());
		}
	}
	
	glfwTerminate();
	
	return ERR_OK;
}
