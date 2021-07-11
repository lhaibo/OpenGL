#include "MainApp.h"

int main()
{
	std::cout << "GameEngine run" << std::endl;

	MainApp* mainApp = new MainApp();
	mainApp->Init(1280,720);
	mainApp->Update();
	return 0;
}