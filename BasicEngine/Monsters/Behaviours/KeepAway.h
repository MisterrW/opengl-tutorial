#pragma once

#include <vector>
#include <map>
#include "../Monster.h"
#include "../Behaviour.h"
#include "../../../Dependencies/include/glm/glm.hpp"
#include <map>

namespace BasicEngine
{
	namespace Monsters
	{
		class KeepAway : public Behaviour
		{
		public:
			void behave(Monster* thisMonster, glm::vec3 playerPosition, glm::vec3 playerOrientation, std::map<std::string, Model*>* models, std::map<std::string, Monster*>* monsters) override final;
		
		private:
			bool IsFleeing = false;
		};

	}
}
