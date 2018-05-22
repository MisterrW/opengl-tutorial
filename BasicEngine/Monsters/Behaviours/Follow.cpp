#include "follow.h"
using namespace BasicEngine::Monsters;

void Follow::behave(Monster* thisMonster, glm::vec3 playerPosition, glm::vec3 playerOrientation, std::map<std::string, Model*>* models, std::map<std::string, Monster*>* monsters)
{
	double maximumDistance = 3000;
	double desiredDistance = 1000;
	/*
	The Follow behaviour causes a monster to attempt to remain within a certain distance from the player.
	If the distance to the player is above the minimum distance, the behaviour creates a desired location,
	along the line from the player to the monster, which makes this distance sufficiently small.
	*/
	glm::mat4 currentPositionMatrix = thisMonster->getPositionMatrix();
	glm::vec3 currentPosition = glm::vec3(currentPositionMatrix * glm::vec4(0, 0, 0, 1));
	glm::vec3 relativePosition = getPositionRelativeToEntityPosition(currentPosition, playerPosition);

	double distance = getVectorLength(relativePosition);

	// reset if we're close enough
	if (distance <= desiredDistance) {
		IsClosing = false;
	}

	// reset if player's new position requires a new assessment
	if (IsClosing && getVectorLength(desiredPosition - playerPosition) > desiredDistance) {
		IsClosing = false;
	}

	if (distance > maximumDistance && !IsClosing)
	{
		IsClosing = true;
		double ratio = desiredDistance / abs(distance);
		glm::vec3 desiredRelativePosition = glm::vec3(relativePosition.x * ratio, relativePosition.y * ratio, relativePosition.z * ratio);
		glm::vec3 desiredPosition = getAbsolutePositionFromRelativePosition(desiredRelativePosition, playerPosition);
		this->desiredPosition = desiredPosition;
	}
}