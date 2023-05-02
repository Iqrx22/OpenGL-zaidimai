#pragma once
#include "includes.h"
class Functions
{
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void ClearWindowColor(int16_t red, int16_t green, int16_t blue, float alpha);

void InitGLFW();
int InitWindow(GLFWwindow* window);
int InitGlad();

void BuildVertexShader(unsigned int &vertexShader);
void BuildFragmentShader(unsigned int &fragmentShader);
void LinkShaders(unsigned int& shaderProgram, unsigned int& vertexShader, unsigned int& fragmentShader);

