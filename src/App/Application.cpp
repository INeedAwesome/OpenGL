#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define GAME_TITLE "OpenGL"
#define GAME_RES_WIDTH 640
#define GAME_RES_HEIGHT 480

#define ERR_OK 0
#define ERR_GLFWINIT -1
#define ERR_GLEWINIT -2

int main(void)
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(GAME_RES_WIDTH, GAME_RES_HEIGHT, GAME_TITLE, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return ERR_GLFWINIT;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	/* Center the window of the screen asuming the user has a 1080p resolution */
	glfwSetWindowPos(window, 1920/ 2 - GAME_RES_WIDTH / 2, 1080 / 2 - GAME_RES_HEIGHT / 2);

	if (glewInit() != GLEW_OK)
		std::cout << "Error! Code: " << ERR_GLEWINIT << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
