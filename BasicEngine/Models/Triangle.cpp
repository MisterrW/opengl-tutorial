#include "Triangle.h";
using namespace BasicEngine::Models;

void Triangle::setNormal(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) {
	glm::vec3 u = v1 - v0;
	glm::vec3 v = v2 - v0;
	normal = glm::cross(u, v);
}

Triangle::Triangle(std::vector<glm::vec3> vertices) {
	v0 = vertices[0];
	v1 = vertices[1];
	v2 = vertices[2];
	setNormal(v0, v1, v2);
};
Triangle::Triangle(std::vector<glm::vec3> vertices, glm::vec3 normal) {
	v0 = vertices[0];
	v1 = vertices[1];
	v2 = vertices[2];
	normal = normal;
};
Triangle::Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) {
	v0 = v0;
	v1 = v1;
	v2 = v2;
	setNormal(v0, v1, v2);
};
Triangle::Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 normal) {
	v0 = v0;
	v1 = v1;
	v2 = v2;
	normal = normal;
};

std::vector<glm::vec3> Triangle::getVertices() {
	std::vector<glm::vec3> vertices = std::vector<glm::vec3>();
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	return vertices;
}

glm::vec3 Triangle::getV0() {
	return v0;
}

glm::vec3 Triangle::getV1() {
	return v1;
}

glm::vec3 Triangle::getV2() {
	return v2;
}

glm::vec3 Triangle::getNormal() {
	return normal;
}