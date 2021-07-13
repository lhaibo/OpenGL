#include "MainApp.h"

void MainApp::Init(int width,int height)
{
	window = new LWindow(width, height);
	window->SetScreenColor(RGBA(0.2f, 0.3f, 0.3f, 1.0f));
}

void MainApp::Update()
{
	while (!glfwWindowShouldClose(window->GetWindow()))//äÖÈ¾Ñ­»·
	{
		ProcessInput(window);
		window->Frame();
	}
	glfwTerminate();
	
}

void MainApp::ProcessInput(LWindow* window)
{
	if (glfwGetKey(window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window->GetWindow(), true);
}



