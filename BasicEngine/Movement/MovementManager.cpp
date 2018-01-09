#include "MovementManager.h"
#include "../Managers/ModelManager.h"

using namespace BasicEngine::Movement;

MovementManager::MovementManager(){
	collisionDeterminer = BasicEngine::Physics::CollisionDeterminer(),
	positionManager = BasicEngine::Movement::PositionManager();

	oldViewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	oldGravityMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f);

	oldPlayerMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 100.0f, 300.0f, 1.0f);
}

MovementManager::~MovementManager()
{
}

// this is the equivalent of calculating movement for the player.
// the new movement matrix must take account of player input, gravity, collisions preventing movement.
glm::mat4 MovementManager::getViewMatrix(std::map<std::string, Model*>* models) {
	//typedef std::chrono::steady_clock clock;
	//typedef std::chrono::milliseconds ms;
	//using TimePoint = std::chrono::time_point<clock, ms>;

	//TimePoint tStart = std::chrono::time_point_cast<ms>(clock::now());
	if (true) {
		//auto updateStarted = clock::now();
		// encodes movement relative to the player's last position and orientation
		glm::mat4 tentativePlayerMatrix = positionManager.GetViewMatrix(oldPlayerMatrix);

		// lame gravity
		// encodes movement relative to the player's last position, orientation in world space
	/*	glm::mat4 tentativeGravityMatrix = glm::mat4(oldGravityMatrix);
		tentativeGravityMatrix[3][1] += 0.2f;
		glm::mat4 tentativeNewMatrix = tentativePlayerMatrix * tentativeGravityMatrix;*/
		oldPlayerMatrix = tentativePlayerMatrix;
		oldViewMatrix = tentativePlayerMatrix;

		//TimePoint tMid = std::chrono::time_point_cast<ms>(clock::now());

		// return tentativeNewMatrix;
		//if (collisionDeterminer.noPlayerCollisions(tentativeNewMatrix, models)) {
		//	oldGravityMatrix = tentativeGravityMatrix;
		//	oldPlayerMatrix = tentativePlayerMatrix;
		//	oldViewMatrix = tentativeNewMatrix;
		//}

		/*TimePoint last = std::chrono::time_point_cast<ms>(lastUpdated);
		TimePoint tEnd = std::chrono::time_point_cast<ms>(clock::now());

		std::chrono::duration<float, std::milli> timeSinceLastCall = tStart - last;
		std::chrono::duration<float, std::milli> timeForMatrices = tMid - tStart;
		std::chrono::duration<float, std::milli> timeForCollisions = tEnd - tMid;
		std::chrono::duration<float, std::milli> totalTimeThisCycle = tEnd - tStart;

		float sinceLastCall = timeSinceLastCall.count() / 1000;
		float forMatrices = timeForMatrices.count() / 1000;
		float forCollisions = timeForCollisions.count() / 1000;
		float thisCycle = totalTimeThisCycle.count() / 1000;*/
		//lastUpdated = tEnd;

		//int wtf = 1;
		//lastUpdated = updateStarted;
	}
	return oldViewMatrix;
};

//glm::mat4 MovementManager::getViewMatrix(std::map<std::string, Model*>* models) {
//	oldViewMatrix[3][1] -= 10;
//	return oldViewMatrix;
//}

void MovementManager::notifyKeyPress(char key, int x, int y) {
	positionManager.notifyKeyPress(key, x, y);
};

void MovementManager::notifyKeyUp(char key, int x, int y) {
	positionManager.notifyKeyUp(key, x, y);
};