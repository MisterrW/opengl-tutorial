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
	return this->model->getThisFrameMoveMatrix();
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