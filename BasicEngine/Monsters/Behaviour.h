#pragma once
#include <vector>
#include "../../../Dependencies/include/glm/glm.hpp"

namespace BasicEngine
{
	namespace Monsters
	{
		class Behaviour
		{
		public:
			// the general aim is to abstract the goals of the monster (where to go and how quickly, whether to attack) from the implementation of movement etc, which will be properties of the model for now.
			Behaviour();

			// will probably end up with modifiers like desired speed (enum)
			glm::vec3 getDesiredPosition();

			// do this for now, assuming that monsters always attack directly in front of them. The specifics of who is being attacked / targeted should be internal to the mind anyway, but we will probably need to share details like which weapon / attack type.
			// we will do something similar for sounds as well, ultimately both will probably be enums.
			bool checkIfAttacking();

		private:

			// these will be stored as state, because we might want to access them more often than we calculate them
			glm::vec3 desiredPosition;
			bool isAttacking;
		};
	}
}
