#include"TestClearColor.h"
#include"Renderer.h"
namespace test {

	TestClearColor::TestClearColor():m_ClearColor{0.2f, 0.3f, 0.8f, 1.0f}
	{

	}

	TestClearColor::~TestClearColor()
	{
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void TestClearColor::OnUpdate(float deltatime)
	{

	}

	void TestClearColor::OnRender()
	{

	}

	void TestClearColor::OnImGuiRender()
	{

	}

}