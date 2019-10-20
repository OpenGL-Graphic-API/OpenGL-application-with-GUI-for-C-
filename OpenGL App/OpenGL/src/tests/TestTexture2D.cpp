#include "TestTexture2D.h"
#include"Renderer.h"
#include"imGui/imgui.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

namespace test {

	TestTexture2D::TestTexture2D() :
		proj(glm::ortho(-2.f, 2.f, -1.5f, 1.5f, -1.f, 1.f)),
		view(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.f, 0.f))),
		translationA(-0.5f, 0.0f, 0.f), translationB(0.5f, 0.0f, 0.f)
	{
		float Vertice_Array[]{ -0.5f, -0.5f, 0.0f, 0.0f,
								0.5f, -0.5f, 1.0f, 0.0f,
								0.5f,  0.5f, 1.0f, 1.0f,
							   -0.5f,  0.5f, 0.0f, 1.0f };

		unsigned int indice[]{ 0, 1, 2, 2, 3, 0 };

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		vao = std::make_unique<VertexArray>();

		vbo = std::make_unique<VertexBuffer>(Vertice_Array, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		vao->AddBuffer(*vbo, layout);

		ibo = std::make_unique<IndexBuffer>(indice, 6);

		shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		shader->Bind();
		texture = std::make_unique<Texture>("res/textures/gold-dollar.png");
		//texture->Bind();
		shader->SetUniform1i("Tex", 0);
		shader->SetUniformMat4f("proj", proj);
		shader->SetUniformMat4f("view", view);

	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdate(float deltatime)
	{

	}

	void TestTexture2D::OnRender()
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		Renderer renderer;
		texture->Bind();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
		glm::mat4 model_ = glm::translate(glm::mat4(1.0f), translationB);

		shader->SetUniformMat4f("model", model);

		renderer.Draw(*vao, *ibo, *shader);
		//va.UnBind();
		shader->SetUniformMat4f("model", model_);
		renderer.Draw(*vao, *ibo, *shader);

	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("TranslationA", &translationA.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("TranslationB", &translationB.x, -1.0f, 1.0f);
		// Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}