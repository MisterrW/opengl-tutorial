#pragma once
#include "Shader_Manager.h"
#include "ModelsManager.h"
#include "../Core/Init/IListener.h"
namespace BasicEngine
{
	namespace Managers
	{
		class SceneManager : public BasicEngine::Core::IListener
		{
		public:
			SceneManager();
			~SceneManager();

			void SetModelsManager(Managers::ModelsManager*& models_manager);

			virtual void notifyBeginFrame();
			virtual void notifyDisplayFrame();
			virtual void notifyEndFrame();
			virtual void notifyReshape(int width,
				int height,
				int previous_width,
				int previous_height);
		private:
			BasicEngine::Managers::Shader_Manager* shader_manager;
			BasicEngine::Managers::ModelsManager* modelsManager;
			glm::mat4 projection_matrix;
			glm::mat4 view_matrix;
		};
	}
}