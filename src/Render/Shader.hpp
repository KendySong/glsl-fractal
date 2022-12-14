#pragma once
#include <string>

class Shader 
{
public :
	Shader() = default;
	Shader(const char* vertexPath, const char* fragmentPath);

	unsigned int getShaderID() noexcept;

private :
	bool checkCompileStatus(unsigned int objectID, std::string name);
	std::pair<std::string, bool> loadShader(const char* shaderPath);

	unsigned int m_shaderID;
};