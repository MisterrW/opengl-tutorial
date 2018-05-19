#include "Monster.h"

using namespace BasicEngine::Monsters;

Monster::Monster(BasicEngine::Models::Model* model, Mind* mind)
{
	this->model = model;
	this->mind = mind;
}

Monster::Monster()
{
}

void Monster::Destroy()
{
	this->model->Destroy();
}

/*
For updating the contained model
*/

void Monster::Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	this->model->Draw(projectionMatrix, viewMatrix);
}

glm::mat4 Monster::getPositionMatrix()
{
	return this->model->getPositionMatrix();
}

glm::mat4 Monster::getThisFrameMoveMatrix()
{
	glm::mat4 moveMatrix = glm::mat4(1);
	// get the desired position from the mind
	glm::vec3 desiredPosition = this->mind->getDesiredPosition();
	// pass this desired position (a vec3) to the model's move function
	moveMatrix = this->model->moveToward(desiredPosition);
	// the move function returns a matrix moving it as far as it can go towards that vector

	// we return that matrix to the movement manager for collision determining. The movement manager will set the adjusted position matrix in this->model.
	return moveMatrix;
}

void Monster::setThisFrameMoveMatrix(glm::mat4 thisFrameMoveMatrix)
{
	this->model->setThisFrameMoveMatrix(thisFrameMoveMatrix);
}

void Monster::setPositionMatrix(glm::mat4 positionMatrix)
{
	this->model->setPositionMatrix(positionMatrix);
}

Model* Monster::getModel()
{
	return this->model;
}

// for interacting with the contained mind

void Monster::think(glm::vec3 playerPosition, glm::vec3 playerOrientation, std::map<std::string, Model*>* models, std::map<std::string, Monster*>* monsters)
{
	// todo get the position of this monster from the model (or should it live in the monster?)
	this->mind->think(this, playerPosition, playerOrientation, models, monsters);
}