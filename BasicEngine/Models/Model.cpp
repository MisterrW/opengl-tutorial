#include "Model.h"
using namespace BasicEngine::Models;


// move this to the base model class
std::vector<glm::vec3> Model::setBoundingBox(std::vector<std::vector<glm::vec3>> vertexArrays) {
	std::vector<glm::vec3> boundingBox = std::vector<glm::vec3>();

	// actually we don't need a box, just 2 vectors representing the smallest and largest xyz corners of a box containing the model, for basic axis-aligned AABB collision / frustrum checks
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

Model::Model() {}

Model::Model(std::vector<std::vector<glm::vec3>> vertexArrays) {
	boundingBox = setBoundingBox(vertexArrays);
}

Model::~Model()
{
	Destroy();
}

std::vector<glm::vec3> Model::getBoundingBox() {
	return boundingBox;
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