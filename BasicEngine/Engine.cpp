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

}

bool Engine::Init()
{
	WindowInfo window(std::string("in2gpu OpenGL Chapter 2 tutorial"),
		0, 0,
		1920, 1200, true);
	ContextInfo context(4, 3, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);


	glEnable(GL_CULL_FACE);

	shaderManager = Managers::ShaderManager();
	

	modelManager = new Managers::ModelManager();
	sceneManager = Managers::SceneManager();
	MovementManager movementManager = BasicEngine::Movement::MovementManager();

	sceneManager.initialise(modelManager);

	Init::Init_GLUT::init(window, context, frameBufferInfo);
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
}