#include "SceneManager.h"
using namespace BasicEngine::Managers;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);

	shader_manager = new Shader_Manager();
	//shader_manager->CreateProgram("colorShader",
	//	"Shaders\\Vertex_Shader.glsl",
	//	"Shaders\\Fragment_Shader.glsl");
	
	// move this definition to camera class
	view_matrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 10.0f, 1.0f);

	
	modelsManager = new ModelsManager();
}

SceneManager::~SceneManager()
{
	delete shader_manager;
	delete modelsManager;
}

void SceneManager::SetModelsManager(BasicEngine::Managers::ModelsManager*& models_m)
{
	modelsManager = models_m;
}

void SceneManager::notifyBeginFrame()
{
	modelsManager->Update();
}

void SceneManager::notifyDisplayFrame()
{
	// call camera.cpp getViewMatrix here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	modelsManager->Draw();
	modelsManager->Draw(projection_matrix, view_matrix);
}

void SceneManager::notifyEndFrame()
{
	//nothing here for the moment
}

void SceneManager::notifyReshape(int width, int height,
	int previous_width, int previous_height)
{
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) /
		(float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;

	projection_matrix[0][0] = 1.0f / (ar * tan(angle / 2.0f));
	projection_matrix[1][1] = 1.0f / tan(angle / 2.0f);
	projection_matrix[2][2] = (-near1 - far1) / (near1 - far1);
	projection_matrix[2][3] = 1.0f;
	projection_matrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);
}