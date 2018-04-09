#include "MonsterManager.h"
#include "../Models/Model.h"
#include "../Monsters/Monster.h"

using namespace BasicEngine::Managers;

MonsterManager::MonsterManager()
{

}

MonsterManager::~MonsterManager()
{
	//auto -it's a map iterator
	for (auto monster : monsterList)
	{
		delete monster.second;
	}
	monsterList.clear();

}

std::map<std::string, Monster*>* MonsterManager::getMonsters() {
	return &this->monsterList;
}

const Monster& MonsterManager::getMonster(const std::string& monsterName) const
{
	return (*this->monsterList.at(monsterName));
}

void MonsterManager::deleteMonster(const std::string& monsterName)
{
	Monster* monster = monsterList[monsterName];
	monster->Destroy();
	monsterList.erase(monsterName);
}

void MonsterManager::setMonster(const std::string& monsterName, Monster* monster)
{
	this->monsterList[monsterName.c_str()] = monster;
}