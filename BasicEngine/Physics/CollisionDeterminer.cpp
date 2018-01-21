#pragma once
#include "CollisionDeterminer.h"
#include "../Managers/ModelManager.h"
#include "../../../Dependencies/include/glm/gtx/transform.hpp"

using namespace BasicEngine::Physics;
using namespace BasicEngine::Managers;

CollisionDeterminer::CollisionDeterminer()
{
}

CollisionDeterminer::~CollisionDeterminer()
{
}

glm::vec3 CollisionDeterminer::getMove(glm::mat4 oldViewMatrix, glm::mat4 newViewMatrix) {
	// get a vector representing the change in position from the old to the new matrix
	// by multiplying the zero vector by the inverse of each matrix
	// and then subtracting the old one from the new one
	// todo inverting might be slow, is there an alternative?

	glm::vec4 origin = glm::vec4(0, 0, 0, 1);
	glm::mat4 oldInv = glm::inverse(oldViewMatrix);
	glm::mat4 newInv = glm::inverse(newViewMatrix);
	glm::vec3 oldPos = glm::vec3(oldInv * origin);
	glm::vec3 newPos = glm::vec3(newInv * origin);

	glm::vec3 move = newPos - oldPos;
	return move;
}

double CollisionDeterminer::getAngleBetween(glm::vec3 a, glm::vec3 b) {
	// the angle between two vectors a and b in R3 is acos(a . b / ||a|| * ||b||), so:
	double multipliedLength = glm::length(a) * glm::length(b);
	double dotProduct = glm::dot(a, b);
	double cosAngle = dotProduct / multipliedLength;
	return glm::acos(cosAngle);
}

/*
====
Given a collided model, gets the normal of the collision plane
====
*/
glm::vec3 CollisionDeterminer::getCollisionPlaneNormal(Model* model) {
	std::vector<glm::vec3> boundingBox;
	//the top surface of a bounding box aligned to world axes
	boundingBox.push_back(glm::vec3(0, 10, 0));
	boundingBox.push_back(glm::vec3(10, 10, 0));
	boundingBox.push_back(glm::vec3(0, 10, 10));
	boundingBox.push_back(glm::vec3(10, 10, 10));

	glm::vec3 relative1 = (boundingBox[2] - boundingBox[0]);
	glm::vec3 relative2 = (boundingBox[1] - boundingBox[0]);

	//doing this to get relative vectors to get a sensible cross
	glm::vec3 cross = glm::cross(relative1, relative2);
	glm::vec3 normal = glm::normalize(cross);

	return normal;
}

/*
====
Given a move vector, and the normal of a collided plane,
returns a matrix which deflects the colliding object along the plane's surface.
Assumes that there is a collision - call after collision confirmed.
====
*/
glm::mat4 CollisionDeterminer::getDeflectionMatrix(glm::vec3 move, glm::vec3 planeNormal) {

	// IMPORTANT todo handle linearly dependant vectors - if you hit something dead on, the angle to the normal is 180 degrees, 
	// so the cross product of the collision angle with the surface normal is undefined.
	// check for this and bail out - no deflection needed, we can just stop dead for a head on collision.
	// add in a 'dead zone' around this.


	double angleFromNormal = getAngleBetween(planeNormal, move);
	float angleFromPlane = angleFromNormal - glm::radians(90.0);

	glm::vec3 rotationAxis = glm::cross(planeNormal, move);

	// GLM has a rotation function for an angle around an axis vector
	glm::mat4 deflectionMatrix = glm::rotate((angleFromPlane), rotationAxis);
	//glm::vec3 deflected = glm::vec3(deflectionMatrix * glm::vec4(move, 1));

	return deflectionMatrix;
}

//std::array<bool, 3>  CollisionDeterminer::noPlayerCollisions(glm::mat4 viewMatrix, std::map<std::string, Model*>* modelList) {
std::vector<Model*> CollisionDeterminer::getPlayerCollidedModels(glm::mat4 viewMatrix, std::map<std::string, Model*>* modelList) {
	// since we have the tentative view matrix, seems simplest to test player collisions in view space
	
	std::vector<Model*> collidedModels = std::vector<Model*>();

	bool noCollisions = true;

	//if we're doing this a lot set a class variable or pass it in
	glm::mat4 inverseView = glm::inverse(viewMatrix);

	glm::vec3 minPlayerBound = glm::vec3(inverseView * glm::vec4(-10, -10, -10, 1));
	glm::vec3 maxPlayerBound = glm::vec3(inverseView  * glm::vec4(10, 10, 10, 1));

	// get models from modelsmanager

	// for each one, convert the bounds to camera space and test them against the player bounds
	// almost certainly better to invert the view matrix, convert player bounds back to world space and do it there
	for (auto model : *modelList)
	{
		if (model.second->shouldCollisionCheck()) {
			std::vector<glm::vec3> modelBounds = model.second->getBoundingBox();

			if (modelBounds.size() == 2) {
				// need to be able to figure out which plane has been collided with
				// probably the nearest one
				// use the old and new move matrices to check

				//glm::vec3 minViewSpaceBound = glm::vec3(viewMatrix * glm::vec4(modelBounds[0], 1));
				//glm::vec3 maxViewSpaceBound = glm::vec3(viewMatrix * glm::vec4(modelBounds[1], 1));
				glm::vec3 minViewSpaceBound = modelBounds[0];
				glm::vec3 maxViewSpaceBound = modelBounds[1];
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
							collidedModels.push_back(model.second);
						}
					}
				}
			}
		}
	}
	return collidedModels;
}

/*
====
Takes in the old and new player movement matrices, figures out if there are any collisions,
does collision detections as needed, and returns a revised move matrix.
Calls itself recursively until no more collisions are found.
====
*/
glm::mat4 CollisionDeterminer::doPlayerCollisions(glm::mat4 oldViewMatrix, glm::mat4 newViewMatrix, std::map<std::string, Model*>* modelList) {
	std::vector<Model*> collidedModels = getPlayerCollidedModels(newViewMatrix, modelList);
	if (collidedModels.size() == 0) {
		return newViewMatrix;
	}
	for (unsigned i = 0; i < collidedModels.size(); i++) {
		glm::vec3 move = getMove(oldViewMatrix, newViewMatrix);
		glm::vec3 planeNormal = getCollisionPlaneNormal(collidedModels[i]);
		glm::mat4 deflectionMatrix = getDeflectionMatrix(move, planeNormal);
		newViewMatrix = deflectionMatrix * newViewMatrix;
	}
	return newViewMatrix;
}