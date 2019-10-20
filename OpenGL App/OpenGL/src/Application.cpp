// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

//Include IMGUI
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw_gl3.h"
#include <iostream>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include"Texture.h"
#include"tests/TestClearColor.h"
#include"tests/TestTexture2D.h"
#include"tests/Test.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);



int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //flag for checking memory leak

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1);
	//glewInit();
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR" << std::endl;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	/* Loop until the user closes the window */

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	Renderer renderer;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	test::Test* CurrentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(CurrentTest);
	CurrentTest = testMenu;
	testMenu->RegisterTest<test::TestClearColor>("Clear Color");
	testMenu->RegisterTest<test::TestTexture2D>("2D Texture");

	//test::TestClearColor test;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		/* Render here */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		renderer.Clear();
		//test.OnUpdate(0.0f);
		//test.OnRender();

		ImGui_ImplGlfwGL3_NewFrame();
		if (CurrentTest) {
			CurrentTest->OnUpdate(0.0f);
			CurrentTest->OnRender();
			ImGui::Begin("Test");
			if (CurrentTest != testMenu && ImGui::Button("<-"))
			{
				delete CurrentTest;
				CurrentTest = testMenu;
			}

			CurrentTest->OnImGuiRender();
			ImGui::End();

		}
		//test.OnImGuiRender();

		ImGui::Render();

		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	delete CurrentTest;
	if (CurrentTest != testMenu)
		delete testMenu;
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

