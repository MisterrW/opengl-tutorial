/*
=================
The models manager maintains lists of models which make up the scene.
In a draw cycle, it returns its model list to the scene manager
which passes them to the renderer to be drawn.
=================
*/

#pragma once
#include <map>
#include "Shader_Manager.h"
#include "../Rendering/IGameObject.h"
#include "../Rendering/Models/Model.h"
#include "../Rendering/Models/Triangle.h"
#include "../Rendering/Models/Quad.h"

using namespace BasicEngine::Rendering;
using namespace BasicEngine::Rendering::Models;

namespace BasicEngine
{
	namespace Managers
	{
		class ModelsManager
		{
		public:
			ModelsManager();
			~ModelsManager();

			void update();

			// void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
			
			// returns all models for rendering
			std::map<std::string, Model*> getModels();
			const Model& getModel(const std::string& gameModelName) const;
			void deleteModel(const std::string& gameModelName);

			void setModel(const std::string& gameObjectName, Model* gameObject);

		private:
			// NOTE this may become a bottleneck, better to use vector
			std::map<std::string, Model*> gameModelList;
		};
	}
}