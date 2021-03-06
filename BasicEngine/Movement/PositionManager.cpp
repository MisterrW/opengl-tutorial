#include "PositionManager.h"

using namespace BasicEngine::Movement;

PositionManager::PositionManager() {

	OldKeyStates = new bool[256];
	KeyStates = new bool[256];
	lookScaleFactor = 2.0;
	moveScaleFactor = 3.0;
}

PositionManager::~PositionManager() {

}

glm::mat4 PositionManager::GetMoveMatrix() {
	// keys control camera position
	glm::mat4 movementMatrix = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	// forward (w s)
	if (KeyStates['w'] == true) {
		movementMatrix[3][2] += 2.0f * moveScaleFactor;
	}
	else if (KeyStates['s'] == true) {
		movementMatrix[3][2] -= 2.0f * moveScaleFactor;
	}

	// sideways (a d)
	if (KeyStates['a'] == true) {
		movementMatrix[3][0] -= 2.0f * moveScaleFactor;
	}
	else if (KeyStates['d'] == true) {
		movementMatrix[3][0] += 2.0f * moveScaleFactor;
	}

	// up/down (x c)
	if (KeyStates['x'] == true) {
		movementMatrix[3][1] += 2.0f * moveScaleFactor;
	}
	else if (KeyStates['c'] == true) {
		movementMatrix[3][1] -= 2.0f * moveScaleFactor;
	}

	return movementMatrix;
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
		orientX = 0.015f * lookScaleFactor;
	}
	else if (KeyStates['l'] == true) {
		orientX = -0.015f * lookScaleFactor;
	}

	// bank left / right (yaw)
	if (KeyStates['k'] == true) {
		orientZ = -0.015f * lookScaleFactor;
	}
	else if (KeyStates[';'] == true) {
		orientZ = 0.015f * lookScaleFactor;
	}

	glm::mat4 rotMat = GetXYZRotMat(orientX, orientY, orientZ);

	return rotMat;
}

//glm::mat4  PositionManager::GetViewMatrix(glm::mat4 oldViewMatrix) {
//	glm::mat4 movedMatrix = GetMoveMatrix(oldViewMatrix);
//
//	glm::mat4 orientationMatrix = GetOrientationMatrix();
//
//	glm::mat4 viewMatrix = orientationMatrix * movedMatrix;
//
//	oldViewMatrix = viewMatrix;
//
//	return viewMatrix;
//}

void PositionManager::notifyKeyPress(char key, int x, int y) {
	OldKeyStates[key] = KeyStates[key];
	KeyStates[key] = true;
};

void PositionManager::notifyKeyUp(char key, int x, int y) {
	OldKeyStates[key] = KeyStates[key];
	KeyStates[key] = false;
};

