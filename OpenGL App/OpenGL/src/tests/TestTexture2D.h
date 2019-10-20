#pragma once
#include"Test.h"
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include"Texture.h"
#include<memory>

namespace test
{
	class TestTexture2D :public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();
		void OnUpdate(float deltatime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr <VertexArray> vao;
		std::unique_ptr <VertexBuffer> vbo;
		std::unique_ptr <IndexBuffer> ibo;
		std::unique_ptr <Shader> shader;
		std::unique_ptr <Texture> texture;
		glm::vec3 translationA;
		glm::vec3 translationB;
		glm::mat4 proj;
		glm::mat4 view;


	};
}
