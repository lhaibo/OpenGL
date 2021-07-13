#pragma once
#include <iostream>
#include "GLFW/glfw3.h"

struct RGBA
{
	float r;
	float g;
	float b;
	float alpha;
	RGBA()
	{
		this->r = 1;
		this->g = 1;
		this->b = 1;
		this->alpha = 1;
	}
	RGBA(float r,float g , float b , float alpha)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->alpha = alpha;
	}
};

class LWindow
{
public:
	LWindow(int width, int height);
	GLFWwindow* GetWindow();
	void SetScreenColor(RGBA color);
	void Frame();
private:
	GLFWwindow* window;
	int WIDTH;
	int	HEIGHT;
	RGBA m_screenColor;
};

