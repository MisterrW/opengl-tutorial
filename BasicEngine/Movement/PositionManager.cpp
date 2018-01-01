#include "PositionManager.h"

using namespace BasicEngine::Movement;

PositionManager::PositionManager() {
	// move this definition to PositionManager class
	ViewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -10.0f, 0.0f,
		0.0f, 0.0f, 10.0f, 1.0f);
}

PositionManager::~PositionManager() {

}

glm::mat4 PositionManager::GetViewMatrix() {
	return this->ViewMatrix;
};
	
void PositionManager::SetViewMatrix(glm::mat4 viewMatrix) {
	this->ViewMatrix = viewMatrix;
};

void PositionManager::notifyKeyPress(char key, int x, int y) {
	if (key == 'w') {
		ViewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, -10.0f, 0.0f,
			0.0f, 0.0f, 20.0f, 1.0f);
	} else if (key == 's') {
		ViewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, -10.0f, 0.0f,
			0.0f, 0.0f, 30.0f, 1.0f);
	}
};

void PositionManager::notifyKeyUp(char key, int x, int y) {
	ViewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -10.0f, 0.0f,
		0.0f, 0.0f, 30.0f, 1.0f);
};