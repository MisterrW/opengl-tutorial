#pragma once
#include <BasicEngine\Engine.h>
#include "GenericModel.h"

using namespace BasicEngine;

float GetRandom() {
	return (std::rand() % 10) / 10.0;
}

void makeStars(Engine* engine) {
	int starRadius = 1000;
	int starCount = 10000;
	int starSize = 10;

	for (unsigned i = 0; i < starCount; i++) {
		vector<glm::vec3> starVertices = vector<glm::vec3>();

		int sx = -starRadius + GetRandom() * 2 * starRadius;
		int sy = -starRadius + GetRandom() * 2 * starRadius;
		int sz = -starRadius + GetRandom() * 2 * starRadius;

		starVertices.push_back(glm::vec3(sx, sy, sz));
		starVertices.push_back(glm::vec3(sx + GetRandom() * starSize, sy + GetRandom() * starSize, sz + GetRandom() * starSize));
		starVertices.push_back(glm::vec3(sx + GetRandom() * starSize, sy + GetRandom() * starSize, sz + GetRandom() * starSize));

		GenericModel* star = new GenericModel(starVertices);
		star->SetProgram(engine->GetShader_Manager()->GetProgram("cubeShader"));
		star->Create();

		engine->GetModels_Manager()->SetModel("star" + i, star);
	}
}

int main(int argc, char **argv)
{
	Engine* engine = new Engine();
	engine->Init();

	//local shaders
	engine->GetShader_Manager()->CreateProgram("cubeShader",
		"Shaders\\CubeVertexShader.glsl",
		"Shaders\\CubeFragmentShader.glsl");

	makeStars(engine);

	engine->Run();

	delete engine;
	return 0;
}