#include "MovementManager.h"
#include "../Managers/ModelManager.h"

using namespace BasicEngine::Movement;

MovementManager::MovementManager(){
	collisionDeterminer = BasicEngine::Physics::CollisionDeterminer(),
	positionManager = BasicEngine::Movement::PositionManager();

	oldOrientationMatrix = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	oldPositionMatrix = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, -100.0f, 600.0f, 1.0f);
}

MovementManager::~MovementManager()
{
}

glm::mat4 MovementManager::getGravityMatrix() {
	return glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.2f, 0.0f, 1.0f);
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
		glm::mat4 moveMatrix = positionManager.GetMoveMatrix();
		glm::mat4 orientationMatrix = positionManager.GetOrientationMatrix();

		// lame gravity
	    glm::mat4 gravityMatrix = getGravityMatrix();

		//TimePoint tMid = std::chrono::time_point_cast<ms>(clock::now());

		//combine move and gravity as position matrix
		glm::mat4 tentativePositionMatrix = moveMatrix * gravityMatrix;
		// then call collision determiner with old position and new position matrix
		
		glm::mat4 actualPositionMatrix = collisionDeterminer.doPlayerCollisions(oldPositionMatrix, tentativePositionMatrix, models);
		
		oldPositionMatrix = actualPositionMatrix;
		
		oldOrientationMatrix = oldOrientationMatrix * orientationMatrix;

		glm::mat4 viewMatrix = oldPositionMatrix * oldOrientationMatrix;
		return viewMatrix;
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