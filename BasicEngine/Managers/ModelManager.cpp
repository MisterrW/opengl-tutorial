#include "ModelManager.h"
#include "../Models/Model.h"

using namespace BasicEngine::Managers;

ModelManager::ModelManager()
{

}

ModelManager::~ModelManager()
{
	//auto -it's a map iterator
	for (auto model : gameModelList)
	{
		delete model.second;
	}
	gameModelList.clear();

}

std::map<std::string, Model*> ModelManager::getModels() {
	return this->gameModelList;
}

const Model& ModelManager::getModel(const std::string& gameModelName) const
{
	return (*this->gameModelList.at(gameModelName));
}

void ModelManager::deleteModel(const std::string& gameModelName)
{
	Model* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);
}

void ModelManager::setModel(const std::string& gameObjectName, Model* gameObject)
{
	this->gameModelList[gameObjectName.c_str()] = gameObject;
}

void ModelManager::update()
{
	//auto -it's a map iterator
	for (auto model : this->gameModelList)
	{
		model.second->Update();
	}

}

//const IGameObject& ModelManager::GetModel_NDC(const std::string& gameModelName) const
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
//void ModelManager::Draw()
//{
//	//auto -it's a map iterator
//	for (auto model : gameModelList)
//	{
//		model.second->Draw();
//	}
//}

// for 3d models
//void ModelManager::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
//{
//	//auto -it's a map iterator
//	for (auto model : gameModelList)
//	{
//		model.second->Draw(projection_matrix, view_matrix);
//	}
//}

//void ModelManager::DeleteModel_NDC(const std::string& gameModelName)
//{
//	IGameObject* model = gameModelList_NDC[gameModelName];
//	model->Destroy();
//	gameModelList_NDC.erase(gameModelName);
//}