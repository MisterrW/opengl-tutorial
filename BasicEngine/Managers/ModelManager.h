/*
=================
The models manager maintains a list of models which make up the scene.
In a draw cycle, it returns its model list to the scene manager,
which passes them to the renderer to be drawn.
=================
*/

#pragma once
#include <map>
#include "ShaderManager.h"
#include "../Models/IGameObject.h"
#include "../Models/Model.h"

using namespace BasicEngine::Models;

namespace BasicEngine
{
	namespace Managers
	{
		class ModelManager
		{
		public:
			ModelManager();
			~ModelManager();

			void update();

			// void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
			
			// returns all models for rendering
			std::map<std::string, Model*>* getModels();
			const Model& getModel(const std::string& gameModelName) const;
			void deleteModel(const std::string& gameModelName);

			void setModel(const std::string& gameObjectName, Model* gameObject);

		private:
			// NOTE this may become a bottleneck, better to use vector
			std::map<std::string, Model*> gameModelList;
			ModelManager(const ModelManager&); // no implementation 
			ModelManager& operator=(const ModelManager&); // no implementation 
		};
	}
}