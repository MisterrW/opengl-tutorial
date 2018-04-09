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
#include "../Managers/MonsterManager.h"
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

			void initialise(Managers::ModelManager* modelManager, BasicEngine::Managers::MonsterManager* monsterManager);

			virtual void updateGameState();
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
			std::chrono::steady_clock::time_point last;
			void drawScene(std::map<std::string, Model*>* models);
			void drawMonsters(std::map<std::string, Monster*>* monsters);
			BasicEngine::Managers::ModelManager* modelManager;
			BasicEngine::Managers::MonsterManager* monsterManager;
			BasicEngine::Rendering::Renderer renderer;
			BasicEngine::Movement::MovementManager movementManager;
		};
	}
}