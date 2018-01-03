#pragma once
#include <BasicEngine\Engine.h>
#include "GenericModel.h"
#include "ModelMakers\TreeMaker.h"

using namespace BasicEngine;
using namespace ModelMakers;

float GetRandom() {
	return (std::rand() / float(RAND_MAX));
}

void makeStars(Engine* engine) {

	vector<vector<glm::vec3>> starVertexArrays = vector<vector<glm::vec3>>();

	vector<glm::vec3> starVertices = vector<glm::vec3>();

	starVertices.push_back(glm::vec3(0, 10, 0));
	starVertices.push_back(glm::vec3(-20, -20, 20));
	starVertices.push_back(glm::vec3(0, -20, 0));

	starVertexArrays.push_back(starVertices);
	//}
	GenericModel* star = new GenericModel(starVertexArrays, GL_TRIANGLES);
	star->SetProgram(engine->GetShader_Manager()->GetProgram("cubeShader"));
	star->Create();

	engine->GetModels_Manager()->SetModel("star", star);


	int starRadius = 500;
	int starCount = 5000;
	int starSize = 2;

	//for (unsigned i = 0; i < starCount; i++) {
	//	vector<vector<glm::vec3>> starVertexArrays = vector<vector<glm::vec3>>();

	//	//for (int i = 0; i < 2; i++) {
	//		vector<glm::vec3> starVertices = vector<glm::vec3>();

	//		int sx = -starRadius + GetRandom() * 2 * starRadius;
	//		int sy = -starRadius + GetRandom() * 2 * starRadius;
	//		int sz = -starRadius + GetRandom() * 2 * starRadius;

	//		starVertices.push_back(glm::vec3(sx, sy, sz));
	//		starVertices.push_back(glm::vec3(sx + GetRandom() * starSize, sy + GetRandom() * starSize, sz + GetRandom() * starSize));
	//		starVertices.push_back(glm::vec3(sx + GetRandom() * starSize, sy + GetRandom() * starSize, sz + GetRandom() * starSize));

	//		starVertexArrays.push_back(starVertices);
	//	//}
	//	GenericModel* star = new GenericModel(starVertexArrays, GL_TRIANGLES);
	//	star->SetProgram(engine->GetShader_Manager()->GetProgram("cubeShader"));
	//	star->Create();

	//	engine->GetModels_Manager()->SetModel("star" + i, star);
	//}
}

void makeTrees(Engine* engine) {
	TreeMaker treeMaker = ModelMakers::TreeMaker();
	for (int i = 0; i < 10; i++) {

		float randX = GetRandom();
		float randZ = GetRandom();

		float x = -100 + (randX * 200);
		float y = -20;
		float z = -100 + (randZ * 200);


		glm::vec3 seed = glm::vec3(x, y, z);
		vector<vector<glm::vec3>> treeVertexArrays = treeMaker.GetTree(seed);
		GenericModel* tree = new GenericModel(treeVertexArrays);
		tree->SetProgram(engine->GetShader_Manager()->GetProgram("genericWithLighting"));
		tree->Create();

		engine->GetModels_Manager()->SetModel("tree" + i, tree);
	}
}

void makeGround(Engine* engine) {
	vector<vector<glm::vec3>> ground;

	ground.push_back(vector<glm::vec3>());

	// right - counter-clockwise (from above)
	//ground[0].push_back(glm::vec3(-200, -20, -200));
	//ground[0].push_back(glm::vec3(200, -20, -200));
	//ground[0].push_back(glm::vec3(-200, -20, 200));
	//ground[0].push_back(glm::vec3(200, -20, 200));


	/*

	ground.push_back(vector<glm::vec3>());
	ground.push_back(vector<glm::vec3>());

	// right - counter-clockwise (from above)
	ground[0].push_back(glm::vec3(-200, -20, -200));
	ground[0].push_back(glm::vec3(200, -20, -200));
	ground[0].push_back(glm::vec3(-200, -20, 200));

	ground[1].push_back(glm::vec3(-200, -20, 200));
	ground[1].push_back(glm::vec3(200, -20, -200));
	ground[1].push_back(glm::vec3(200, -20, 200));

	// wrong - clockwise (from above)
	//ground[0].push_back(glm::vec3(-200, -20, -200));
	//ground[0].push_back(glm::vec3(-200, -20, 200));
	//ground[0].push_back(glm::vec3(200, -20, -200));

	*/

	int x = -200;
	int y = -20;
	int z = -200;

	for (int i = 0; i < 20; i++) {
		z = -200;
		for (int j = 0; j < 20; j++) {
			ground[0].push_back(glm::vec3(x, y, z));
			ground[0].push_back(glm::vec3(x + 20, y, z));
			ground[0].push_back(glm::vec3(x, y, z + 20));
			ground[0].push_back(glm::vec3(x + 20, y, z + 20));
			z += 20;
		}
		x += 20;
	}

	GenericModel* groundModel = new GenericModel(ground, GL_TRIANGLE_STRIP);
	groundModel->SetProgram(engine->GetShader_Manager()->GetProgram("genericWithLighting"));
	groundModel->Create();

	engine->GetModels_Manager()->SetModel("ground", groundModel);
}


int main(int argc, char **argv)
{
	Engine* engine = new Engine();
	engine->Init();

	//local shaders
	engine->GetShader_Manager()->CreateProgram("cubeShader",
		"Shaders\\CubeVertexShader.glsl",
		"Shaders\\CubeFragmentShader.glsl");

	engine->GetShader_Manager()->CreateProgram("genericWithLighting", 
		"Shaders\\GenericLightedVertexShader.glsl",
		"Shaders\\GenericLightedFragmentShader.glsl");

	makeStars(engine);
	makeTrees(engine);
	makeGround(engine);

	engine->Run();

	delete engine;
	return 0;
}