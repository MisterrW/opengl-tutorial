#include "Engine.h"
using namespace BasicEngine;
using namespace Core;

Engine::Engine()
{

}

//You can set params for init
bool Engine::Init()
{
	WindowInfo window(std::string("in2gpu OpenGL Chapter 2 tutorial"),
		400, 200,
		800, 600, true);
	ContextInfo context(4, 3, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);

	Init::Init_GLUT::init(window, context, frameBufferInfo);

	m_scene_manager = new Managers::SceneManager();

	Init::Init_GLUT::SetListener(m_scene_manager);

	//this was created in  scene manager constructor, now copy here
	m_shader_manager = new Managers::Shader_Manager();
	m_shader_manager->CreateProgram("colorShader",
		"..\\BasicEngine\\Shaders\\Vertex_Shader.glsl",
		"..\\BasicEngine\\Shaders\\Fragment_Shader.glsl");

	if (m_scene_manager && m_shader_manager)
	{
		m_models_manager = new Managers::ModelsManager();
		m_scene_manager->SetModelsManager(m_models_manager);
	}
	else
	{
		return false;
	}

	return true;
}

//Create the loop
void Engine::Run()
{
	Init::Init_GLUT::Run();
}

Managers::SceneManager* Engine::GetScene_Manager() const
{
	return m_scene_manager;
}

Managers::Shader_Manager* Engine::GetShader_Manager() const
{
	return m_shader_manager;
}

Managers::ModelsManager* Engine::GetModels_Manager() const
{
	return m_models_manager;
}

Engine::~Engine()
{
	if (m_scene_manager)
		delete m_scene_manager;

	if (m_shader_manager)
		delete m_shader_manager;

	if (m_models_manager)
		delete m_models_manager;
}