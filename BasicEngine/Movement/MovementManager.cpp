#include "MovementManager.h"
#include "../Managers/ModelsManager.h"

using namespace BasicEngine::Movement;

MovementManager::MovementManager()
{
	positionManager = PositionManager();
	collisionDeterminer = Physics::CollisionDeterminer();
	oldViewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, -20.0f, 300.0f, 1.0f);
	oldGravityMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, -20.0f, 300.0f, 1.0f);
}

MovementManager::~MovementManager()
{
}

void MovementManager::setModelsManager(BasicEngine::Managers::ModelsManager* modelsManager) {
	collisionDeterminer.setModelsManager(modelsManager);
};

// this is the equivalent of calculating movement for the player.
// the new movement matrix must take account of player input, gravity, collisions preventing movement.
glm::mat4 MovementManager::getViewMatrix() {
	// encodes movement relative to the player's last position and orientation
	glm::mat4 tentativePlayerMatrix = positionManager.GetViewMatrix(oldViewMatrix);

	// lame gravity
	// encodes movement relative to the player's last position, orientation in world space
	glm::mat4 tentativeGravityMatrix = glm::mat4(oldGravityMatrix);
	tentativeGravityMatrix[3][1] += 2.0f;
	glm::mat4 tentativeNewMatrix = tentativePlayerMatrix * tentativeGravityMatrix;

	// return tentativeNewMatrix;
	if (collisionDeterminer.noPlayerCollisions(tentativeNewMatrix)) {
		oldGravityMatrix = tentativeGravityMatrix;
		oldViewMatrix = tentativePlayerMatrix;
		return tentativeNewMatrix;
	}
	else {
		return oldViewMatrix;
	}
};

void MovementManager::notifyKeyPress(char key, int x, int y) {
	positionManager.notifyKeyPress(key, x, y);
};

void MovementManager::notifyKeyUp(char key, int x, int y) {
	positionManager.notifyKeyUp(key, x, y);
};