#pragma once
#include <BasicEngine\Engine.h>
#include "GenericModel.h"
#include "Models\MeshStrip.h"
#include "ModelMakers\TreeMaker.h"
#include <thread>

using namespace BasicEngine;
using namespace ModelMakers;
using namespace LocalModels;

float GetRandom() {
	return (std::rand() / float(RAND_MAX));
}

vector<GenericModel*> makeStars(Engine* engine) {
	vector<GenericModel*> stars = vector<GenericModel*>();

	int starRadius = 20000;
	//int starCount = 50000;
	int starCount = 1000;
	int starSize = 50;

	for (unsigned i = 0; i < starCount; i++) {
		vector<vector<glm::vec3>> starVertexArrays = vector<vector<glm::vec3>>();

		//for (int i = 0; i < 2; i++) {
			vector<glm::vec3> starVertices = vector<glm::vec3>();

			int sx = -starRadius + GetRandom() * 2 * starRadius;
			int sz = -starRadius + GetRandom() * 2 * starRadius;
			int sy = abs(sx) < 10000 && abs(sz) < 10000 ? 10000 + (GetRandom() * 0.5 * starRadius) : -2000 + GetRandom() * starRadius;

			starVertices.push_back(glm::vec3(sx, sy, sz));
			starVertices.push_back(glm::vec3(sx + GetRandom() * starSize, sy + GetRandom() * starSize, sz + GetRandom() * starSize));
			starVertices.push_back(glm::vec3(sx + GetRandom() * starSize, sy + GetRandom() * starSize, sz + GetRandom() * starSize));

			starVertexArrays.push_back(starVertices);
		//}
		GenericModel* star = new GenericModel(starVertexArrays, GL_TRIANGLES);
		star->SetProgram(engine->GetShader_Manager()->GetProgram("cubeShader"));
		star->Create();
		string modelName = "star_" + std::to_string(i);

		engine->GetModels_Manager()->setModel(modelName, star);
		stars.push_back(star);
		
	}
	return stars;
}

void makeSomeTrees(Engine* engine, int i_min, int i_max) {
	TreeMaker treeMaker = ModelMakers::TreeMaker();
	vector<GenericModel*> trees = vector<GenericModel*>();
	for (int i = i_min; i < i_max; i++) {

		float randX = GetRandom();
		float randZ = GetRandom();

		float x = -400 + (randX * 500);
		float y = -4;
		float z = -400 + (randZ * 500);


		glm::vec3 seed = glm::vec3(x, y, z);
		vector<vector<glm::vec3>> treeVertexArrays = treeMaker.GetTree(seed);
		GenericModel* tree = new GenericModel(treeVertexArrays);
		tree->SetProgram(engine->GetShader_Manager()->GetProgram("genericWithLighting"));
		tree->Create();

		engine->GetModels_Manager()->setModel("tree" + i, tree);
	}
	int thing = 1;
}

void makeTrees(Engine* engine) {
	
	// Constructs the new thread and runs it. Does not block execution.
	/*thread t1(makeSomeTrees, engine, 0, 10);
	thread t2(makeSomeTrees, engine, 10, 20);
	thread t3(makeSomeTrees, engine, 20, 30);*/

	TreeMaker treeMaker = ModelMakers::TreeMaker();
	makeSomeTrees(engine, 375, 500);

	// Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
	//t1.join();
	//t2.join();
	//t3.join();



	int trees = 1;
}

void makePyramid(int seedX, int seedZ, float baseLength, Engine* engine) {
	vector<vector<glm::vec3>> pyramid;

	pyramid.push_back(vector<glm::vec3>());

	int x = seedX;
	int y = -20;
	int z = seedZ;

	int x_offset = 0 - seedX;
	int z_offset = 0 - seedZ;
	int max_x = baseLength;
	int max_z = baseLength;
	int half_x = baseLength / 2;
	int half_z = baseLength / 2;

	float baseLength_over_200 = baseLength / 200;
	float baseLength_over_100 = baseLength / 100;
	float baseLength_over_50 = baseLength / 50;

	int XHeight;
	int ZHeight;
	float YHeight;

	for (int i = 0; i < 200; i++) {
		bool evens = i % 2 == 0;

		z = evens ? seedZ : seedZ + baseLength;

		for (int j = 0; j < 200; j++) {
			XHeight = half_x - abs((x + x_offset) - half_x);
			ZHeight = half_z - abs((z + z_offset) - half_z);
			YHeight = (XHeight * ZHeight) * (baseLength * 2) / (max_x * max_z);

			y = YHeight;
			pyramid[0].push_back(glm::vec3(x, y, z));
			y = -(baseLength_over_200)+int(GetRandom() * (baseLength_over_100)) + YHeight;
			pyramid[0].push_back(glm::vec3(x + (baseLength_over_50), y, z));
			y = -(baseLength_over_200)+int(GetRandom() * (baseLength_over_100)) + YHeight;
			pyramid[0].push_back(glm::vec3(x, y, z + (baseLength_over_50)));
			y = -(baseLength_over_200)+int(GetRandom() * (baseLength_over_100)) + YHeight;
			pyramid[0].push_back(glm::vec3(x + (baseLength_over_50), y, z + (baseLength_over_50)));
			if (evens) {
				z += (baseLength_over_200);
			}
			else {
				z -= (baseLength_over_200);
			}
		}
		x += (baseLength / 200);
	}

	GenericModel* pyramidModel = new GenericModel(pyramid, GL_TRIANGLE_STRIP);
	pyramidModel->SetProgram(engine->GetShader_Manager()->GetProgram("genericWithLighting"));
	pyramidModel->Create();
	string modelName = "pyramid_" + std::to_string(seedZ) + "_" + std::to_string(seedX);
	engine->GetModels_Manager()->setModel(modelName, pyramidModel);
}

void makeGround(Engine* engine) {
	vector<vector<glm::vec3>> ground;

	ground.push_back(vector<glm::vec3>());

	int x = -2000;
	int y = -20;
	int z = -2000;

	for (int i = 0; i < 500; i++) {
		z = -2000;
		for (int j = 0; j < 500; j++) {

			ground[0].push_back(glm::vec3(x, y, z));
			y = -5 + int(GetRandom() * 10);
			ground[0].push_back(glm::vec3(x + 50, y, z));
			y = -5 + int(GetRandom() * 10);
			ground[0].push_back(glm::vec3(x, y, z + 50));
			y = -5 + int(GetRandom() * 10);
			ground[0].push_back(glm::vec3(x + 50, y, z + 50));
			z += 40;
		}
		x += 40;
	}

	GenericModel* groundModel = new GenericModel(ground, GL_TRIANGLE_STRIP);
	groundModel->SetProgram(engine->GetShader_Manager()->GetProgram("genericWithLighting"));
	groundModel->Create();

	engine->GetModels_Manager()->setModel("ground", groundModel);
}

void makeMesh(Engine* engine) {
	MeshStrip* meshStrip = new MeshStrip();
	meshStrip->SetProgram(engine->GetShader_Manager()->GetProgram("cubeShader"));
	engine->GetModels_Manager()->setModel("meshStrip", meshStrip);
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

	//vector<GenericModel*> stars = makeStars(engine);
	//makeTrees(engine);
	//makePyramid(0, 0, engine);
	//makePyramid(-1020, 0, 1000, engine);
	//makePyramid(20, 20, 10000, engine);
	//makePyramid(-100, -100, 70, engine);
	// makePyramid(0, 0, 1000, engine);
	makeGround(engine);

	//makeMesh(engine);

   

	engine->Run();

	delete engine;
	return 0;
}