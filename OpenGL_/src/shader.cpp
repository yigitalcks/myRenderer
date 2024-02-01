#include "shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {

	std::string vertexSource = getShaderSource(vertexShaderPath);
	std::string fragmentSource = getShaderSource(fragmentShaderPath);

	id = createProgram(vertexSource, fragmentSource); // set program id
}

void Shader::use() {
	glUseProgram(id);
}

unsigned int Shader::getId() const{
	return id;
}

void Shader::setInt1(const std::string& name, int value1) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value1);
}
void Shader::setInt2(const std::string& name, int value1, int value2) const {
	glUniform2i(glGetUniformLocation(id, name.c_str()), value1, value2);
}
void Shader::setInt3(const std::string& name, int value1, int value2, int value3) const {
	glUniform3i(glGetUniformLocation(id, name.c_str()), value1, value2, value3);
}
void Shader::setInt4(const std::string& name, int value1, int value2, int value3, int value4) const {
	glUniform4i(glGetUniformLocation(id, name.c_str()), value1, value2, value3, value4);
}
	
void Shader::setFloat1(const std::string& name, float value1) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value1);
}
void Shader::setFloat2(const std::string& name, float value1, float value2) const {
	glUniform2f(glGetUniformLocation(id, name.c_str()), value1, value2);
}
void Shader::setFloat3(const std::string& name, float value1, float value2, float value3) const {
	glUniform3f(glGetUniformLocation(id, name.c_str()), value1, value2, value3);
}
void Shader::setFloat4(const std::string& name, float value1, float value2, float value3, float value4) const {
	glUniform4f(glGetUniformLocation(id, name.c_str()), value1, value2, value3, value4);
}


std::string Shader::getShaderSource(const std::string& shaderPath) {
	std::ifstream stream(shaderPath);

	std::stringstream ss;
	std::string line;
	while (std::getline(stream, line)) {
		ss << line << "\n";
	}
	return ss.str();
}

unsigned int Shader::CCshader(unsigned int type, const std::string& sourceCode) {

	unsigned int id = glCreateShader(type);
	const char* src = sourceCode.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* msg = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, msg);

		std::cout << "fail in Compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader" << std::endl;
		std::cout << msg;

		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int Shader::createProgram(const std::string& vertexShader, const std::string& fragmentShader) {

	unsigned int program = glCreateProgram();
	unsigned int vs = CCshader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CCshader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}