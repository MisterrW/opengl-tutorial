#pragma once
#include <vector>
#include <map>
#include "Behaviour.h"
#include "../../../Dependencies/include/glm/glm.hpp"

namespace BasicEngine
{
	namespace Monsters
	{
		class Monster;

		class Mind
		{
		public:
			// the general aim is to abstract the goals of the monster (where to go and how quickly, whether to attack) from the implementation of movement etc, which will be properties of the model for now.
			Mind();

			Mind(std::vector<BasicEngine::Monsters::Behaviour*> behaviours);


			// the function which takes in all the gamestate and decides what to do
			// it will call setActiveBehaviour(), and then make that behaviour behave()
			void think(Monster* thisMonster, glm::vec3 playerPosition, glm::vec3 playerOrientation, std::map<std::string, Model*>* models, std::map<std::string, Monster*>* monsters);

			// passes this query through to the active behaviour
			// will probably end up with modifiers like desired speed (enum)
			glm::vec3 getDesiredPosition();

			// passes this query through to the active behaviour
			// do this for now, assuming that monsters always attack directly in front of them. The specifics of who is being attacked / targeted should be internal to the mind anyway, but we will probably need to share details like which weapon / attack type.
			// we will do something similar for sounds as well, ultimately both will probably be enums.
			bool checkIfAttacking();

		private:
			/**
			* Behaviours: each of these will make the monster behave in a different way, eg: move toward goal, attack, flee, mill about.
			* Changing the active behaviour changes the result of querying the mind for actions.
			* Behaviours will need access to all the information the mind has.
			* Behaviours might nest recursively to allow complex behaviours without mandating levels of behaviour - eg combining a moving behaviour and an attacking behaviour
			*/

			// remember: teams, an int (player is 0, everything else typically 1). Every monster needs a team, and a uid.
			std::vector<Behaviour*> behaviours;
			Behaviour* activeBehaviour;


			void setActiveBehaviour(Monster* thisMonster, glm::vec3 playerPosition, glm::vec3 playerOrientation, std::map<std::string, Model*>* models, std::map<std::string, Monster*>* monsters);
		};
	}
}