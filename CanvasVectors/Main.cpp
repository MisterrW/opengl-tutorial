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
		star->SetProgram(engine->getProgram("cubeShader"));
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
		GenericModel* tree = new GenericModel(treeVertexArrays);
		tree->SetProgram(engine->getProgram("genericWithLighting"));
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
	pyramidModel->SetProgram(engine->getProgram("genericWithLighting"));
	pyramidModel->Create();
	string modelName = "pyramid_" + std::to_string(seedZ) + "_" + std::to_string(seedX);
	engine->setModel(modelName, pyramidModel);
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
	groundModel->toggleCollisionCheck(true);
	groundModel->SetProgram(engine->getProgram("genericWithLighting"));
	groundModel->Create();

	engine->setModel("ground", groundModel);
}

void makeMesh(Engine* engine) {
	//MeshStrip* meshStrip = new MeshStrip();
	//meshStrip->SetProgram(engine->getProgram("cubeShader"));
	//engine->setModel("meshStrip", meshStrip);
}

double getAngleBetween(glm::vec3 a, glm::vec3 b) {
	// we also want the angle between the bb surface normal and the collision angle.

	// the angle between two vectors a and b in R3 is acos(a . b / ||a|| * ||b||) 
	// (the arc cosine of the dot product of a and b divided by the length of a and b multiplied together)

	// so:

	double multipliedLength = glm::length(a) * glm::length(b);
	double dotProduct = glm::dot(a, b);
	double cosAngle = dotProduct / multipliedLength;
	double angle = glm::acos(cosAngle);
	double angleDegsApprox = (angle / (3.141 * 2)) * 360;

	return angle;
}

glm::mat4 testCollisionDeflections() {
	// IMPORTANT handle linearly dependant vectors - if you hit something dead on, the angle to the normal is 180 degrees, 
	// so the cross product of the collision angle with the surface normal is undefined.
	// check for this and bail out - no deflection needed, we can just stop dead for a head on collision.


	//glm::mat4 oldMoveMatrix = glm::mat4(1, 0, 0, 0,
	//	0, 1, 0, 0,
	//	0, 0, 1, 0,
	//	-2, -11, 0, 1);

	//glm::mat4 newMoveMatrix = glm::mat4(1, 0, 0, 0,
	//	0, 1, 0, 0,
	//	0, 0, 1, 0,
	//	-1, -9, 0, 1);


	glm::mat4 oldMoveMatrix = glm::mat4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		3, -3, -5, 1);

	glm::mat4 newMoveMatrix = glm::mat4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0.1, 50, 5, 1);

	vector<glm::vec3> boundingBox;
	//the top surface of a bounding box aligned to world axes
	boundingBox.push_back(glm::vec3(0, 10, 0));
	boundingBox.push_back(glm::vec3(10, 10, 0));
	boundingBox.push_back(glm::vec3(0, 10, 10));
	boundingBox.push_back(glm::vec3(10, 10, 10));

	glm::vec3 relative1 = (boundingBox[2] - boundingBox[0]);
	glm::vec3 relative2 = (boundingBox[1] - boundingBox[0]);

	// see the matrix expression of cross product at
	// https://en.wikipedia.org/wiki/Cross_product#Conversion_to_matrix_multiplication

	//doing this to get relative vectors to get a sensible cross
	glm::vec3 cross = glm::cross(relative1, relative2);
	glm::vec3 normal = glm::normalize(cross);

	// a vector representing the change represented by the difference between the old and new matrices
	// by multiplying the zero vector by the inverse of each matrix
	// and then subtracting the old one from the new one

	glm::vec4 origin = glm::vec4(0, 0, 0, 1);
	glm::mat4 oldInv = glm::inverse(oldMoveMatrix);
	glm::mat4 newInv = glm::inverse(newMoveMatrix);
	// console.log(oldInv);
	glm::vec3 oldPos = glm::vec3(oldInv * origin);
	glm::vec3 newPos = glm::vec3(newInv * origin);

	glm::vec3 result = newPos - oldPos;

	// now we want to find the normal of the bounding box's normal and the angle of collision, 
	// because it is the angle we need to rotate around to get the vector we want (the one at 90 degrees to the bounding box surface normal, ie in the plane of the BB).
	// (in this example it wil be along the z axis)
	// in fact, when we do this properly the maths might be easier if we rotate this normal to lie on the z axis
	// don't know whether to normalise the movement vector
	// CV = collision vector, BBSN = bounding box normal

    glm::vec3 normalCVandBBSN = glm::normalize(glm::cross(normal, result));

	double angleFromNormal = getAngleBetween(normal, result);
	//float angleFromNormalDegrees = glm::degrees(float(angleFromNormal));
	//float angleFromPlaneDegrees = angleFromNormal - 90; // 

	float angleFromPlane = angleFromNormal - glm::radians(90.0);

	// OK, we have the angle of our vector with the normal. Now we need to reduce that angle until we have a vector orthogonal to the normal.
	// courtesy of https://math.stackexchange.com/questions/80414/increasing-the-angle-between-two-vectors:
	// decompose into the parts parallel and orthogonal to the normal (parPart is a projection of col onto norm, orthPart is the rest)

	// glm::vec3 parallelPart = (glm::dot(result, normal) / (glm::length(normal) * glm::length(normal))) * normal;
	// glm::vec3 orthogonalPart = result - parallelPart; // this is what we want.

	// but we actually want a rotation matrix which represents reducing the angle to the normal to 90 degrees. 
	// GLM has a rotation function which we can use with the normal we figured out earlier 

	glm::mat4 deflectionMatrix = glm::rotate((angleFromPlane), normalCVandBBSN);
    glm::vec3 deflected = glm::vec3(deflectionMatrix * glm::vec4(result, 1));

	glm::mat4 deflectedMovementMatrix = deflectionMatrix * newMoveMatrix;

	return deflectedMovementMatrix;
}

int main(int argc, char **argv)
{
	Engine* engine = new Engine();

	testCollisionDeflections();

	engine->Init();

	//local shaders
	engine->createProgram("cubeShader",
		"Shaders\\CubeVertexShader.glsl",
		"Shaders\\CubeFragmentShader.glsl");

	engine->createProgram("genericWithLighting",
		"Shaders\\GenericLightedVertexShader.glsl",
		"Shaders\\GenericLightedFragmentShader.glsl");

	vector<GenericModel*> stars = makeStars(engine);
	makeTrees(engine);
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