#include "PositionManager.h"

using namespace BasicEngine::Movement;

PositionManager::PositionManager() {
	ViewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, -20.0f, 300.0f, 1.0f);

	OldKeyStates = new bool[256];
	KeyStates = new bool[256];
	ScaleFactor = 100.0;
}

PositionManager::~PositionManager() {

}

glm::mat4 PositionManager::GetViewMatrix() {
	return this->ViewMatrix;
};

void PositionManager::SetViewMatrix(glm::mat4 viewMatrix) {
	this->ViewMatrix = viewMatrix;
};

glm::mat4 PositionManager::GetMoveMatrix() {
	// keys control camera position
	glm::mat4 updatedViewMatrix = glm::mat4(ViewMatrix);

	// forward (w s)
	if (KeyStates['w'] == true) {
		updatedViewMatrix[3][2] -= 0.01f * ScaleFactor;
	}
	else if (KeyStates['s'] == true) {
		updatedViewMatrix[3][2] += 0.01f * ScaleFactor;
	}

	// sideways (a d)
	if (KeyStates['a'] == true) {
		updatedViewMatrix[3][0] += 0.01f * ScaleFactor;
	}
	else if (KeyStates['d'] == true) {
		updatedViewMatrix[3][0] -= 0.01f * ScaleFactor;
	}

	// up/down (x c)
	if (KeyStates['x'] == true) {
		updatedViewMatrix[3][1] -= 0.01f * ScaleFactor;
	}
	else if (KeyStates['c'] == true) {
		updatedViewMatrix[3][1] += 0.01f * ScaleFactor;
	}

	return updatedViewMatrix;
}

glm::mat4 PositionManager::GetXYZRotMat(float x, float y, float z) {
	float cosX = cos(x);
	float sinX = sin(x);
	float cosY = cos(y);
	float sinY = sin(y);
	float cosZ = cos(z);
	float sinZ = sin(z);

	glm::mat4 rotX, rotY, rotZ;

	rotX = glm::mat4(
		1, 0, 0, 0,
		0, cosX, -sinX, 0,
		0, sinX, cosX, 0,
		0, 0, 0, 1);

	rotY = glm::mat4(
		cosY, 0, sinY, 0,
		0, 1, 0, 0,
		-sinY, 0, cosY, 0,
		0, 0, 0, 1
	);

	rotZ = glm::mat4(
		cosZ, -sinZ, 0, 0,
		sinZ, cosZ, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	return rotX * rotZ * rotY;
}

glm::mat4 PositionManager::GetOrientationMatrix() {
	// using keys for look for now as well
	float orientX = 0.0f;
	float orientY = 0.0f;
	float orientZ = 0.0f;

	// look up / down
	if (KeyStates['o'] == true) {
		orientX = -0.0015f * ScaleFactor;
	}
	else if (KeyStates['l'] == true) {
		orientX = +0.0015f * ScaleFactor;
	}

	// bank left / right (yaw)
	if (KeyStates['k'] == true) {
		orientZ = +0.0015f * ScaleFactor;
	}
	else if (KeyStates[';'] == true) {
		orientZ = -0.0015f * ScaleFactor;
	}

	glm::mat4 rotMat = GetXYZRotMat(orientX, orientY, orientZ);

	return rotMat;
}

void PositionManager::UpdateViewMatrix() {
	glm::mat4 movedMatrix = GetMoveMatrix();

	glm::mat4 orientationMatrix = GetOrientationMatrix();

	ViewMatrix = orientationMatrix * movedMatrix;
}

void PositionManager::notifyKeyPress(char key, int x, int y) {
	OldKeyStates[key] = KeyStates[key];
	KeyStates[key] = true;
};

void PositionManager::notifyKeyUp(char key, int x, int y) {
	OldKeyStates[key] = KeyStates[key];
	KeyStates[key] = false;
};

