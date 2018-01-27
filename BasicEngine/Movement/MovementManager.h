/*
=================
The movement manager computes the new position of an entity (currently only the player)
The new position is based on requested movement based on player input,
and movement based on physics including gravity and collisions.
=================
*/

#pragma once
#include "PositionManager.h"
#include <chrono>
#include "../Physics/CollisionDeterminer.h"

namespace BasicEngine {
	namespace Movement {
		class MovementManager
		{
		public:
			MovementManager();
			~MovementManager();
			glm::mat4 getViewMatrix(const std::map<std::string, Model*>* models);
			void updateModelPositions(std::map<std::string, Model*>* models);
			void notifyKeyPress(char key, int x, int y);
			void notifyKeyUp(char key, int x, int y);

		private:
			Movement::PositionManager positionManager;
			Physics::CollisionDeterminer collisionDeterminer;
			glm::mat4 oldOrientationMatrix;
			glm::mat4 oldPositionMatrix;
			std::chrono::steady_clock::time_point lastUpdated;

			glm::mat4 getGravityMatrix();
		};
	}
}
