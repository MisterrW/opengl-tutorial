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

double Behaviour::getVectorLength(glm::vec3 vectorini) {
	//pythagoras x2, once to get x/y hypoteneuse, then the hypoteneuse of that with z.
	double xy = sqrt((vectorini.x * vectorini.x) + (vectorini.y * vectorini.y));
	double length = sqrt(xy + (vectorini.z * vectorini.z));
	return length;
}

glm::vec3 Behaviour::getPositionRelativeToEntityPosition(glm::vec3 thisPosition, glm::vec3 otherEntityPosition) {
	return thisPosition - otherEntityPosition;
}

glm::vec3 Behaviour::getAbsolutePositionFromRelativePosition(glm::vec3 relativePosition, glm::vec3 otherEntityPosition) {
	return relativePosition + otherEntityPosition;
}

void Behaviour::behave(Monster* thisMonster, glm::vec3 playerPosition, glm::vec3 playerOrientation, std::map<std::string, Model*>* models, std::map<std::string, Monster*>* monsters)
{

}