#include "MainApp.h"

void MainApp::Init(int width,int height)
{
	WIDTH = width;
	HEIGHT = height;
	glfwInit();
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW ��ʼ��GLFW
	glfwInit();
	// Set all the required options for GLFW ����GLFW��Ҫ��ѡ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(window);
}

void MainApp::Update()
{
	while (!glfwWindowShouldClose(window))//��Ⱦѭ��
	{
		ProcessInput();

		//��Ⲣ�����¼�
		glfwPollEvents();
		glfwSwapBuffers(window);//ÿһ֡���ƣ��������壩
		glClearColor(r, g, b, alpha);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	glfwTerminate();
}

void MainApp::ProcessInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void MainApp::SetScreenColor(float r=0.2f, float g=0.3f, float b=0.3f, float alpha=1.0f)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->alpha = alpha;
}


