#pragma once
#include <BasicEngine\Engine.h>
#include "GenericModel.h"
#include "ModelMakers\TreeMaker.h"

using namespace BasicEngine;
using namespace ModelMakers;

float GetRandom() {
	return (std::rand() / float(RAND_MAX));
}

vector<GenericModel*> makeStars(Engine* engine) {
	vector<GenericModel*> stars = vector<GenericModel*>();

	int starRadius = 2000;
	int starCount = 5000;
	int starSize = 5;

	for (unsigned i = 0; i < starCount; i++) {
		vector<vector<glm::vec3>> starVertexArrays = vector<vector<glm::vec3>>();

		//for (int i = 0; i < 2; i++) {
			vector<glm::vec3> starVertices = vector<glm::vec3>();

			int sx = -starRadius + GetRandom() * 2 * starRadius;
			int sy = 600 + GetRandom() * 0.2 * starRadius;
			int sz = -starRadius + GetRandom() * 2 * starRadius;

			starVertices.push_back(glm::vec3(sx, sy, sz));
			starVertices.push_back(glm::vec3(sx + GetRandom() * starSize, sy + GetRandom() * starSize, sz + GetRandom() * starSize));
			starVertices.push_back(glm::vec3(sx + GetRandom() * starSize, sy + GetRandom() * starSize, sz + GetRandom() * starSize));

			starVertexArrays.push_back(starVertices);
		//}
		GenericModel* star = new GenericModel(starVertexArrays, GL_TRIANGLES);
		star->SetProgram(engine->GetShader_Manager()->GetProgram("cubeShader"));
		star->Create();

		engine->GetModels_Manager()->SetModel("star" + i, star);
		stars.push_back(star);
		
	}
	return stars;
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

void makePyramid(Engine* engine) {
	vector<vector<glm::vec3>> ground;

	ground.push_back(vector<glm::vec3>());

	int x = 0;
	int y = -20;
	int z = 0;

	int max_x = 1000;
	int max_z = 1000;
	int half_x = 500;
	int half_z = 500;
	int XHeight;
	int ZHeight;
	float YHeight;

	vector<int> absols = vector<int>();

	for (int i = 0; i < 200; i++) {
		z = 0;
		for (int j = 0; j < 200; j++) {
			XHeight = (half_x - abs(x - (half_x)));
			ZHeight = (half_z - abs(z - (half_z)));
			YHeight = (XHeight * ZHeight) * 1000 / (max_x * max_z);

			y = YHeight;
				ground[0].push_back(glm::vec3(x, y, z));
				y = -5 + (GetRandom() * 10) + YHeight;
				ground[0].push_back(glm::vec3(x + 20, y, z));
				y = -5 + (GetRandom() * 10) + YHeight;
				ground[0].push_back(glm::vec3(x, y, z + 20));
				y = -5 + (GetRandom() * 10) + YHeight;
				ground[0].push_back(glm::vec3(x + 20, y, z + 20));
				z += 5;
		}
		x += 5;
	}

	GenericModel* groundModel = new GenericModel(ground, GL_TRIANGLE_STRIP);
	groundModel->SetProgram(engine->GetShader_Manager()->GetProgram("genericWithLighting"));
	groundModel->Create();

	engine->GetModels_Manager()->SetModel("pyramid", groundModel);
}

void makeGround(Engine* engine) {
	vector<vector<glm::vec3>> ground;

	ground.push_back(vector<glm::vec3>());

	int x = -2000;
	int y = -20;
	int z = -2000;

	vector<int> absols = vector<int>();

	for (int i = 0; i < 500; i++) {
		z = -2000;
		for (int j = 0; j < 500; j++) {

			ground[0].push_back(glm::vec3(x, y, z));
			y = -5 + (GetRandom() * 10);
			ground[0].push_back(glm::vec3(x + 50, y, z));
			y = -5 + (GetRandom() * 10);
			ground[0].push_back(glm::vec3(x, y, z + 50));
			y = -5 + (GetRandom() * 10);
			ground[0].push_back(glm::vec3(x + 50, y, z + 50));
			z += 40;
		}
		x += 40;
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

	vector<GenericModel*> stars = makeStars(engine);
	makeTrees(engine);
	makePyramid(engine);
	makeGround(engine);

	engine->Run();

	delete engine;
	return 0;
}