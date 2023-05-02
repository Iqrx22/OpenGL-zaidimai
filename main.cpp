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
	unsigned int vertexShader, fragmentShader, shaderProgram;
	BuildVertexShader(vertexShader);
	BuildFragmentShader(fragmentShader);
	LinkShaders(shaderProgram, vertexShader, fragmentShader);

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{		
		//input
		processInput(window);

		//rendering commands
		ClearWindowColor(117, 201, 235, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); 
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}
