/*
=================
The engine class is the interface / API for clients of this library.
Outside of the engine project, interaction with the engine is only through public methods of this class.
=================
*/

#pragma once
#include "Core/Init/Init_GLUT.h"
#include "Managers/SceneManager.h"
#include "Managers/ShaderManager.h"
#include "Managers/ModelManager.h"
#include "Rendering/renderer.h"

namespace BasicEngine
{
	class Engine
	{

	public:
		Engine();
		~Engine();

		//OpenGL and manager initialisation
		bool Init();

		//Loop
		void Run();

		//IO for client
		void createProgram(const std::string& ShaderName,
			const std::string& VertexShaderFilename,
			const std::string& FragmentShaderFilename);
		const GLuint getProgram(const std::string&);
		void setModel(const std::string& gameObjectName, Model* gameObject);

	private:
		Managers::SceneManager sceneManager;
		Managers::ShaderManager shaderManager;
		Managers::ModelManager* modelManager;
	};
}