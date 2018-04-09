#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <BasicEngine\Engine.h>
#include "GenericModel.h"
#include "Models\MeshStrip.h"
#include "ModelMakers\TreeMaker.h"
#include <thread>
#include "../../../Dependencies/include/glm/gtx/transform.hpp"


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
	int starCount = 150;
	int starSize = 100;

	for (unsigned i = 0; i < starCount; i++) {
		vector<vector<glm::vec3>> starVertexArrays = vector<vector<glm::vec3>>();

		//for (int i = 0; i < 2; i++) {
		vector<glm::vec3> starVertices = vector<glm::vec3>();

		int sx = -starRadius + GetRandom() * 2 * starRadius;
		int sz = -starRadius + GetRandom() * 2 * starRadius;
		//int sy = abs(sx) < 5000 && abs(sz) < 5000 ? 10000 + (GetRandom() * 0.5 * starRadius) : -2000 + GetRandom() * starRadius;
		int sy = -starRadius + GetRandom() * 2 * starRadius;;

		starVertices.push_back(glm::vec3(sx, sy, sz));
		starVertices.push_back(glm::vec3(sx + GetRandom() * starSize, sy + GetRandom() * starSize, sz + GetRandom() * starSize));
		starVertices.push_back(glm::vec3(sx + GetRandom() * starSize, sy + GetRandom() * starSize, sz + GetRandom() * starSize));

		starVertexArrays.push_back(starVertices);
		//}
		GenericModel* star = new GenericModel(starVertexArrays, GL_TRIANGLES, glm::vec4(1.0, 1.0, 1.0, 1.0));
		star->SetProgram(engine->getProgram("flatShader"));
		star->Create();
		string modelName = "star_" + std::to_string(i);

		engine->setModel(modelName, star);
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
		GenericModel* tree = new GenericModel(treeVertexArrays, glm::vec4(0.3, 0.3, 0.3, 0.9));
		tree->SetProgram(engine->getProgram("flatShader"));
		tree->toggleCollisionCheck(true);
		tree->Create();

		string modelName = "tree_" + std::to_string(i);
		engine->setModel(modelName, tree);
	}
	int thing = 1;
}

void makeTrees(Engine* engine) {

	// Constructs the new thread and runs it. Does not block execution.
	/*thread t1(makeSomeTrees, engine, 0, 10);
	thread t2(makeSomeTrees, engine, 10, 20);
	thread t3(makeSomeTrees, engine, 20, 30);*/

	TreeMaker treeMaker = ModelMakers::TreeMaker();
	makeSomeTrees(engine, 0, 15);

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

	GenericModel* pyramidModel = new GenericModel(pyramid, GL_TRIANGLE_STRIP, glm::vec4(0.7, 0.9, 0.2, 0.3));
	pyramidModel->SetProgram(engine->getProgram("flatShader"));
	pyramidModel->Create();
	string modelName = "pyramid_" + std::to_string(seedZ) + "_" + std::to_string(seedX);
	engine->setModel(modelName, pyramidModel);
}



void makeMesh(Engine* engine) {
	//MeshStrip* meshStrip = new MeshStrip();
	//meshStrip->SetProgram(engine->getProgram("flatShader"));
	//engine->setModel("meshStrip", meshStrip);
}

vector<Triangle> getCube(glm::vec3 min, glm::vec3 max) {
	std::vector<Triangle> cube = std::vector<Triangle>();

	// top = more y, right = more x, front = more z

	glm::vec3 TopRearLeft = glm::vec3(min.x, max.y, min.z);
	glm::vec3 TopRearRight = glm::vec3(max.x, max.y, min.z);
	glm::vec3 TopFrontRight = glm::vec3(max.x, max.y, max.z);
	glm::vec3 TopFrontLeft = glm::vec3(min.x, max.y, max.z);

	glm::vec3 BottomRearLeft = glm::vec3(min.x, min.y, min.z);
	glm::vec3 BottomRearRight = glm::vec3(max.x, min.y, min.z);
	glm::vec3 BottomFrontRight = glm::vec3(max.x, min.y, max.z);
	glm::vec3 BottomFrontLeft = glm::vec3(min.x, min.y, max.z);


	//in openGL standard winding order is counterclockwise

	//top
	cube.push_back(Triangle(TopRearLeft, TopFrontLeft, TopFrontRight));
	cube.push_back(Triangle(TopRearLeft, TopFrontRight, TopRearRight));

	//left
	cube.push_back(Triangle(TopRearLeft, BottomRearLeft, BottomFrontLeft));
	cube.push_back(Triangle(TopRearLeft, BottomFrontLeft, TopFrontLeft));

	//front
	cube.push_back(Triangle(TopFrontLeft, BottomFrontLeft, BottomFrontRight));
	cube.push_back(Triangle(TopFrontLeft, BottomFrontRight, TopFrontRight));

	//right
	cube.push_back(Triangle(TopFrontRight, BottomFrontRight, BottomRearRight));
	cube.push_back(Triangle(TopFrontRight, BottomRearRight, TopRearRight));

	//back
	cube.push_back(Triangle(TopRearLeft, BottomRearLeft, BottomRearRight));
	cube.push_back(Triangle(TopRearLeft, BottomRearRight, TopRearRight));

	//bottom
	cube.push_back(Triangle(BottomFrontLeft, BottomRearLeft, BottomRearRight));
	cube.push_back(Triangle(BottomFrontLeft, BottomRearRight, BottomFrontRight));

	return cube;
}

void makeFallingCube(Engine* engine) {
	std::vector<Triangle> cube = getCube(glm::vec3(-200, 0, -200), glm::vec3(200, 400, 200));
	std::vector<std::vector<glm::vec3>> cubeVertices = std::vector<std::vector<glm::vec3>>();
	for (unsigned i = 0; i < cube.size(); i++) {
		cubeVertices.push_back(cube[i].getVertices());
	}

	GenericModel* cubeModel = new GenericModel(cubeVertices, GL_TRIANGLES, glm::vec4(0.2, 0.9, 0.9, 0.9));
	cubeModel->toggleCollisionCheck(true);
	cubeModel->SetProgram(engine->getProgram("flatShader"));
	
	cubeModel->makeMoveable();
	cubeModel->setInitialPositionMatrix(glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 150.0f, 600.0f, 1.0f));
	cubeModel->setEachFrameMoveMatrix(glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.6f, 0.0f, 1.0f));

	cubeModel->Create();

	BasicEngine::Monsters::Monster* cubeMonster = new BasicEngine::Monsters::Monster(cubeModel, new BasicEngine::Monsters::Mind());

	engine->setMonster("cube", cubeMonster);
}

void makeSecondCube(Engine* engine) {
	std::vector<Triangle> cube = getCube(glm::vec3(-200, 0, -200), glm::vec3(200, 400, 200));
	std::vector<std::vector<glm::vec3>> cubeVertices = std::vector<std::vector<glm::vec3>>();
	for (unsigned i = 0; i < cube.size(); i++) {
		cubeVertices.push_back(cube[i].getVertices());
	}

	GenericModel* cubeModel = new GenericModel(cubeVertices, GL_TRIANGLES, glm::vec4(0.2, 0.9, 0.9, 0.9));
	cubeModel->toggleCollisionCheck(true);
	cubeModel->SetProgram(engine->getProgram("flatShader"));

	cubeModel->makeMoveable();
	cubeModel->setInitialPositionMatrix(glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 600.0f, 600.0f, 1.0f));
	cubeModel->setEachFrameMoveMatrix(glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.9f, 0.0f, 1.0f));

	cubeModel->Create();

	engine->setModel("cube2", cubeModel);
}

void makeGround(Engine* engine) {
	std::vector<Triangle> ground = getCube(glm::vec3(-1000, -50, -1000), glm::vec3(1000, -40, 1000));
	std::vector<std::vector<glm::vec3>> groundVertices = std::vector<std::vector<glm::vec3>>();
	for (unsigned i = 0; i < ground.size(); i++) {
		groundVertices.push_back(ground[i].getVertices());
	}

	GenericModel* groundModel = new GenericModel(groundVertices, GL_TRIANGLES, glm::vec4(0.6, 0.2, 0.8, 0.3));
	groundModel->toggleCollisionCheck(true);
	groundModel->SetProgram(engine->getProgram("flatShader"));
	groundModel->Create();

	engine->setModel("ground", groundModel);
}

int main(int argc, char **argv)
{
	Engine* engine = new Engine();

	engine->Init();

	//local shaders
	engine->createProgram("flatShader",
		"Shaders\\CubeVertexShader.glsl",
		"Shaders\\CubeFragmentShader.glsl");

	engine->createProgram("genericWithLighting",
		"Shaders\\GenericLightedVertexShader.glsl",
		"Shaders\\GenericLightedFragmentShader.glsl");

	// vector<GenericModel*> stars = makeStars(engine);
	//makeTrees(engine);
	//makePyramid(0, 0, engine);
	//makePyramid(-1020, 0, 1000, engine);
	//makePyramid(20, 20, 10000, engine);
	//makePyramid(-100, -100, 70, engine);
	// makePyramid(0, 0, 1000, engine);
	makeGround(engine);
	makeFallingCube(engine);
	makeSecondCube(engine);
	//makeMesh(engine);



	engine->Run();

	delete engine;
	return 0;
}