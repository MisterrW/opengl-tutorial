#pragma once
#include <map>
#include "Shader_Manager.h"
#include "../Rendering/IGameObject.h"
#include "../Rendering/Models/Triangle.h"
#include "../Rendering/Models/Quad.h"

using namespace BasicEngine::Rendering;

namespace BasicEngine
{
	namespace Managers
	{
		class ModelsManager
		{
		public:
			ModelsManager();
			~ModelsManager();

			void Update();
			
			// 3D
			void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
			const IGameObject& GetModel(const std::string& gameModelName) const;
			void DeleteModel(const std::string& gameModelName);
			

			// NDC
			void Draw();
			void DeleteModel_NDC(const std::string& gameModelName);
			const IGameObject& GetModel_NDC(const std::string& gameModelName) const;

			void SetModel(const std::string& gameObjectName, IGameObject* gameObject);

		private:
			// NOTE this may become a bottleneck, better to use vector

			// 3D
			std::map<std::string, IGameObject*> gameModelList;

			// NDC
			std::map<std::string, IGameObject*> gameModelList_NDC;
		};
	}
}