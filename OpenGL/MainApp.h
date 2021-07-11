#include <GLFW/glfw3.h>
#include <iostream>

class MainApp
{
public:
	void Init(int width,int height);	//初始化
	void Update();	//主循环
	void ProcessInput();	//处理输入
	void SetScreenColor(float r, float g, float b, float alpha);	//设定屏幕颜色

private:
	float r=0.2f, g=0.3f, b=0.3f, alpha=1.0f;
	int WIDTH;
	int	HEIGHT;
	GLFWwindow* window;
};

