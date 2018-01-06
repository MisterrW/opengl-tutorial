#include "MeshStrip.h"
using namespace LocalModels;

MeshStrip::MeshStrip()
{
}


MeshStrip::~MeshStrip()
{
}

void MeshStrip::Create()
{
}

void MeshStrip::Update()
{
}

int MeshStrip::getVerticesCount(int width, int height) {
	return width * height * 3;
}

int MeshStrip::getIndicesCount(int width, int height) {
	return (width*height) + (width - 1)*(height - 2);
}

float* MeshStrip::getVertices(int width, int height) {
	if (vertices) return vertices;

	vertices = new float[getVerticesCount(width, height)];
	int i = 0;

	for (int row = 0; row<height; row++) {
		for (int col = 0; col<width; col++) {
			vertices[i++] = (float)col;
			vertices[i++] = 0.0f;
			vertices[i++] = (float)row;
		}
	}

	return vertices;
}

int* MeshStrip::getIndices(int width, int height) {
	// if (indices) return indices;
	std::vector<int> ints = std::vector<int>();
	indices = new int[200];
	int i = 0;

	for (int row = 0; row < height - 1; row++) {
		if ((row & 1) == 0) { // even rows
			for (int col = 0; col < width; col++) {
				indices[i++] = col + row * width;
				indices[i++] = col + (row + 1) * width;
				ints.push_back(col + row * width);
				ints.push_back(col + (row + 1) * width);
			}
		}
		else { // odd rows
			for (int col = width - 1; col > 0; col--) {
				indices[i++] = col + (row + 1) * width;
				indices[i++] = col - 1 + +row * width;
				ints.push_back(col + (row + 1) * width);
				ints.push_back(col - 1 + +row * width);
			}
		}
	}
	if ((height & 1) && height > 2) {
		indices[i++] = (height - 1) * width;
	}

	
	return indices;
}

void MeshStrip::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	width = 10;
	height = 10;
	indices = getIndices(width, height);
	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &modelMatrix[0][0]);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(
	//	0,
	//	3, 
	//	GL_FLOAT, 
	//	GL_FALSE,
	//	0, 
	//	(void*)0
	//	// getVertices(width, height)
	//);
	//glDrawElements(
	//	GL_TRIANGLE_STRIP, 
	//	getIndicesCount(width, height), 
	//	GL_UNSIGNED_INT, 
	//	getIndices(width, height));

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, getVertices(width, height));
	glDrawElements(GL_TRIANGLE_STRIP, getIndicesCount(width, height), GL_UNSIGNED_INT, getIndices(width, height));
	glDisableClientState(GL_VERTEX_ARRAY);
}

