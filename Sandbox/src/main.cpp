#include <LampEngine.h>

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define LE LampEngine

int main()
{ 
	LE::Application app("LampEngine", 1200, 720);
	LE::Scene mainScene("MainScene", app);
	LE::Object testObject("TestObject", app, &mainScene.getRoot());
	
	app.setCurrentScene(mainScene);
	while (app.isRunning()) {
		app.update();
	}
	app.close();

	return 0;
}