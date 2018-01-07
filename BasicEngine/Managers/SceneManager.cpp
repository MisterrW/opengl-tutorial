#include "SceneManager.h"
using namespace BasicEngine::Managers;
using namespace BasicEngine::Rendering;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);

	shader_manager = new Shader_Manager();

	renderer = Renderer();
}

SceneManager::~SceneManager()
{
	delete shader_manager;
	delete modelsManager;
}

void SceneManager::SetModelsManager(BasicEngine::Managers::ModelsManager* models_m)
{
	modelsManager = models_m;
	movementManager.setModelsManager(modelsManager);
}

void SceneManager::notifyBeginFrame()
{
	modelsManager->update();
}

void SceneManager::drawScene() {
	// get models from modelsmanager
	std::map<std::string, Model*> modelList = modelsManager->getModels();

	// iterate over them and pass them to renderer's draw method
	for (auto model : modelList)
	{
		renderer.draw(model.second);
	}
}

void SceneManager::notifyDisplayFrame()
{
	renderer.setViewMatrix(movementManager.getViewMatrix());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	drawScene();
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
	float angle = 45.0f, near1 = 0.1f, far1 = 20000.0f;

	glm::mat4 projection_matrix = glm::mat4();
	projection_matrix[0][0] = 1.0f / (ar * tan(angle / 2.0f));
	projection_matrix[1][1] = 1.0f / tan(angle / 2.0f);
	projection_matrix[2][2] = (-near1 - far1) / (near1 - far1);
	projection_matrix[2][3] = 1.0f;
	projection_matrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);

	renderer.setProjectionMatrix(projection_matrix);
}

void SceneManager::notifyKeyPress(char key, int x, int y) {
	movementManager.notifyKeyPress(key, x, y);
}

void SceneManager::notifyKeyUp(char key, int x, int y) {
	movementManager.notifyKeyUp(key, x, y);
};