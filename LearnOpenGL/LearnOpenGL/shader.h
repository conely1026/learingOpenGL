#pragma once
#include <glad/glad.h>; 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class shader
{
public:
	shader();
	shader(const char* vertexPath, const char* fragmentPath);
	~shader();

	// 程序ID
	unsigned int ID;

	// 使用/激活程序
	void use();

	// uniform工具函数
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
private:
	void checkCompileErrors(unsigned int shader, std::string type);
};

