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

	Shader myShader("Shader1.vertexShader", "Shader1.fragmentShader");

	unsigned int VBO, VAO, EBO;
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	int i = 0;

	while (!glfwWindowShouldClose(window))
	{		
		//input
		processInput(window);

		//rendering commands
		ClearWindowColor(117, 201, 235, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();

		float timeValue = glfwGetTime();
		float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
		myShader.uniform4f("myColor", 0.0f, greenValue, 0.0f, 1.0f);

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
	myShader.deleteProgram();

	glfwTerminate();
	return 0;
}
