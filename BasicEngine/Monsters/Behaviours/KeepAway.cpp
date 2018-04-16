#include "keepaway.h"
using namespace BasicEngine::Monsters;

KeepAway::KeepAway() {
	this->isAttacking = false;
	this->desiredPosition = glm::vec3(1, 1, 1);
}

glm::vec3 KeepAway::getDesiredPosition()
{
	return this->desiredPosition;
};

bool KeepAway::checkIfAttacking()
{
	return this->isAttacking;
}

void KeepAway::behave(Monster* thisMonster, glm::vec3 playerPosition, glm::vec3 playerOrientation, std::map<std::string, Model*>* models, std::map<std::string, Monster*>* monsters)
{
	double minimumDistance = 100000;
	/*
	The KeepAway behaviour causes a monster to attempt to maintain a minimum distance from the player.
    If the distance to the player is below the minimum distance, the behaviour creates a desired location,
	along the line from the player to the monster, which makes this distance sufficient.
	In other words, with the player at 0, 0, 0, scale the vector to the monster to the correct length.

	pseudocode:
	*/
	glm::vec3 thisPosition = glm::vec3( glm::vec4(0, 0, 0, 0) * (thisMonster->getPositionMatrix()));
	

	glm::vec3 relativePosition = getPositionRelativeToEntityPosition(thisPosition, playerPosition);
	double distance = getVectorLength(relativePosition);
	if (distance < minimumDistance) {
		double ratio = minimumDistance / abs(distance);
		glm::vec3 desiredRelativePosition = glm::vec3(relativePosition.x * ratio, relativePosition.y * ratio, relativePosition.z * ratio);
		
		glm::vec3 desiredPosition = getAbsolutePositionFromRelativePosition(desiredRelativePosition, playerPosition);
		this->desiredPosition = desiredPosition;
	}
	
}