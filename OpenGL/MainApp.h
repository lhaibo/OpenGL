#include <GLFW/glfw3.h>
#include <iostream>
#include "LWindow.h"
class MainApp
{
public:
	void Init(int width,int height);	//��ʼ��
	void Update();	//��ѭ��
	void ProcessInput(LWindow* window);	//��������
private:
	LWindow* window;
};

