#include "Behaviour.h"
using namespace BasicEngine::Monsters;

Behaviour::Behaviour() 
{
};

glm::vec3 Behaviour::getDesiredPosition()
{
	return glm::vec3(1, 1, 1);
};

bool Behaviour::checkIfAttacking()
{
	return false;
}