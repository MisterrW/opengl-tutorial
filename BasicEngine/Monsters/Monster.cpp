#include "Monster.h"

using namespace BasicEngine::Monsters;

Monster::Monster(BasicEngine::Models::Model* model, Mind* mind)
{
	this->model = model;
	this->mind = mind;
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

void Monster::setPositionMatrix(glm::mat4 positionMatrix)
{
	this->model->setPositionMatrix(positionMatrix);
}

Model* Monster::getModel()
{
	return this->model;
}