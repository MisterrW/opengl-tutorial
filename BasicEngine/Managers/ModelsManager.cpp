#include "ModelsManager.h"
#include "../Models/Model.h"

using namespace BasicEngine::Managers;

ModelsManager::ModelsManager()
{

}

ModelsManager::~ModelsManager()
{
	//auto -it's a map iterator
	for (auto model : gameModelList)
	{
		delete model.second;
	}
	gameModelList.clear();

}

std::map<std::string, Model*> ModelsManager::getModels() {
	return gameModelList;
}

const Model& ModelsManager::getModel(const std::string& gameModelName) const
{
	return (*gameModelList.at(gameModelName));
}

void ModelsManager::deleteModel(const std::string& gameModelName)
{
	Model* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);
}

void ModelsManager::setModel(const std::string& gameObjectName, Model* gameObject)
{
	gameModelList[gameObjectName.c_str()] = gameObject;
}

void ModelsManager::update()
{
	//auto -it's a map iterator
	for (auto model : gameModelList)
	{
		model.second->Update();
	}

}

//const IGameObject& ModelsManager::GetModel_NDC(const std::string& gameModelName) const
//{
//	return (*gameModelList_NDC.at(gameModelName));
//}


//for (auto model : gameModelList_NDC)
//{
//	model.second->Update();
//}

/*for (auto model : gameModelList_NDC)
{
delete model.second;
}
gameModelList_NDC.clear();*/

// for NDC models
//void ModelsManager::Draw()
//{
//	//auto -it's a map iterator
//	for (auto model : gameModelList)
//	{
//		model.second->Draw();
//	}
//}

// for 3d models
//void ModelsManager::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
//{
//	//auto -it's a map iterator
//	for (auto model : gameModelList)
//	{
//		model.second->Draw(projection_matrix, view_matrix);
//	}
//}

//void ModelsManager::DeleteModel_NDC(const std::string& gameModelName)
//{
//	IGameObject* model = gameModelList_NDC[gameModelName];
//	model->Destroy();
//	gameModelList_NDC.erase(gameModelName);
//}