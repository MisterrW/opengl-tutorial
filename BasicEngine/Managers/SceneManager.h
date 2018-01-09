/*
=================
The scene manager handles callbacks from the glut main loop.
Each draw cycle, it retrieves the current model list from the model manager
These models are passed to the renderer to draw.
=================
*/

#pragma once
#include "ShaderManager.h"
#include "ModelManager.h"
#include "../Rendering/Renderer.h"
#include "../Movement/MovementManager.h"
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

			void initialise(Managers::ModelManager* modelManager);

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
			void drawScene(std::map<std::string, Model*>* modelList);
			BasicEngine::Managers::ModelManager* modelManager;
			BasicEngine::Rendering::Renderer renderer;
			BasicEngine::Movement::MovementManager movementManager;
		};
	}
}