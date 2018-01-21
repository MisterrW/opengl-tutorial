#include "Triangle.h"
using namespace BasicEngine::Models;

void Triangle::setNormal(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) {
	glm::vec3 u = v1 - v0;
	glm::vec3 v = v2 - v0;
	this->normal = glm::cross(u, v);
}

Triangle::Triangle(std::vector<glm::vec3> vertices) {
	this->v0 = vertices[0];
	this->v1 = vertices[1];
	this->v2 = vertices[2];
	setNormal(v0, v1, v2);
};
Triangle::Triangle(std::vector<glm::vec3> vertices, glm::vec3 normal) {
	this->v0 = vertices[0];
	this->v1 = vertices[1];
	this->v2 = vertices[2];
	this->normal = normal;
};
Triangle::Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) {
	this->v0 = v0;
	this->v1 = v1;
	this->v2 = v2;
	setNormal(v0, v1, v2);
};
Triangle::Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 normal) {
	this->v0 = v0;
	this->v1 = v1;
	this->v2 = v2;
	this->normal = normal;
};

std::vector<glm::vec3> Triangle::getVertices() {
	std::vector<glm::vec3> vertices = std::vector<glm::vec3>();
	vertices.push_back(this->v0);
	vertices.push_back(this->v1);
	vertices.push_back(this->v2);
	return vertices;
}

glm::vec3 Triangle::getV0() {
	return this->v0;
}

glm::vec3 Triangle::getV1() {
	return this->v1;
}

glm::vec3 Triangle::getV2() {
	return this->v2;
}

glm::vec3 Triangle::getNormal() {
	return this->normal;
}