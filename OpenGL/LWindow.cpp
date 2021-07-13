#include "LWindow.h"

LWindow::LWindow(int width,int height)
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
		return;
	}
	glfwMakeContextCurrent(window);
}

GLFWwindow* LWindow::GetWindow()
{
	return window;
}

void LWindow::SetScreenColor(RGBA color)
{
	m_screenColor = color;
}

void LWindow::Frame()
{
	//��Ⲣ�����¼�
	glfwPollEvents();
	glfwSwapBuffers(window);//ÿһ֡���ƣ��������壩
	glClearColor(m_screenColor.r, m_screenColor.g, m_screenColor.b, m_screenColor.alpha);
	glClear(GL_COLOR_BUFFER_BIT);
	
}
