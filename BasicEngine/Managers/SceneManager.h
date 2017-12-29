#pragma once
#include "Shader_Manager.h"
#include "ModelsManager.h"
#include "../Core/Init/IListener.h"
namespace Managers
{
	class SceneManager : public Core::IListener
	{
	public:
		SceneManager();
		~SceneManager();

		virtual void notifyBeginFrame();
		virtual void notifyDisplayFrame();
		virtual void notifyEndFrame();
		virtual void notifyReshape(int width,
			int height,
			int previous_width,
			int previous_height);
	private:
		Managers::Shader_Manager* shader_manager;
		Managers::ModelsManager* modelsManager;
	};
}