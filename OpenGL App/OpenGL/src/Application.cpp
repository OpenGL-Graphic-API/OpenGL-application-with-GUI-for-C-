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
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

	float Vertice_Array[]{ -0.5f, -0.5f, 0.0f, 0.0f,
							0.5f, -0.5f, 1.0f, 0.0f,
							0.5f,  0.5f, 1.0f, 1.0f,
						   -0.5f,  0.5f, 0.0f, 1.0f };
	unsigned int indice[]{ 0, 1, 2, 2, 3, 0 };
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	VertexArray va;
	VertexBuffer vb(Vertice_Array, 4*4*sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	//va.UnBind();

	IndexBuffer ib(indice, 6);
	//ib.Bind();
	//va.UnBind();
	
	glm::mat4 proj = glm::ortho(-2.f, 2.f, -1.5f, 1.5f, -1.f, 1.f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.f, 0.f));
	Shader shader("res/shaders/Basic.shader");
	shader.Bind();
	Texture texture("res/textures/gold-dollar.png");
	texture.Bind();
	shader.SetUniform1i("Tex", 0);
	shader.SetUniformMat4f("proj", proj);
	shader.SetUniformMat4f("view", view);
	//shader.SetUniformMat4f("model", model);

	Renderer renderer;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
	glm::vec3 translationA(-0.5f, 0.f, 0.f);
	glm::vec3 translationB(0.5f, 0.f, 0.f);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		/* Render here */
		renderer.Clear();
		ImGui_ImplGlfwGL3_NewFrame();
		texture.Bind();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
		glm::mat4 model_ = glm::translate(glm::mat4(1.0f), translationB);
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		shader.SetUniformMat4f("model", model);
		//glClear(GL_COLOR_BUFFER_BIT);
		//shader.SetUniform1f("b", b);
		renderer.Draw(va, ib, shader);
		//va.UnBind();
		shader.SetUniformMat4f("model", model_);
		renderer.Draw(va, ib, shader);
		//va.Bind();
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		//increment *= ((b > 1 || b < 0) ? -1 : 1);
		//b += increment;
		{

			ImGui::SliderFloat3("TranslationA", &translationA[0], -1.0f, 1.0f);
			ImGui::SliderFloat3("TranslationB", &translationB[0], -1.0f, 1.0f);
			// Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			
		}

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
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