#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "fullScreenOp.h"


#include <stdlib.h>

OpenGLWindow* fullScreenMode = nullptr;

// ����0-1֮��������
float rand01() {
	return (rand() % 255) / 255.0f;
}

// ��һ�����̽�����
void myKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		printf("��� Ů��");
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
	
	// ��ʼ��
	if (!glfwInit()) {
		printf("Failed to initialize GLFW ...");
		return -1; 
	}
	
	// ��ȡopengl�汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// means we will not use deprecated files
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ��������
	GLFWwindow* window = glfwCreateWindow(
		width, 
		height, 
		windowsName, 
		nullptr, 
		nullptr
	);

	// �������ʧ�ܱ���
	if (window == nullptr) {
		printf("Window is nullptr!");
		glfwTerminate();
		return -1;
	}

	// 
	glfwMakeContextCurrent(window);
	
	// 
	gladLoadGL();

	// ������ʾ��������ȫ������
	OpenGLWindow fullScreenInfo = OpenGLWindow();
	fullScreenMode = fullScreenInfo.Init(window);
	
	// ���ü��̽���
	glfwSetKeyCallback(window, myKeyCallBack);
	glfwSetScrollCallback(window, myScrollCallback);

	
	

	// ���û�������
	glViewport(0, 0, width, height);
	
	// ��ʼbuffer��ɫ
	glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// swap buffer 
	glfwSwapBuffers(window);

	// ���رյ�ʱ��ͱ��ִ��ڿ���
	while (!glfwWindowShouldClose(window)) {
		
		
		glfwPollEvents();
	}

	// ��������
	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}