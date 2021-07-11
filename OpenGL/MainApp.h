#include <GLFW/glfw3.h>
#include <iostream>

class MainApp
{
public:
	void Init(int width,int height);	//��ʼ��
	void Update();	//��ѭ��
	void ProcessInput();	//��������
	void SetScreenColor(float r, float g, float b, float alpha);	//�趨��Ļ��ɫ

private:
	float r=0.2f, g=0.3f, b=0.3f, alpha=1.0f;
	int WIDTH;
	int	HEIGHT;
	GLFWwindow* window;
};

