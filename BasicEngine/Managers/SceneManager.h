/*
=================
The scene manager handles callbacks from the glut main loop.
Each draw cycle, it retrieves the current model list from the model manager
These models are passed to the renderer to draw.
=================
*/

#pragma once
#include "Shader_Manager.h"
#include "ModelsManager.h"
#include "../Rendering/Renderer.h"
#include "../Movement/PositionManager.h"
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
			// void SetRenderer(Rendering::Renderer renderer);

			virtual void notifyBeginFrame();
			virtual void notifyDisplayFrame();
			virtual void notifyEndFrame();
			virtual void notifyReshape(int width,
				int height,
				int previous_width,
				int previous_height);
			virtual void notifyKeyPress(char key, int x, int y);
			virtual void notifyKeyUp(char key, int x, int y);
		private:
			void drawScene();
			BasicEngine::Managers::Shader_Manager* shader_manager;
			BasicEngine::Managers::ModelsManager* modelsManager;
			BasicEngine::Rendering::Renderer renderer;
			BasicEngine::Movement::PositionManager* PositionManager;
		};
	}
}