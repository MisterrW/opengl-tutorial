#pragma once
#include "CollisionDeterminer.h"
#include "../Managers/ModelManager.h"
#define GLM_ENABLE_EXPERIMENTAL
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
Line-triangle intersection code courtesy of softSurfer, http://geomalgorithms.com/a06-_intersect-2.html#intersect3D_RayTriangle()
====
*/

// Copyright 2001 softSurfer, 2012 Dan Sunday
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.


// some of the below invalid as (for now) using glm::vec3 for vectors and simply std::vector<glm::vec3> for lines and triangles

// Assume that classes are already given for the objects:
//    Point and Vector with
//        coordinates {float x, y, z;}
//        operators for:
//            == to test  equality
//            != to test  inequality
//            (Vector)0 =  (0,0,0)         (null vector)
//            Point   = Point ± Vector
//            Vector =  Point - Point
//            Vector =  Scalar * Vector    (scalar product)
//            Vector =  Vector * Vector    (cross product)
//    Line and Ray and Segment with defining  points {Point P0, P1;}
//        (a Line is infinite, Rays and  Segments start at P0)
//        (a Ray extends beyond P1, but a  Segment ends at P1)
//    Plane with a point and a normal {Point V0; Vector  n;}
//    Triangle with defining vertices {Point V0, V1, V2;}
//    Polyline and Polygon with n vertices {int n;  Point *V;}
//        (a Polygon has V[n]=V[0])
//===================================================================


#define SMALL_NUM   0.00000001 // anything that avoids division overflow
// dot product (3D) which allows vector operations in arguments
#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)



// intersect3D_RayTriangle(): find the 3D intersection of a ray with a triangle
//    Input:  a ray R, and a triangle T
//    Output: *I = intersection point (when it exists)
//    Return: -1 = triangle is degenerate (a segment or point)
//             0 =  disjoint (no intersect)
//             1 =  intersect in unique point I1
//             2 =  are in the same plane
int CollisionDeterminer::intersect3D_RayTriangle(const std::vector<glm::vec3> lineSeg, const std::vector<glm::vec3> triangle, glm::vec3* I) {
	glm::vec3    u, v, n;              // triangle vectors
	glm::vec3    dir, w0, w;           // ray vectors
	float        r, a, b;              // params to calc ray-plane intersect

									   // get triangle edge vectors and plane normal
	u = triangle[1] - triangle[0];
	v = triangle[2] - triangle[0];
	n = glm::cross(u, v);              // cross product
	if (n == glm::vec3(0, 0, 0))             // triangle is degenerate
		return -1;                  // do not deal with this case

	dir = lineSeg[1] - lineSeg[0];              // ray direction vector
	w0 = lineSeg[0] - triangle[0];
	a = -dot(n, w0);
	b = dot(n, dir);
	if (fabs(b) < SMALL_NUM) {     // ray is  parallel to triangle plane
		if (a == 0)                 // ray lies in triangle plane
			return 2;
		else return 0;              // ray disjoint from plane
	}

	// get intersect point of ray with triangle plane
	r = a / b;
	if (r < 0.0 || r > 1.0)                    // r < 0.0 => ray goes away from triangle . for a segment, also test if (r > 1.0) => no intersect
		return 0;                   // => no intersect

	*I = lineSeg[0] + r * dir;            // intersect point of ray and plane

										  // is I inside T?
	float    uu, uv, vv, wu, wv, D;
	uu = dot(u, u);
	uv = dot(u, v);
	vv = dot(v, v);
	w = *I - triangle[0];
	wu = dot(w, u);
	wv = dot(w, v);
	D = uv * uv - uu * vv;

	// get and test parametric coords
	float s, t;
	s = (uv * wv - vv * wu) / D;
	if (s < 0.0 || s > 1.0)         // I is outside T
		return 0;
	t = (uv * wu - uu * wv) / D;
	if (t < 0.0 || (s + t) > 1.0)  // I is outside T
		return 0;

	return 1;                       // I is in T
}

/*
====
Given a collided model, gets the normal of the collision plane
====
*/
glm::vec3 CollisionDeterminer::getCollisionPlaneNormal(Model* model, std::vector<glm::vec3> lineSeg) {
	
	std::vector<Triangle> boundingBoxTriangles = model->getBoundingBoxTriangles();
	for (unsigned i = 0; i < boundingBoxTriangles.size(); i++) {
		glm::vec3 intersection = glm::vec3(0, 0, 0);
		//todo modify this function to accept the triangle so we don't have to recalculate the normal
		if ( intersect3D_RayTriangle(lineSeg, boundingBoxTriangles[i].getVertices(), &intersection) > 0) {
			return boundingBoxTriangles[i].getNormal();
		}
	}
	return boundingBoxTriangles[0].getNormal();
	// todo fast-moving object could cross two planes, and we want to check we have the right one ie first one crossed

}

/*
====
Given a move vector, and the normal of a collided plane,
returns a matrix which deflects the colliding object along the plane's surface.
Assumes that there is a collision - so only call after collision confirmed.
====
*/
glm::mat4 CollisionDeterminer::getDeflectionMatrix(glm::vec3 move, glm::vec3 planeNormal, double angleFromNormal) {
	glm::mat4 deflectionMatrix;

	// IMPORTANT todo handle linearly dependant vectors - if you hit something dead on, the angle to the normal is 180 degrees, 
	// so the cross product of the collision angle with the surface normal is undefined.
	// check for this and bail out - no deflection needed, we can just stop dead for a head on collision.
	// add in a 'dead zone' around this.

	
	glm::vec3 rotationAxis = glm::cross(planeNormal, move);
	
	float angleFromPlane = angleFromNormal - glm::radians(90.0);

	
	// GLM has a rotation function for an angle around an axis vector
	// but it's experimental - TODO write one based on Rodrigues' rotation matrix

	deflectionMatrix = glm::rotate(angleFromPlane, rotationAxis);

	//glm::vec3 deflected = glm::vec3(deflectionMatrix * glm::vec4(move, 1));



	return deflectionMatrix;
}

/*
====
Bounding-box based collision detector
Returns a vector of the models which collide with the position represented by the view matrix
====
*/
std::vector<Model*> CollisionDeterminer::getCollidedModels(const std::map<std::string, Model*>* modelList, glm::vec3 minBound, glm::vec3 maxBound) {

	std::vector<Model*> collidedModels = std::vector<Model*>();

	for (auto model : *modelList)
	{
		if (model.second->shouldCollisionCheck()) {
			std::vector<glm::vec3> modelBounds = model.second->getBoundingBox();

			if (modelBounds.size() == 2) {
				glm::vec3 minViewSpaceBound = modelBounds[0];
				glm::vec3 maxViewSpaceBound = modelBounds[1];
				if ((minViewSpaceBound.x < minBound.x && minBound.x < maxViewSpaceBound.x) ||
					(minViewSpaceBound.x < maxBound.x && maxBound.x < maxViewSpaceBound.x) ||
					(minBound.x < minViewSpaceBound.x && minViewSpaceBound.x < maxBound.x) ||
					(minBound.x < maxViewSpaceBound.x && maxViewSpaceBound.x < maxBound.x)) {

					if ((minViewSpaceBound.y < minBound.y && minBound.y < maxViewSpaceBound.y) ||
						(minViewSpaceBound.y < maxBound.y && maxBound.y < maxViewSpaceBound.y) ||
						(minBound.y < minViewSpaceBound.y && minViewSpaceBound.y < maxBound.y) ||
						(minBound.y < maxViewSpaceBound.y && maxViewSpaceBound.y < maxBound.y)) {

						if ((minViewSpaceBound.z < minBound.z && minBound.z < maxViewSpaceBound.z) ||
							(minViewSpaceBound.z < maxBound.z && maxBound.z < maxViewSpaceBound.z) ||
							(minBound.z < minViewSpaceBound.z && minViewSpaceBound.z < maxBound.z) ||
							(minBound.z < maxViewSpaceBound.z && maxViewSpaceBound.z < maxBound.z)) {
							collidedModels.push_back(model.second);
						}
					}
				}
			}
		}
	}
	return collidedModels;
}

std::vector<glm::vec3> CollisionDeterminer::getLineSegmentFromViewMatrices(glm::mat4 oldViewMatrix, glm::mat4 newViewMatrix) {

	std::vector<glm::vec3> lineSeg = std::vector<glm::vec3>();

	glm::vec4 origin = glm::vec4(0, 0, 0, 1);
	glm::mat4 oldInv = glm::inverse(oldViewMatrix);
	glm::mat4 newInv = glm::inverse(newViewMatrix);
	glm::vec3 oldPos = glm::vec3(oldInv * origin);
	glm::vec3 newPos = glm::vec3(newInv * origin);
	lineSeg.push_back(oldPos);
	lineSeg.push_back(newPos);

	return lineSeg;
}

/*
====
Takes in the old and new player movement matrices, figures out if there are any collisions,
does collision detections as needed, and returns a revised move matrix.
Should call itself recursively until no more collisions are found.
====
*/
glm::mat4 CollisionDeterminer::doPlayerCollisions(const glm::mat4 oldViewMatrix, glm::mat4 newViewMatrix, const std::map<std::string, Model*>* modelList) {
	
	// need to invert to get from view to world position matrix
	glm::mat4 inverseView = glm::inverse(newViewMatrix);
	std::vector<Model*> collidedModels = getCollidedModels(
		modelList, 
		glm::vec3(inverseView * glm::vec4(0, 0, 0, 1)),
		glm::vec3(inverseView  * glm::vec4(0, 0, 0, 1)));
	if (collidedModels.size() == 0) {
		return newViewMatrix;
	}
	for (unsigned i = 0; i < collidedModels.size(); i++) {
		glm::vec3 move = getMove(oldViewMatrix, newViewMatrix);
		std::vector<glm::vec3> lineSeg = getLineSegmentFromViewMatrices(oldViewMatrix, newViewMatrix);
		glm::vec3 planeNormal = getCollisionPlaneNormal(collidedModels[i], lineSeg);
		double collisionAngleFromPlaneNormal = getAngleBetween(planeNormal, move);
		
		if (collisionAngleFromPlaneNormal < 3.13 || collisionAngleFromPlaneNormal > 3.15) {
			glm::mat4 deflectionMatrix = getDeflectionMatrix(move, planeNormal, collisionAngleFromPlaneNormal);
			// so we have our deflection matrix, which is a rotation matrix.
			// If we do it this way, we'd need to reorient, apply the move, and orient back again. invDeflect * newView * deflect.
			// newViewMatrix = deflectionMatrix * newViewMatrix;

			glm::mat4 inverseDeflectionMatrix = glm::inverse(deflectionMatrix);
			//glm::mat4 deflectedViewMatrix = inverseDeflectionMatrix * (newViewMatrix * deflectionMatrix);
			glm::mat4 deflectedViewMatrix = deflectionMatrix * (newViewMatrix * inverseDeflectionMatrix);
			newViewMatrix = deflectedViewMatrix;
		}
		else {
			newViewMatrix = oldViewMatrix;
		}
	}
	return newViewMatrix;
}

glm::mat4 CollisionDeterminer::doModelCollisions(Model* model, const glm::mat4 thisFrameMoveMatrix, const glm::mat4 oldMoveMatrix, glm::mat4 newMoveMatrix, const std::map<std::string, Model*>* models) {

	glm::mat4 deflectedMoveThisFrame = glm::mat4(thisFrameMoveMatrix);

	std::vector<Model*> collidedModels = getCollidedModels(
		models,
		glm::vec3(newMoveMatrix * glm::vec4(0, 0, 0, 1)),
		glm::vec3(newMoveMatrix * glm::vec4(0, 0, 0, 1)));
	for (int i = 0; i < collidedModels.size(); i++) {
		if (collidedModels[i] == model) {
			collidedModels.erase(collidedModels.begin() +i);
		}
	}
	if (collidedModels.size() == 0) {
		return newMoveMatrix;
	}
	for (unsigned i = 0; i < collidedModels.size(); i++) {
		glm::vec3 move = getMove(oldMoveMatrix, newMoveMatrix);
		std::vector<glm::vec3> lineSeg = getLineSegmentFromViewMatrices(oldMoveMatrix, newMoveMatrix);
		glm::vec3 planeNormal = getCollisionPlaneNormal(collidedModels[i], lineSeg);
		double collisionAngleFromPlaneNormal = getAngleBetween(planeNormal, move);

		if ((collisionAngleFromPlaneNormal < 3.13 || collisionAngleFromPlaneNormal > 3.15) && collisionAngleFromPlaneNormal > 0.01) {
			glm::mat4 deflectionMatrix = getDeflectionMatrix(move, planeNormal, collisionAngleFromPlaneNormal);
			// so we have our deflection matrix, which is a rotation matrix.
			// If we do it this way, we'd need to reorient, apply the move, and orient back again. invDeflect * newView * deflect.
			// newViewMatrix = deflectionMatrix * newViewMatrix;

			glm::mat4 inverseDeflectionMatrix = glm::inverse(deflectionMatrix);
			//glm::mat4 deflectedViewMatrix = inverseDeflectionMatrix * (newViewMatrix * deflectionMatrix);
			// deflectedMoveThisFrame = deflectionMatrix * (deflectedMoveThisFrame * inverseDeflectionMatrix);
			deflectedMoveThisFrame = inverseDeflectionMatrix * deflectedMoveThisFrame * deflectionMatrix;
			newMoveMatrix = oldMoveMatrix * deflectedMoveThisFrame;
		}
		else {
			newMoveMatrix = oldMoveMatrix;
		}
		//newMoveMatrix = oldMoveMatrix;
	}
	return newMoveMatrix;
};