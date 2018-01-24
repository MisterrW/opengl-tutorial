#include "Engine.h"
#include "Physics/CollisionDeterminer.h"
#include "Movement/MovementManager.h"

using namespace BasicEngine;
using namespace Core;
using namespace Rendering;
using namespace Physics;
using namespace Movement;
using namespace Managers;

Engine::Engine()
{
	shaderManager = Managers::ShaderManager();
	modelManager = new Managers::ModelManager();
	sceneManager = Managers::SceneManager();
	sceneManager.initialise(modelManager);
}

bool Engine::Init()
{
	WindowInfo window(std::string("engine"),
		0, 0,
		1920, 1080, true);
	ContextInfo context(4, 3, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);

	//glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);

	Init::Init_GLUT::init(window, context, frameBufferInfo);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	Init::Init_GLUT::SetListener(&sceneManager);

	shaderManager.CreateProgram("colorShader",
		"..\\BasicEngine\\Shaders\\Vertex_Shader.glsl",
		"..\\BasicEngine\\Shaders\\Fragment_Shader.glsl");

	return true;
}

void Engine::setModel(const std::string& gameObjectName, Model* gameObject)
{
	modelManager->setModel(gameObjectName, gameObject);
}

void Engine::createProgram(const std::string& shaderName,
	const std::string& vertexShaderFilename,
	const std::string& fragmentShaderFilename)
{
	shaderManager.CreateProgram(shaderName, vertexShaderFilename, fragmentShaderFilename);
}

const GLuint Engine::getProgram(const std::string& programName)
{
	return shaderManager.GetProgram(programName);
}

//Create the loop
void Engine::Run()
{
	Init::Init_GLUT::Run();
}


Engine::~Engine()
{
	delete modelManager;
}