#pragma once
#include "Core\Init\Init_GLUT.h"
#include "Managers\SceneManager.h"

using namespace Core;

int main(int argc, char **argv)
{
	WindowInfo window(std::string("in2gpu OpenGL Beginner Tutorial "),
		400, 200,//position
		800, 600, //size
		true);//reshape

	ContextInfo context(4, 4, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);
	Init::Init_GLUT::init(window, context, frameBufferInfo);

	IListener* scene = new Managers::SceneManager();
	Init::Init_GLUT::setListener(scene);

	Init::Init_GLUT::run();

	delete scene;
	return 0;
}