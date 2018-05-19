/*
=================
The monsters manager maintains a list of monsters in the scene.
In a draw cycle, it returns its model list to the scene manager,
which passes them to the renderer to be drawn.
=================
*/

#pragma once
#include <map>
#include "ShaderManager.h"
#include "../Monsters/Monster.h"
#include "../Monsters/Mind.h"
#include "../Monsters/Behaviour.h"
#include "../Monsters/Behaviours/KeepAway.h"
#include "../Monsters/Behaviours/Follow.h"
#include "../Models/Model.h"

using namespace BasicEngine::Monsters;
using namespace BasicEngine::Models;

namespace BasicEngine
{
	namespace Managers
	{
		class MonsterManager
		{
		public:
			MonsterManager();
			~MonsterManager();

			// returns all monsters
			std::map<std::string, Monster*>* getMonsters();
			const Monster& getMonster(const std::string& monsterName) const;
			void deleteMonster(const std::string& monsterName);

			void setMonster(const std::string& monsterName, Monster* monster);

			void doMonsterThinking(glm::vec3 playerPosition, glm::vec3 playerOrientation, std::map<std::string, Model*>* models);

		private:
			// NOTE this may become a bottleneck, better to use vector
			std::map<std::string, Monster*> monsterList;
			MonsterManager(const MonsterManager&); // no implementation 
			MonsterManager& operator=(const MonsterManager&); // no implementation 
		};
	}
}