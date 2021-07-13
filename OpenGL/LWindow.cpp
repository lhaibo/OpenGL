#include "LWindow.h"

LWindow::LWindow(int width,int height)
{
	WIDTH = width;
	HEIGHT = height;
	glfwInit();
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW 初始化GLFW
	glfwInit();
	// Set all the required options for GLFW 设置GLFW需要的选项
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
	//检测并调用事件
	glfwPollEvents();
	glfwSwapBuffers(window);//每一帧绘制（交换缓冲）
	glClearColor(m_screenColor.r, m_screenColor.g, m_screenColor.b, m_screenColor.alpha);
	glClear(GL_COLOR_BUFFER_BIT);
	
}
