#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "Engine/Renderer/Renderer.h"
#include "Engine/Buffers/VertexBuffer.h"
#include "Engine/Buffers/VertexBufferLayout.h"
#include "Engine/Buffers/IndexBuffer.h"
#include "Engine/Buffers/VertexArray.h"
#include "Engine/Shader/Shader.h"
#include "Engine/Texture/Texture.h"
#include "Engine/WindowingSystem/Window.h"

#include "Tests/TestClearColor.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define GAME_TITLE "OpenGL"
#define GAME_RES_WIDTH 960
#define GAME_RES_HEIGHT 540
// https://pacoup.com/2011/06/12/list-of-true-169-resolutions/

#define ERR_OK 0
#define ERR_UNIDENTIFINED -1
#define ERR_GLFWINIT -10
#define ERR_GLEWINIT -11
#define ERR_WIN_CREATION_FAIL -20

int main(void)
{
	if (!glfwInit())
		return ERR_GLFWINIT;

	Window window(GAME_RES_WIDTH, GAME_RES_HEIGHT, GAME_TITLE);
	window.SetDefaultWindowHints();
	if (!window.CreateWindow())
		return ERR_WIN_CREATION_FAIL;
	window.SetVSync(true);

	if (glewInit() != GLEW_OK)
		std::cout << "Error! Code: " << ERR_GLEWINIT << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	//Begining of a new scope
	{
		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f,	// 0
			 50.0f,  -50.0f, 1.0f, 0.0f,	// 1
			 50.0f,  50.0f, 1.0f, 1.0f,	// 2
			-50.0f, 50.0f, 0.0f, 1.0f 	// 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		//VertexArray va;
		//VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		//VertexBufferLayout layout;
		//layout.Push<float>(2);
		//layout.Push<float>(2);
		//va.AddBuffer(vb, layout);

		//IndexBuffer ib(indices, 6);

		//glm::mat4 proj = glm::ortho(0.0f, (float)GAME_RES_WIDTH, 0.0f, (float)GAME_RES_HEIGHT, -1.0f, 1.0f);
		//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		//Shader shader("res/shaders/shader.shader");
		//shader.Bind();
		//shader.SetUniform4f("u_Color", 0.2f, 0.6f, 0.8f, 1.0f);

		//Texture texture("res/textures/ChernoLogo.png");
		//texture.Bind(0); 
		//shader.SetUniform1i("u_Texture", 0);

		//va.Unbind();
		//shader.Unbind();
		//vb.Unbind();
		//ib.Unbind();

		Renderer renderer;

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	// Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	// Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		// Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		// Enable Multi-Viewport / Platform Windows
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init();
		ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<test::TestClearColor>("Clear Color");

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window.GetWindow()))
		{
			renderer.Clear();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest)
			{
				currentTest->onUpdate(0.0f);
				currentTest->onRender();
				ImGui::Begin("Test");
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->onImGuiRender();
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			GLCall(glfwSwapBuffers(window.GetWindow()));
			GLCall(glfwPollEvents());
		}
		delete currentTest;
		if (currentTest != testMenu)
		{
			delete testMenu;
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

	return ERR_OK;
}
