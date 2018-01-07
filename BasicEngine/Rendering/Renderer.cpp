#include "Renderer.h"

using namespace BasicEngine::Rendering;

Renderer::Renderer() {
	viewMatrix = glm::mat4();
	projectionMatrix = glm::mat4();
}

Renderer::~Renderer() {

}

void Renderer::setProjectionMatrix(glm::mat4 projectionMatrix) {
	this->projectionMatrix = projectionMatrix;
}

void Renderer::setViewMatrix(glm::mat4 viewMatrix) {
	this->viewMatrix = viewMatrix;
}

bool Renderer::shouldDraw(const Model& model) {
	// frustrum culling etc
	return true;
}

void Renderer::draw(Model* model) {
	if (shouldDraw(*model)) {
		model->Draw(projectionMatrix, viewMatrix);
	}
}

