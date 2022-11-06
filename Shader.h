#pragma once
#include <string>
#include <unordered_map>
#include "glm/mat4x4.hpp"

class Shader
{
public:

	

	enum ShaderType
	{
		None = 0,Vertex=1,Fragment=2
	};

	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void Bind()const;
	void Unbind()const;

	void SetUniform4f(const std::string& name, float v0,float v1,float v2,float v3);
	void SetUniform1i(const std::string& name,int value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:

	int GetUniformLocation(const std::string& name) const;
	unsigned int CreateShader(const char* vertexPath, const char* fragmentPath);
	void CheckCompileErrors(unsigned int shader, std::string& type);

private:
	unsigned int m_RendererID;
	mutable std::unordered_map<std::string,int> m_UniformLocationCache;
};
