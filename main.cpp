#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "fullScreenOp.h"


#include <stdlib.h>

OpenGLWindow* fullScreenMode = nullptr;

// 返回0-1之间的随机数
float rand01() {
	return (rand() % 255) / 255.0f;
}

// 第一个键盘交互键
void myKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		printf("亻尔 女子");
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		glClearColor(rand01(), rand01(), rand01(), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}
	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		// printf("change full screen mode! \n");
		fullScreenMode->SetFullScreen();
	}
		
}

void myScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	glClearColor(rand01(), rand01(), rand01(), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window); 
}

void fullScreenCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
}

int main() {
	
	int width = 1280, height = 720;
	const char* windowsName = "Journey starts from a single step";
	
	// 初始化
	if (!glfwInit()) {
		printf("Failed to initialize GLFW ...");
		return -1; 
	}
	
	// 获取opengl版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// means we will not use deprecated files
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(
		width, 
		height, 
		windowsName, 
		nullptr, 
		nullptr
	);

	// 如果创建失败报错
	if (window == nullptr) {
		printf("Window is nullptr!");
		glfwTerminate();
		return -1;
	}

	// 
	glfwMakeContextCurrent(window);
	
	// 
	gladLoadGL();

	// 创建显示器，用于全屏操作
	OpenGLWindow fullScreenInfo = OpenGLWindow();
	fullScreenMode = fullScreenInfo.Init(window);
	
	// 设置键盘交互
	glfwSetKeyCallback(window, myKeyCallBack);
	glfwSetScrollCallback(window, myScrollCallback);

	
	

	// 设置绘制区域
	glViewport(0, 0, width, height);
	
	// 初始buffer颜色
	glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// swap buffer 
	glfwSwapBuffers(window);

	// 不关闭的时候就保持窗口开启
	while (!glfwWindowShouldClose(window)) {
		
		
		glfwPollEvents();
	}

	// 结束操作
	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}