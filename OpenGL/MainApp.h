#include <GLFW/glfw3.h>
#include <iostream>
#include "LWindow.h"
class MainApp
{
public:
	void Init(int width,int height);	//初始化
	void Update();	//主循环
	void ProcessInput(LWindow* window);	//处理输入
private:
	LWindow* window;
};

