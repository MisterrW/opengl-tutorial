#include "SceneManager.h"
using namespace BasicEngine::Managers;
using namespace BasicEngine::Rendering;


SceneManager::SceneManager()
{
	renderer = Renderer();
	movementManager = BasicEngine::Movement::MovementManager();
}

SceneManager::~SceneManager()
{
}

void SceneManager::initialise(BasicEngine::Managers::ModelManager* modelManager) {
	this->modelManager = modelManager;
};

void SceneManager::notifyBeginFrame()
{
	this->modelManager->update();
}

void SceneManager::drawScene(std::map<std::string, Model*>* modelList) {
	// get models from modelsmanager

	// iterate over them and pass them to renderer's draw method
	for (auto model : *modelList)
	{
		renderer.draw(model.second);
	}
}

void SceneManager::notifyDisplayFrame()
{
	std::map<std::string, Model*>* modelList = modelManager->getModels();
	movementManager.updateModelPositions(modelList);
	renderer.setViewMatrix(movementManager.getViewMatrix(modelList));
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	drawScene(modelList);
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
	float angle = 45.0f, near1 = 2.0f, far1 = 100000.0f;

	glm::mat4 projectionMatrix = glm::mat4();
	projectionMatrix[0][0] = 1.0f / (ar * tan(angle / 2.0f));
	projectionMatrix[1][1] = 1.0f / tan(angle / 2.0f);
	projectionMatrix[2][2] = (-near1 - far1) / (near1 - far1);
	projectionMatrix[2][3] = 1.0f;
	projectionMatrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);

	//gluPerspective(45.0,
	//	(1920.0/1080.0),
	//	0.2,
	//	20000);

	//glm::mat4 projectionMatrix = glm::mat4(1.0f);
	renderer.setProjectionMatrix(projectionMatrix);
}

void SceneManager::notifyKeyPress(char key, int x, int y) {
	movementManager.notifyKeyPress(key, x, y);
}

void SceneManager::notifyKeyUp(char key, int x, int y) {
	movementManager.notifyKeyUp(key, x, y);
}