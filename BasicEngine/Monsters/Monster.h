#pragma once
#include <vector>
#include <map>
#include "Mind.h"
#include "../Models/Model.h"
#include "../../../Dependencies/include/glm/glm.hpp"

using namespace BasicEngine::Models;

namespace BasicEngine
{
	namespace Monsters
	{
		class Monster
		{
		public:
			Monster();
			Monster(BasicEngine::Models::Model* model, Mind* mind);
			void Destroy();

			// pass thru fns to mind to think

			// pass thru fns to model to render etc
			void Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
			glm::mat4 getPositionMatrix();
			glm::mat4 getThisFrameMoveMatrix();
			void setPositionMatrix(glm::mat4 positionMatrix);
			void setThisFrameMoveMatrix(glm::mat4 thisFrameMoveMatrix);
			Model* getModel();
			void think(glm::vec3 playerPosition, glm::vec3 playerOrientation, std::map<std::string, Model*>* models, std::map<std::string, Monster*>* monsters);

		private:
			BasicEngine::Models::Model* model;
			Mind* mind;
		};
	}
}