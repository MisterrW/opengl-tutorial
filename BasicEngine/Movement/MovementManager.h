/*
=================
The movement manager computes the new position of an entity (currently only the player)
The new position is based on requested movement based on player input,
and movement based on physics including gravity and collisions.
=================
*/

#pragma once
#include "PositionManager.h"
#include "../Physics/CollisionDeterminer.h"

namespace BasicEngine {
	namespace Movement {
		class MovementManager
		{
		public:
			MovementManager();
			~MovementManager();
			glm::mat4 getViewMatrix(std::map<std::string, Model*> models);
			void notifyKeyPress(char key, int x, int y);
			void notifyKeyUp(char key, int x, int y);

		private:
			Movement::PositionManager positionManager;
			Physics::CollisionDeterminer collisionDeterminer;
			glm::mat4 oldViewMatrix;
			glm::mat4 oldGravityMatrix;
		};
	}
}
