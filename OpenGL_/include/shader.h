#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {

public:

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	//bind shaders and use program
	void use();

	//get id
	unsigned int getId() const;

	// set integer uniforms
	void setInt1(const std::string& name, int value1) const;
	void setInt2(const std::string& name, int value1, int value2) const;
	void setInt3(const std::string& name, int value1, int value2, int value3) const;
	void setInt4(const std::string& name, int value1, int value2, int value3, int value4) const;
	//set float uniforms
	void setFloat1(const std::string& name, float value1) const;
	void setFloat2(const std::string& name, float value1, float value2) const;
	void setFloat3(const std::string& name, float value1, float value2, float value3) const;
	void setFloat4(const std::string& name, float value1, float value2, float value3, float value4) const;

private:
	unsigned int id;

private:
	std::string getShaderSource(const std::string& shaderPath); //get shader source code to the string
	unsigned int CCshader(unsigned int type, const std::string& sourceCode); //create shader and return id
	unsigned int createProgram(const std::string& vertexShader, const std::string& fragmentShader); //create shader and program, then link to the program
};



#endif