#include "Model.h"
using namespace BasicEngine::Rendering;
using namespace BasicEngine::Rendering::Models;

Model::Model() {}

Model::~Model()
{
	Destroy();
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