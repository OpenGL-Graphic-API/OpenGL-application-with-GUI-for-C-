#include"Test.h"
#include"imgui/imgui.h"
namespace test
{
	TestMenu::TestMenu(Test*& m_CurrentTestPointer) :m_CurrentTest(m_CurrentTestPointer)
	{

	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& it : m_Tests)
		{
			if (ImGui::Button(it.first.c_str()))
			{
				m_CurrentTest = it.second();
			}
		}
	}


}