#include "Window.h"

Window::Window(int width, int height, std::string name)
{
	m_width = width;
	m_height = height;
	m_name = name;
}

Window::~Window()
{
}

void Window::SetDefaultWindowHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool Window::CreateWindow()
{
	m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);
	glfwSetWindowPos(m_window, 1920 / 2 - m_width / 2, 1080 / 2 - m_height / 2);
	return true;
}

void Window::SetVSync(bool vsync)
{
	glfwSwapInterval(vsync ? 1 : 0);
}
