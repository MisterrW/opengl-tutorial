#include "keepaway.h"
using namespace BasicEngine::Monsters;

void KeepAway::behave(Monster* thisMonster, glm::vec3 playerPosition, glm::vec3 playerOrientation, std::map<std::string, Model*>* models, std::map<std::string, Monster*>* monsters)
{
	double minimumDistance = 1000;
	/*
	The KeepAway behaviour causes a monster to attempt to maintain a minimum distance from the player.
    If the distance to the player is below the minimum distance, the behaviour creates a desired location,
	along the line from the player to the monster, which makes this distance sufficient.
	In other words, with the player at 0, 0, 0, scale the vector to the monster to the correct length.
	*/
	glm::mat4 currentPositionMatrix = thisMonster->getPositionMatrix();
	glm::vec3 currentPosition = glm::vec3(currentPositionMatrix * glm::vec4(0, 0, 0, 1));
	glm::vec3 relativePosition = getPositionRelativeToEntityPosition(currentPosition, playerPosition);
	
	double distance = getVectorLength(relativePosition);

	if (distance < minimumDistance)
	{
		double ratio = minimumDistance / abs(distance);
		glm::vec3 desiredRelativePosition = glm::vec3(relativePosition.x * ratio, relativePosition.y * ratio, relativePosition.z * ratio);
		glm::vec3 desiredPosition = getAbsolutePositionFromRelativePosition(desiredRelativePosition, playerPosition);
		this->desiredPosition = desiredPosition;
	}
	else
	{
		this->desiredPosition = currentPosition;
	}
	
}