#pragma once
#include <BasicEngine\Engine.h>
#include "Cube.h"

using namespace BasicEngine;
int main(int argc, char **argv)
{
	Engine* engine = new Engine();
	engine->Init();

	//local shaders
	engine->GetShader_Manager()->CreateProgram("cubeShader",
		"Shaders\\CubeVertexShader.glsl",
		"Shaders\\CubeFragmentShader.glsl");

	Cube* cube = new Cube();
	cube->SetProgram(engine->GetShader_Manager()->GetProgram("cubeShader"));
	cube->Create();

	engine->GetModels_Manager()->SetModel("cube", cube);

	engine->Run();

	delete engine;
	return 0;
}