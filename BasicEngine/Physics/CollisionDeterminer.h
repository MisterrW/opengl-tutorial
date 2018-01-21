/*
=================
The collision determiner contains various functions for detecting collisions.
It is used by the movement manager to deflect move vectors which collide with models.
It is also used by the renderer for frustrum clipping.
=================
*/

#pragma once
#include "../Managers/ModelManager.h"
#include <array>

namespace BasicEngine {
	namespace Physics {
		class CollisionDeterminer
		{
		public:
			CollisionDeterminer();
			~CollisionDeterminer();
			//std::array<bool, 3> noPlayerCollisions(glm::mat4 viewMatrix, std::map<std::string, Model*>* models);
			glm::mat4 doPlayerCollisions(glm::mat4 oldViewMatrix, glm::mat4 newViewMatrix, std::map<std::string, Model*>* models);
		private:
			std::vector<Model*> getPlayerCollidedModels(glm::mat4 viewMatrix, std::map<std::string, Model*>* models);
			glm::vec3 getMove(glm::mat4 oldViewMatrix, glm::mat4 newViewMatrix);
			double getAngleBetween(glm::vec3 a, glm::vec3 b);
			glm::vec3 getCollisionPlaneNormal(Model* model);
			glm::mat4 getDeflectionMatrix(glm::vec3 move, glm::vec3 planeNormal);
		};
	}
}