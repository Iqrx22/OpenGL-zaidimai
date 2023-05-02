#include "includes.h";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void ClearWindowColor(int16_t red, int16_t green, int16_t blue, float alpha) {
	glClearColor((float)red / 255, (float)green / 255, (float)blue / 255, alpha);
}
