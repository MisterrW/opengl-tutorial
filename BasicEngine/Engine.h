#pragma once
#include "Core\Init\Init_GLUT.h"
#include "Managers\SceneManager.h"
#include "Rendering\renderer.h"
namespace BasicEngine
{
	class Engine
	{

	public:
		Engine();
		~Engine();

		//OpenGL and manager init
		bool Init();

		//Loop
		void Run();

		//Getters
		Managers::SceneManager*  GetScene_Manager()  const;
		Managers::Shader_Manager* GetShader_Manager() const;
		Managers::ModelsManager* GetModels_Manager() const;

	private:
		Managers::SceneManager*  m_scene_manager;
		Managers::Shader_Manager* m_shader_manager;
		Managers::ModelsManager* m_models_manager;
	};
}