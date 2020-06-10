#include <iostream>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
		 // positions          // colors           // texture coords (UV)
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = {
	0,1,2,
	0,2,3
};

//�任����
glm::mat4 trans;

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
	int WIDTH, HEIGHT;
	glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
	glViewport(0, 0, WIDTH, HEIGHT);//����opengl��Ⱦ���ڵĳߴ��С

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

	//Shader
	Shader* myShader = new Shader("vertexSource.txt","fragmentSource.txt");
	
	unsigned int textureBufferA;
	glGenTextures(1, &textureBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureBufferA);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("load image failed!\n");
	}
	stbi_image_free(data);

	unsigned int textureBufferB;
	glGenTextures(1, &textureBufferB);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureBufferB);
	unsigned char* data2 = stbi_load("awesomeface.jpg", &width, &height, &nrChannel, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("load image failed!\n");
	}
	stbi_image_free(data2);
#pragma region Shader
	////����������ɫ��
//unsigned int vertexShader;
//vertexShader = glCreateShader(GL_VERTEX_SHADER);
//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//glCompileShader(vertexShader);

////����Ƭ����ɫ��
//unsigned int fragmentShader;
//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//glCompileShader(fragmentShader);

////������ɫ������
//unsigned int shaderProgram;
//shaderProgram = glCreateProgram();
//glAttachShader(shaderProgram, vertexShader);
//glAttachShader(shaderProgram, fragmentShader);
//glLinkProgram(shaderProgram);  
#pragma endregion

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(6);

	glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(7);

	
	//unsigned int transformLoc = glGetUniformLocation(myShader->id, "transform");
	
	trans = glm::mat4(1.0f);

	glm::mat4 modelMat=glm::mat4(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0, 0));
	
	glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));

	glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


	// Game loop ��Ϸѭ��
	while (!glfwWindowShouldClose(window))//��Ⱦѭ��
	{
		//����
		processInput(window);//��ÿһ֡�м��

		//״̬���ú���
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//��һ����ɫ�����Ļ
		//״̬ʹ�ú���
		glClear(GL_COLOR_BUFFER_BIT);//�����ɫ����

		//
		//glBindTexture(GL_TEXTURE_2D, textureBufferA);

		// ��Ⱦָ��
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//float redValue= (cos(timeValue) / 2.0f) + 0.5f;
		//float blueValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
		//glUseProgram(shaderProgram);
		//glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
		
		//shader->use()
		myShader->use();

		glUniform1i(glGetUniformLocation(myShader->id, "ourTexture"),0);
		glUniform1i(glGetUniformLocation(myShader->id, "ourFace"),3);
		//trans = glm::translate(trans, glm::vec3(-0.01f, 0, 0));
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glUniformMatrix4fv(glGetUniformLocation(myShader->id, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->id, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->id, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->id, "trans"), 1, GL_FALSE, glm::value_ptr(trans));

		
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
	if (glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
	{
		trans = glm::translate(trans, glm::vec3(-0.01f, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		trans = glm::translate(trans, glm::vec3(0.01f, 0, 0));
	}
}