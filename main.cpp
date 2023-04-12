#include "core.h"
#include "Shader.h"
#include <vector>

OpenGLWindow* fullScreenMode = nullptr;

bool keyPressedData[1000] = {};



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
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		keyPressedData['A'] = true;
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
	
	int width = 800, height = 800;
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

	std::vector<GLfloat> vertices = {
		-0.7f, -0.5f * float(sqrt(3))/3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.7f, 0.0f,
		0.2f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -1.0f * float(sqrt(3)) / 3, 0.0f,
		0.0f, -0.8f, 0.0f
	};
	const unsigned int vertexSize = 3;

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

	// compile shader : vertex and fragment
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// create fragment shader and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// compile shader into machine code
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// link all shaders into shader program
	glLinkProgram(shaderProgram);


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLuint VAO, VBO;
	// ordering is important
	// generate VAO and VBO with only 1 object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	// make VAO current vertex array object by binding it
	glBindVertexArray(VAO);

	// bind VBO and declare it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ע�⣬��һ�������������byte������Ϣ��Ȼ����ָ���ַ
	// sizeof �����������͵Ĵ�С������sizeof(vertices)�ͻ᷵��std::vector��size
	glBufferData(GL_ARRAY_BUFFER, 10 * vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	// configure Vertex attribute so opengl know how to read VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// bind both VAO and VBO to 0 so we dont accidentally modify them
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);




	
	// ��ʼbuffer��ɫ
	glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// swap buffer 
	glfwSwapBuffers(window);

	// ���رյ�ʱ��ͱ��ִ��ڿ���
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		if (keyPressedData['A']) {
			for (int i = 0; i < 9; i++) {
				vertices.push_back(rand01());
			}
			keyPressedData['A'] = false;
			// glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
		}
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / vertexSize);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// ��������
	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}