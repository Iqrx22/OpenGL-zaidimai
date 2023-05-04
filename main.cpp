#include "includes.h"

const int WINDOW_HEIGHT = 800, WINDOW_WIDTH = 800;
const char* WINDOW_TITLE = "OpenGL zaidimai";

const char* fragmentShaderOrangeSource =
"#version 460 core\n"
"out vec4 FragColor;\n\n"

"void main()\n"
"{\n"
" FragColor = vec4(0.878431f, 0.533333f, 0.078431f, 1.0f);\n"
"}\0";

const char* fragmentShaderCyanSource =
"#version 460 core\n"
"out vec4 FragColor;\n\n"

"void main()\n"
"{\n"
" FragColor = vec4(0.458824f, 0.788235f, 0.921569f, 1.0f);\n"
"}\0";

int main() {
	//Initializing glfw
	InitGLFW();
	
	//Window creation
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	if (InitWindow(window) == -1) return -1;

	//Initalizing Glad
	if (InitGlad() == -1) return -1;
	
	//Dealing with shaders

	float orangeTriangle[] = {
		-0.70f,  0.65f, 0.0f, // top left: bottom left triangle
		-0.70f, -0.70f, 0.0f, // bottom left: bottom left triangle
		 0.65f, -0.70f, 0.0f, // bottom right: bottom left triangle
	};
	float cyanTriangle[] = {
		-0.65f,  0.70f, 0.0f, // top left: top right triangle
		 0.70f,  0.70f, 0.0f, // top right: top right triangle
		 0.70f, -0.65f, 0.0f  // bottom right: top right triangle
	};

	unsigned int vertexShader, fragmentShaderOrange, fragmentShaderCyan, shaderProgram1, shaderProgram2, VBOs[2], VAOs[2];
	BuildVertexShader(vertexShader);
	BuildFragmentShader(fragmentShaderOrange, fragmentShaderOrangeSource);
	BuildFragmentShader(fragmentShaderCyan, fragmentShaderCyanSource);
	LinkShaders(shaderProgram1, vertexShader, fragmentShaderOrange);
	LinkShaders(shaderProgram2, vertexShader, fragmentShaderCyan); 

	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(orangeTriangle), orangeTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cyanTriangle), cyanTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{		
		//input
		processInput(window);

		//rendering commands
		ClearWindowColor(0, 48, 4, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram1);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES,0, 3);
		// glBindVertexArray(0);
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgram1);
	glDeleteProgram(shaderProgram2);

	glfwTerminate();
	return 0;
}
