#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//��������
float vertices[] = {
	-0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
	0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
	0.0f,0.5f,0.0f,0.0f,0.0f,1.0f,
	//-0.5f,-0.5f,0.0f,
	//0.5f,-0.5f,0.0f,
	0.8f,-0.8f,0.0f,1.0f,0.0f,1.0f,
};

unsigned int indices[] = {
	0,1,2,
	0,1,3
};

//Vertex Shader
const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 6) in vec3 aColor;\n"
"out vec4 vertexColor;\n"
"void main(){\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	vertexColor= vec4(aColor.x,aColor.y,aColor.z,1.0);\n"
"}\n";

//Fragment Shader
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"uniform vec4 myColor;\n"
"void main(){\n"
"	FragColor = vec4(vertexColor.x,vertexColor.y,vertexColor.z,vertexColor.w);}\n";

// The MAIN function, from here we start the application and run the game loop
int main()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW ��ʼ��GLFW
	glfwInit();
	// Set all the required options for GLFW ����GLFW��Ҫ��ѡ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions ����һ������Ӧ��GLFW����ķ�����GLFW���ڶ���
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);//����opengl��Ⱦ���ڵĳߴ��С

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�߿�ģʽ
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);//����Ⱦ����

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//�󶨻ص�����

	//
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	////ʵ�������㻺�����
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//�����㻺�����󶨵�GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//�����ݸ��Ƶ���ǰ�󶨻���
	//
	unsigned int EBO;
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//����������ɫ��
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//����Ƭ����ɫ��
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//������ɫ������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(6);

	// Game loop ��Ϸѭ��
	while (!glfwWindowShouldClose(window))//��Ⱦѭ��
	{
		//����
		processInput(window);//��ÿһ֡�м��

		//״̬���ú���
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//��һ����ɫ�����Ļ
		//״̬ʹ�ú���
		glClear(GL_COLOR_BUFFER_BIT);//�����ɫ����

		// ��Ⱦָ��
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		float redValue= (cos(timeValue) / 2.0f) + 0.5f;
		float blueValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
		//��Ⲣ�����¼�
		glfwPollEvents();
		glfwSwapBuffers(window);//ÿһ֡���ƣ��������壩
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}
//�ص�������ÿ�����ڴ�С����ʱ������
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//����û��Ƿ񰴼�
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}