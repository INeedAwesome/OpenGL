#include "TestClearColor.h"

#include "Engine/Renderer/Renderer.h"
#include "imgui/imgui.h"

test::TestClearColor::TestClearColor()
	: m_clearColor{ 1.0f, 0.0f, 1.0f, 1.0f}
{

}

test::TestClearColor::~TestClearColor()
{
}

void test::TestClearColor::onUpdate(float deltaTime)
{
}

void test::TestClearColor::onRender()
{
	GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void test::TestClearColor::onImGuiRender()
{
	ImGui::ColorEdit4("clear color", m_clearColor);
}
