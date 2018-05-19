#include "Behaviour.h"
using namespace BasicEngine::Monsters;

Behaviour::Behaviour() 
{
	this->isAttacking = false;
	this->desiredPosition = glm::vec3(1, 1, 1);
};

glm::vec3 Behaviour::getDesiredPosition()
{
	return this->desiredPosition;
};

bool Behaviour::checkIfAttacking()
{
	return this->isAttacking;
}

double Behaviour::getVectorLength(glm::vec3 vectorini) {
	glm::vec3 absVec = glm::vec3(abs(vectorini.x), abs(vectorini.y), abs(vectorini.z));
	//pythagoras x2, once to get x/y hypoteneuse, then the hypoteneuse of that with z.
	double xy = sqrt((absVec.x * absVec.x) + (absVec.y * absVec.y));
	double length = sqrt((xy * xy) + (absVec.z * absVec.z));
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
	this->desiredPosition = glm::vec3(0, 0, 0);
	this->isAttacking = false;
}