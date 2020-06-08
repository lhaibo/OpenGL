#pragma once
#include <string>
class Shader
{
public:
	Shader(const char* vertexPath,const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int id;
	void use();
private:
	void checkCompileErrors(unsigned int id, std::string type);
};

