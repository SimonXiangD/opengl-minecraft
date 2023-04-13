#include "core.h"
#include "Shader.h"
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

OpenGLWindow* fullScreenMode = nullptr;

float keyPressedData[1000] = {};

using std::endl;
using std::cin;
using std::cout;

using glm::mat4;
using glm::vec3;


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
		keyPressedData['A'] += 0.1;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		keyPressedData['S'] += 0.1;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		keyPressedData['D'] += 0.1;
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		keyPressedData['W'] += 0.1;
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

	std::vector<GLfloat> vertices = {
		-0.7f, -0.5f * float(sqrt(3))/3, 0.0f,1,1,1,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,1,1,1,
		0.0f, 0.7f, 0.0f,1,1,1,
		0.2f, -0.5f * float(sqrt(3)) / 3, 0.0f,1,1,1,
		0.5f, -1.0f * float(sqrt(3)) / 3, 0.0f,1,1,1,
		0.0f, -0.8f, 0.0f,1,1,1
	};
	const unsigned int vertexSize = 3;

	GLfloat vertices2[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	float vertices3[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};


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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	// pos, color, texcoord
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// bind both VAO and VBO to 0 so we dont accidentally modify them
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	std::vector<unsigned int> indices = {
		0,1,3,
		1,2,3
		// 3,4,5
	};

	//GLuint EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);


	int texW, texH, nrChannels;
	unsigned char* data = stbi_load("iron.png", &texW, &texH, &nrChannels, 0);
	if (data) cout << " iron texture load succeed!" << endl;
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texW, texH, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);


	
	// ��ʼbuffer��ɫ
	glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

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

	// swap buffer 
	glfwSwapBuffers(window);



	vec3 eyePos = vec3(0.0, 0.0, 0.0);
	vec3 cameraTarget = vec3(0.0, 0.0, 0.0);
	vec3 eyeDir;
	vec3 upDir(0.0, 1.0, 0.0);
	vec3 rightDir;

	// ���رյ�ʱ��ͱ��ִ��ڿ���
	while (!glfwWindowShouldClose(window)) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		//glm::mat4 trans = glm::mat4(1.0f);
		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		

		//for (int i = 0; i < 4; i++) {
		//	for (int j = 0; j < 4; j++) {
		//		cout << trans[i][j] << " ";
		//	}
		//	cout << endl;
		//}

		mat4 model = mat4(1.0f);
		eyePos = vec3(keyPressedData['D'] - keyPressedData['A'], 0.0, keyPressedData['W'] - keyPressedData['S']);
		mat4 view = glm::lookAt(eyePos, cameraTarget, upDir);
		//view = mat4(1.0f);
		//eyeDir = glm::normalize(cameraTarget - eyePos);
		//rightDir = glm::cross(eyeDir, upDir);
		mat4 projection = mat4(1.0f);
		

		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "mvp");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection*view*model));

		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		if (keyPressedData['A']) {

		}
		glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, vertices.size() / vertexSize);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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