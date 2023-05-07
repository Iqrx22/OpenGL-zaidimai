#pragma once
#include "includes.h"

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
	void deleteProgram();

	void uniform1b(const std::string& name, bool value) const;
	void uniform1i(const std::string& name, int value) const;
	void uniform1f(const std::string& name, float value) const;
	void uniform3f(const std::string& name, float x, float y, float z) const;
	void uniform4f(const std::string& name, float x, float y, float z, float w) const;
};

