/*
=================
The collision determiner contains various functions for detecting collisions.
It is used by the movement manager to identify whether prospective moves are possible.
It is also used by the renderer for frustrum clipping.
=================
*/

#pragma once
#include "../Managers/ModelsManager.h"

namespace BasicEngine {
	namespace Physics {
		class CollisionDeterminer
		{
		public:
			CollisionDeterminer();
			void setModelsManager(BasicEngine::Managers::ModelsManager* modelsManager);
			~CollisionDeterminer();
			bool noPlayerCollisions(glm::mat4 viewMatrix);
		private:
			BasicEngine::Managers::ModelsManager* modelsManager;
		};
	}
}