#include "includes.h"

const int WINDOW_HEIGHT = 800, WINDOW_WIDTH = 800;
const char* WINDOW_TITLE = "OpenGL zaidimai";

int main() {
	//Initializing glfw
	InitGLFW();
	
	//Window creation
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	if (InitWindow(window) == -1) return -1;

	//Initalizing Glad
	if (InitGlad() == -1) return -1;
	
	//Dealing with shaders
	/*float vertices[] = {
	  // l - r| t - b   
		 0.7f,  0.7f, 0.0f, // top right +
		-0.7f, -0.7f, 0.0f, // bottom left +
		 0.65f, -0.7f, 0.0f, // bottom right bottom +
		 0.7f, -0.65f, 0.0f, // bottom right right +
		-0.65f,  0.7f, 0.0f  //top left top +
		-0.7f,  0.65f, 0.0f  //top left left
	};*/

	float vertices[] = {
		-0.70f,   0.65f, 0.0f, // top left: bottom left triangle
		-0.65f,  0.70f,  0.0f, // top left: top right triangle
		0.70f,   0.70f, 0.0f, // top right: top right triangle
		-0.70f,  -0.70f, 0.0f, // bottom left: bottom left triangle
		 0.65f, -0.70f,  0.0f, // bottom right: bottom left triangle
		 0.70f,  -0.65f, 0.0f  // bottom right: top right triangle
	};

	unsigned int indices[] = {
		0, 3, 4, // top-right triangle
		1, 2, 5  // bottom-left triangle
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
