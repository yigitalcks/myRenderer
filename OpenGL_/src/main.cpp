#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "shader.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include "texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(void) {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(720, 720, "Open_GL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW Init error\n";
	}

	glViewport(0, 0, 720, 720);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	float verticies[] = {
		// positions		 // color		  
		-0.7f,  0.7f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.7f, -0.7f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		 0.7f, -0.7f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		 0.7f,  0.7f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f
	};
	//float vert1[] = {
	//	-0.9f, -0.5f, 0.0f,  // left 
	//	-0.0f, -0.5f, 0.0f,  // right
	//	-0.45f, 0.5f, 0.0f,  // top 
	//};
	//float vert2[] = {
	//	0.0f, -0.5f, 0.0f,  // left
	//	0.9f, -0.5f, 0.0f,  // right
	//	0.45f, 0.5f, 0.0f   // top 
	//};

	unsigned short indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int VAO, VBO, EBO, texture;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenTextures(1, &texture);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Texture texture_i;
	texture_i.load("assets/container.jpg");
	
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned short), indicies, GL_STATIC_DRAW);

	//vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//glBindVertexArray(VAO[1]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vert2), vert2, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned short), &indicies[3], GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	Shader shaderHandler("shaders/vertex.shader", "shaders/fragment.shader");

	//unsigned int shaderProgram = CreateProgram(vs, fs);
	glBindVertexArray(VAO);
	shaderHandler.use();

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);

		double timeValue = glfwGetTime();
		float redValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
		float greenValue = static_cast<float>(cos(timeValue) / 2.0 + 0.5);
		//int vertexColorLocation = glGetUniformLocation(shaderHandler.getId(), "renkli");
		//glUniform4f(vertexColorLocation, redValue, greenValue, 0.0f, 1.0f);
		shaderHandler.setFloat4("renkli", redValue, greenValue, 0.0f, 1.0f);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}