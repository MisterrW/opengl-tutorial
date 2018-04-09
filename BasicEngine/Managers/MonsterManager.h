/*
=================
The models manager maintains a list of models which make up the scene.
In a draw cycle, it returns its model list to the scene manager,
which passes them to the renderer to be drawn.
=================
*/

#pragma once
#include <map>
#include "ShaderManager.h"
#include "../Monsters/Monster.h"
#include "../Monsters/Mind.h"
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

		private:
			// NOTE this may become a bottleneck, better to use vector
			std::map<std::string, Monster*> monsterList;
			MonsterManager(const MonsterManager&); // no implementation 
			MonsterManager& operator=(const MonsterManager&); // no implementation 
		};
	}
}