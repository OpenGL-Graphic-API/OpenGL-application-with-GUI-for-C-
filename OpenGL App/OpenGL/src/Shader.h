#pragma once
#include<string>
#include<unordered_map>
#include"glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int RendererID;
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform4f(const std::string& name, const glm::vec4& value);

	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform3f(const std::string& name, const glm::vec3& value);

	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform2f(const std::string& name, const glm::vec2& value);

	void SetUniform1f(const std::string& name, float v0);
	void SetUniform1i(const std::string& name, int i);

	void SetUniformMat4f(const std::string& name, const glm::mat4 matrix44);
	void SetUniformMat3f(const std::string& name, const glm::mat3& matrix33);
private:
	int GetUniformLoaction(const std::string& name)const;
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);

};
