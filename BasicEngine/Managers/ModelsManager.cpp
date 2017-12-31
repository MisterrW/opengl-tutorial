#include "ModelsManager.h"

using namespace BasicEngine::Managers;
using namespace BasicEngine::Rendering;

ModelsManager::ModelsManager()
{
	////triangle game object
	//Models::Triangle* triangle = new Models::Triangle();
	//triangle->SetProgram(Shader_Manager::GetProgram("colorShader"));
	//triangle->Create();
	//gameModelList_NDC["triangle"] = triangle;

	////quad game object
	//Models::Quad* quad = new Models::Quad();
	//quad->SetProgram(Shader_Manager::GetProgram("colorShader"));
	//quad->Create();
	//gameModelList_NDC["quad"] = quad;

}

ModelsManager::~ModelsManager()
{
	//auto -it's a map iterator
	for (auto model : gameModelList)
	{
		delete model.second;
	}
	gameModelList.clear();

	for (auto model : gameModelList_NDC)
	{
		delete model.second;
	}
	gameModelList_NDC.clear();
}

void ModelsManager::Update()
{
	//auto -it's a map iterator
	for (auto model : gameModelList)
	{
		model.second->Update();
	}
	for (auto model : gameModelList_NDC)
	{
		model.second->Update();
	}
}

// for NDC models
void ModelsManager::Draw()
{
	//auto -it's a map iterator
	for (auto model : gameModelList)
	{
		model.second->Draw();
	}
}

// for 3d models
void ModelsManager::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	//auto -it's a map iterator
	for (auto model : gameModelList)
	{
		model.second->Draw(projection_matrix, view_matrix);
	}
}

void ModelsManager::DeleteModel_NDC(const std::string& gameModelName)
{
	IGameObject* model = gameModelList_NDC[gameModelName];
	model->Destroy();
	gameModelList_NDC.erase(gameModelName);
}

void ModelsManager::DeleteModel(const std::string& gameModelName)
{
	IGameObject* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);
}

const IGameObject& ModelsManager::GetModel_NDC(const std::string& gameModelName) const
{
	return (*gameModelList_NDC.at(gameModelName));
}

const IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const
{
	return (*gameModelList.at(gameModelName));
}

void ModelsManager::SetModel(const std::string& gameObjectName, IGameObject* gameObject)
{
	gameModelList[gameObjectName.c_str()] = gameObject;
}