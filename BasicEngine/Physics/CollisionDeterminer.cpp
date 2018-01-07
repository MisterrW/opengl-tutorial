#pragma once
#include "CollisionDeterminer.h"
#include "../Managers/ModelsManager.h"

using namespace BasicEngine::Physics;
using namespace BasicEngine::Managers;

CollisionDeterminer::CollisionDeterminer()
{
}

CollisionDeterminer::~CollisionDeterminer()
{
}

void CollisionDeterminer::setModelsManager(BasicEngine::Managers::ModelsManager* modelsManager) {
	modelsManager = modelsManager;
};

bool CollisionDeterminer::noPlayerCollisions(glm::mat4 viewMatrix) {
	// since we have the tentative view matrix, seems simplest to test player collisions in view space
	
	bool noCollisions = true;

	// save these as a constant!!

	glm::vec3 minPlayerBound = glm::vec3(-10, -10, -10);
	glm::vec3 maxPlayerBound = glm::vec3(10, 10, 10);

	// get models from modelsmanager
	std::map<std::string, Model*> modelList = modelsManager->getModels();

	// for each one, convert the bounds to camera space and test them against the player bounds
	// almost certainly better to invert the view matrix, convert player bounds back to world space and do it there
	for (auto model : modelList)
	{
		std::vector<glm::vec3> modelBounds = model.second->getBoundingBox();

		glm::vec3 minViewSpaceBound = glm::vec3(viewMatrix * glm::vec4(modelBounds[0], 1));
		glm::vec3 maxViewSpaceBound = glm::vec3(viewMatrix * glm::vec4(modelBounds[1], 1));
		if ((minViewSpaceBound.x < minPlayerBound.x && minPlayerBound.x < maxViewSpaceBound.x) || 
			(minViewSpaceBound.x < maxPlayerBound.x && maxPlayerBound.x < maxViewSpaceBound.x) ||
			(minPlayerBound.x < minViewSpaceBound.x && minViewSpaceBound.x < maxPlayerBound.x) ||
			(minPlayerBound.x < maxViewSpaceBound.x && maxViewSpaceBound.x < maxPlayerBound.x)) {
			
			if ((minViewSpaceBound.y < minPlayerBound.y && minPlayerBound.y < maxViewSpaceBound.y) ||
				(minViewSpaceBound.y < maxPlayerBound.y && maxPlayerBound.y < maxViewSpaceBound.y) ||
				(minPlayerBound.y < minViewSpaceBound.y && minViewSpaceBound.y < maxPlayerBound.y) ||
				(minPlayerBound.y < maxViewSpaceBound.y && maxViewSpaceBound.y < maxPlayerBound.y)) {
				
				if ((minViewSpaceBound.z < minPlayerBound.z && minPlayerBound.z < maxViewSpaceBound.z) ||
					(minViewSpaceBound.z < maxPlayerBound.z && maxPlayerBound.z < maxViewSpaceBound.z) ||
					(minPlayerBound.z < minViewSpaceBound.z && minViewSpaceBound.z < maxPlayerBound.z) ||
					(minPlayerBound.z < maxViewSpaceBound.z && maxViewSpaceBound.z < maxPlayerBound.z)) {
					noCollisions = false;
				}
			}
		}
	}

	return noCollisions;
};