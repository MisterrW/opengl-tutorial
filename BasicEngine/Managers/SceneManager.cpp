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

void SceneManager::initialise(BasicEngine::Managers::ModelManager* modelManager, BasicEngine::Managers::MonsterManager* monsterManager) {
	this->modelManager = modelManager;
	this->monsterManager = monsterManager;
};

void SceneManager::notifyBeginFrame()
{
	this->modelManager->update();
}

//duplicate for monsters
void SceneManager::drawScene(std::map<std::string, Model*>* models) {
	// get models from modelsmanager

	// iterate over them and pass them to renderer's draw method
	for (auto model : *models)
	{
		renderer.draw(model.second);
	}
}

//duplicate for monsters
void SceneManager::drawMonsters(std::map<std::string, Monster*>* monsters) {
	// iterate over them and pass them to renderer's draw method
	for (auto monster : *monsters)
	{
		renderer.drawMonster(monster.second);
	}
}

// everything that needs to update in 'real time' should happen here - this is called 30 times a second, OR as often as the frame rate lets us.
// unhook this from the glut render loop - we want to control physics / world updates separately from graphics rendering
void SceneManager::updateGameState()
{
	std::map<std::string, Model*>* modelList = modelManager->getModels();
	glm::vec3 playerPosition = movementManager.getPlayerPosition();
	glm::vec3 playerOrientation = movementManager.getPlayerOrientation();
	monsterManager->doMonsterThinking(playerPosition, playerOrientation, modelList);

	std::map<std::string, Monster*>* monsters = monsterManager->getMonsters();
	movementManager.updateModelPositions(modelList);
	movementManager.updateMonsterPositions(monsters, modelList);
	glm::mat4 viewMatrix = movementManager.getViewMatrix(modelList, monsters);
	renderer.setViewMatrix(viewMatrix); // model list required for player collision detection
}

void SceneManager::notifyDisplayFrame()
{
	typedef std::chrono::steady_clock clock;
	typedef std::chrono::milliseconds ms;
	using TimePoint = std::chrono::time_point<clock, ms>;

	TimePoint now = std::chrono::time_point_cast<ms>(clock::now());

	std::chrono::duration<float, std::milli> timeSinceLastCall = now - this->last;

	if (timeSinceLastCall.count() > 16.666667) // approx 30 per second
	{
		last = now;
		updateGameState();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	std::map<std::string, Model*>* models = modelManager->getModels();
	drawScene(models);
	std::map<std::string, Monster*>* monsters = monsterManager->getMonsters();
	drawMonsters(monsters);
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