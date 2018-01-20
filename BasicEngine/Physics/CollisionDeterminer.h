/*
=================
The collision determiner contains various functions for detecting collisions.
It is used by the movement manager to identify whether prospective moves are possible.
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
			bool noPlayerCollisions(glm::mat4 viewMatrix, std::map<std::string, Model*>* models);
		private:
		};
	}
}