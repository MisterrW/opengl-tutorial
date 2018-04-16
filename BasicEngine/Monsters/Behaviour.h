#pragma once
#include <vector>
#include <map>
#include "../Models/Model.h"
#include "../../../Dependencies/include/glm/glm.hpp"

using namespace BasicEngine::Models;

namespace BasicEngine
{
	namespace Monsters
	{
		class Mind;
		class Monster;

		class Behaviour
		{
		public:
			// the general aim is to abstract the goals of the monster (where to go and how quickly, whether to attack) from the implementation of movement etc, which will be properties of the model for now.
			Behaviour();

			// will probably end up with modifiers like desired speed (enum)
			// might not need to be virtual, if it's just an accessor
			virtual glm::vec3 getDesiredPosition();

			// do this for now, assuming that monsters always attack directly in front of them. The specifics of who is being attacked / targeted should be internal to the mind anyway, but we will probably need to share details like which weapon / attack type.
			// we will do something similar for sounds as well, ultimately both will probably be enums.
			// might not need to be virtual, if it's just an accessor
			virtual bool checkIfAttacking();

			// helper methods for implementations of behave()

			double getVectorLength(glm::vec3 vectorini);

			// returns the monster's relative position to another entity (i.e. position in a coord space with otherEntity at the origin)
			glm::vec3 getPositionRelativeToEntityPosition(glm::vec3 thisPosition, glm::vec3 otherEntityPosition);

			// returns the monster's absolute position given a relative position and another entity
			glm::vec3 getAbsolutePositionFromRelativePosition(glm::vec3 relativePosition, glm::vec3 otherEntityPosition);

			virtual void behave(Monster* thisMonster, glm::vec3 playerPosition, glm::vec3 playerOrientation, std::map<std::string, BasicEngine::Models::Model*>* models, std::map<std::string, Monster*>* monsters);


			// these will be stored as state, because we might want to access them more often than we calculate them
			glm::vec3 desiredPosition;
			bool isAttacking;
		};
	}
}
