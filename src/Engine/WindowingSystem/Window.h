#pragma once

#include "Engine/Renderer/Renderer.h"
#include <GLFW/glfw3.h>


class Window
{
public:
	Window(int width, int height, std::string name);
	~Window();

	void SetDefaultWindowHints();
	bool CreateWindow();
	void SetVSync(bool vsync);

	inline GLFWwindow* GetWindow() { return m_window; }

private:
	GLFWwindow* m_window;
	int m_width;
	int m_height;
	std::string m_name;
};

