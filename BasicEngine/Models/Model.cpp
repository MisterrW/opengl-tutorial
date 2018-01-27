#include "Model.h"
using namespace BasicEngine::Models;

/*====
Defines a bounding box aligned to world axes which contains all points in the model
Also defines normals for all 6 planes of the box
====*/
std::vector<glm::vec3> Model::setBoundingBox(std::vector<std::vector<glm::vec3>> vertexArrays) {
	std::vector<glm::vec3> boundingBox = std::vector<glm::vec3>();

	glm::vec3 minXYZ = vertexArrays[0][0];
	glm::vec3 maxXYZ = vertexArrays[0][0];

	for (unsigned i = 0; i < vertexArrays.size(); i++) {
		for (unsigned y = 0; y < vertexArrays[i].size(); y++) {
			if (vertexArrays[i][y].x < minXYZ.x) {
				minXYZ.x = vertexArrays[i][y].x;
			}
			else if (vertexArrays[i][y].x > maxXYZ.x) {
				maxXYZ.x = vertexArrays[i][y].x;
			}
			if (vertexArrays[i][y].y < minXYZ.y) {
				minXYZ.y = vertexArrays[i][y].y;
			}
			else if (vertexArrays[i][y].y > maxXYZ.y) {
				maxXYZ.y = vertexArrays[i][y].y;
			}
			if (vertexArrays[i][y].z < minXYZ.z) {
				minXYZ.z = vertexArrays[i][y].z;
			}
			else if (vertexArrays[i][y].z > maxXYZ.z) {
				maxXYZ.z = vertexArrays[i][y].z;
			}
		}
	}

	boundingBox.push_back(minXYZ);
	boundingBox.push_back(maxXYZ);

	return boundingBox;
}

std::vector<Triangle> Model::setBoundingBoxTriangles(std::vector<glm::vec3> boundingBoxMinMax) {
	std::vector<Triangle> boundingBoxTriangles = std::vector<Triangle>();
	
	glm::vec3 min = boundingBoxMinMax[0];
	glm::vec3 max = boundingBoxMinMax[1];

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
	boundingBoxTriangles.push_back(Triangle(TopRearLeft, TopFrontLeft, TopFrontRight));
	boundingBoxTriangles.push_back(Triangle(TopRearLeft, TopFrontRight, TopRearRight));

	//left
	boundingBoxTriangles.push_back(Triangle(TopRearLeft, BottomRearLeft, BottomFrontLeft));
	boundingBoxTriangles.push_back(Triangle(TopRearLeft, BottomFrontLeft, TopFrontLeft));

	//front
	boundingBoxTriangles.push_back(Triangle(TopFrontLeft, BottomFrontLeft, BottomFrontRight));
	boundingBoxTriangles.push_back(Triangle(TopFrontLeft, BottomFrontRight, TopFrontRight));

	//right
	boundingBoxTriangles.push_back(Triangle(TopFrontRight, BottomFrontRight, BottomRearRight));
	boundingBoxTriangles.push_back(Triangle(TopFrontRight, BottomRearRight, TopRearRight));

	//back
	boundingBoxTriangles.push_back(Triangle(TopFrontLeft, BottomFrontLeft, BottomFrontRight));
	boundingBoxTriangles.push_back(Triangle(TopFrontLeft, BottomFrontRight, TopFrontRight));

	//bottom
	boundingBoxTriangles.push_back(Triangle(BottomFrontLeft, BottomRearLeft, BottomRearRight));
	boundingBoxTriangles.push_back(Triangle(BottomFrontLeft, BottomRearRight, BottomFrontRight));

	return boundingBoxTriangles;
}

std::vector<glm::vec3> Model::getBoundingBox() {
	std::vector<glm::vec3> worldspaceBounds = std::vector<glm::vec3>();
	for (unsigned i = 0; i < boundingBox.size(); i++) {
		worldspaceBounds.push_back(glm::vec3(newMoveMatrix * (glm::vec4(boundingBox[i], 1))));
	}
	return worldspaceBounds;
}


std::vector<Triangle> Model::getBoundingBoxTriangles() {

	std::vector<Triangle> worldspaceBoundingTriangles = std::vector<Triangle>();
	for (unsigned i = 0; i < boundingBoxTriangles.size(); i++) {
		std::vector<glm::vec3> oldVertices = boundingBoxTriangles[i].getVertices();
		std::vector<glm::vec3> newVertices = std::vector<glm::vec3>();
		for (unsigned j = 0; j < oldVertices.size(); j++) {
			newVertices.push_back(glm::vec3(newMoveMatrix * (glm::vec4(oldVertices[j], 1))));
		}
		Triangle newTriangle = Triangle(newVertices);
		worldspaceBoundingTriangles.push_back(newTriangle);
	}
	return worldspaceBoundingTriangles;
}

////////movement section

glm::mat4 Model::getThisFrameMoveMatrix() {
	return this->eachFrameMoveMatrix;
};
glm::mat4 Model::getOldMoveMatrix() {
	return this->oldMoveMatrix;
};
glm::mat4 Model::getNewMoveMatrix() {
	return this->newMoveMatrix;
};
void Model::setNewMoveMatrix(glm::mat4 newMoveMatrix) {
	this->oldMoveMatrix = this->newMoveMatrix;
	this->newMoveMatrix = newMoveMatrix;
};
void Model::setOldMoveMatrix(glm::mat4 oldMoveMatrix) {
	this->oldMoveMatrix = oldMoveMatrix;
};
void Model::setInitialPositionMatrix(glm::mat4 moveMatrix) {
	this->oldMoveMatrix = moveMatrix;
	this->newMoveMatrix = moveMatrix;
};

void Model::makeMoveable() {
	if (!this->canMove) {
		this->oldMoveMatrix = this->newMoveMatrix;
		this->eachFrameMoveMatrix = glm::mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		this->canMove = true;
	}
}

void Model::setEachFrameMoveMatrix(glm::mat4 moveMatrix) {
	this->eachFrameMoveMatrix = moveMatrix;
}


////////end movement section

Model::Model() {}

void Model::initialise(std::vector<std::vector<glm::vec3>> vertexArrays) {
	collisionCheck = false;
	boundingBox = setBoundingBox(vertexArrays);
	boundingBoxTriangles = setBoundingBoxTriangles(boundingBox);
	this->canMove = false;

	this->newMoveMatrix = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Model::Model(std::vector<std::vector<glm::vec3>> vertexArrays) {
	initialise(vertexArrays);
}

Model::Model(std::vector<std::vector<glm::vec3>> vertexArrays, bool canMove) {

	initialise(vertexArrays);

	if (canMove) {
		this->canMove = true;
		this->oldMoveMatrix = glm::mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		this->eachFrameMoveMatrix = glm::mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}
}

Model::~Model()
{
	Destroy();
}

void Model::toggleCollisionCheck(bool shouldCheck) {
	collisionCheck = shouldCheck;
}

bool Model::shouldCollisionCheck() {
	return collisionCheck;
}

void Model::Draw()
{
	// NDC
}

void Model::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	// 3D
}

void Model::Update()
{
	//this will be again overridden
}

void Model::SetProgram(GLuint program)
{
	this->program = program;
}

GLuint Model::GetVao() const
{
	return vao;
}

const std::vector<GLuint>& Model::GetVbos() const
{
	return vbos;
}

void Model::Destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbos.size(), &vbos[0]);
	vbos.clear();
}