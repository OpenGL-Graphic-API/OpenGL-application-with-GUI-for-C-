//#include"Renderer.h"

#include"Shader.h"
#include <GL/glew.h>
#include<map>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

enum class ShaderType
{
	VERTEX = GL_VERTEX_SHADER,
	FRAGMENT = GL_FRAGMENT_SHADER,
	GEOMETRY = GL_GEOMETRY_SHADER,
	TESS_CONTROL = GL_TESS_CONTROL_SHADER,
	TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
	COMPUTE = GL_COMPUTE_SHADER
};

std::map<unsigned int, std::string> ShaderInfo = {
	{GL_VERTEX_SHADER, "vertex"},
	{GL_FRAGMENT_SHADER, "fragment"},
	{GL_GEOMETRY_SHADER, "geometry"},
	{GL_TESS_CONTROL_SHADER, "Tess_control"},
	{GL_TESS_EVALUATION_SHADER, "tess_evaluation",},
	{GL_COMPUTE_SHADER, "compute"}
};

Shader::Shader(const std::string& filepath):m_FilePath(filepath), RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	RendererID = CreateShader(source.VertexSource, source.FragmentSource);

	
}

Shader::~Shader()
{
	glDeleteProgram(RendererID);
}

void Shader::Bind() const
{
	glUseProgram(RendererID);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLoaction(name), v0, v1, v2, v3);
}

void Shader::SetUniform4f(const std::string& name, const glm::vec4& value)
{
	glUniform4f(GetUniformLoaction(name), value.x, value.y, value.z, value.w);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(GetUniformLoaction(name), v0, v1, v2);
}

void Shader::SetUniform3f(const std::string& name, const glm::vec3& value)
{
	glUniform3f(GetUniformLoaction(name), value.x, value.y, value.z);
}

void Shader::SetUniform2f(const std::string& name, float v0, float v1)
{
	glUniform2f(GetUniformLoaction(name), v0, v1);
}

void Shader::SetUniform2f(const std::string& name, const glm::vec2& value)
{
	glUniform2f(GetUniformLoaction(name), value.x, value.y);
}

void Shader::SetUniform1f(const std::string& name, float v0)
{
	glUniform1f(GetUniformLoaction(name), v0);
}

void Shader::SetUniform1i(const std::string& name, int i)
{
	glUniform1i(GetUniformLoaction(name), i);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4 matrix44)
{
	glUniformMatrix4fv(GetUniformLoaction(name), 1, GL_FALSE, &matrix44[0][0]);
}

void Shader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix33)
{
	glUniformMatrix3fv(GetUniformLoaction(name), 1, GL_FALSE, &matrix33[0][0]);
}

int Shader::GetUniformLoaction(const std::string& name)const
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
		return m_UniformLocationCache[name];
	}

	int location = glGetUniformLocation(RendererID, name.c_str());
	if (location== -1) {
		std::cout << "Warning: uniform " << name << " doesn't exist" << std::endl;
	}
	m_UniformLocationCache[name] = location;
	
	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	ShaderProgramSource source;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else
			ss[(int)type] << line << "\n";
	}

	return { ss[0].str(), ss[1].str() };
}


unsigned int Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;

}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	//TODO error handling;
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		//char* message = (char*)alloca(length * sizeof(char));
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::string shaderinfo;
		auto it = ShaderInfo.find(type);
		if (it != ShaderInfo.end()) {
			shaderinfo = it->second;
		}

		//std::cout << "Fail to compile "<<(type == GL_VERTEX_SHADER? "vertex": "fragment")<<"shader!" << std::endl;
		std::cout << "Fail to compile " << shaderinfo << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}