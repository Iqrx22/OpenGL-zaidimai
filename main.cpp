#include "includes.h"

const int WINDOW_HEIGHT = 800, WINDOW_WIDTH = 800;
const char* WINDOW_TITLE = "OpenGL zaidimai";

void test(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO, float vertices[], unsigned int indices[]) {
	
	
}

int main() {
	//Initializing glfw
	InitGLFW();
	
	//Window creation
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	if (InitWindow(window) == -1) return -1;

	//Initalizing Glad
	if (InitGlad() == -1) return -1;
	
	//Dealing with shaders
	float vertices[] = {
		 0.5f,  0.5f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f  //top left
	};

	unsigned int indices[] = {
		0, 1, 3, // top-right triangle
		1, 2, 3  // bottom-left triangle
	};

	unsigned int vertexShader, fragmentShader, shaderProgram, VBO, VAO, EBO;
	BuildVertexShader(vertexShader);
	BuildFragmentShader(fragmentShader);
	LinkShaders(shaderProgram, vertexShader, fragmentShader);
	
	BufferObjectGenerators1(VBO, VAO, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	BufferObjectGenerators2(VBO, VAO, EBO);

	while (!glfwWindowShouldClose(window))
	{		
		//input
		processInput(window);

		//rendering commands
		ClearWindowColor(117, 201, 235, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); 
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}
