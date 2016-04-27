#include "BoundingObjectManager.h"

BoundingObjectManager* BoundingObjectManager::instance = nullptr;

void BoundingObjectManager::AddObject(String model, String nick)
{
	m_pMeshMngr->LoadModel(model, nick);
	objects.push_back(new MyBoundingObjectClass(m_pMeshMngr->GetVertexList(nick)));
}

void BoundingObjectManager::SwitchAABBVisibility()
{
	if (AABBvisibility) AABBvisibility = false;
	else AABBvisibility = true;
}

void BoundingObjectManager::SetVisibility(int index, bool vis)
{
	objects[index]->SetVisible(vis);
}

int BoundingObjectManager::GetNumberObjects()
{
	return objects.size();
}

void BoundingObjectManager::SetColor(int index,vector3 color)
{
	objects[index]->SetColor(color);
}

void BoundingObjectManager::Render()
{
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->Draw();
	}
}

void BoundingObjectManager::Render(int index)
{
	objects[index]->Draw();
}

BoundingObjectManager::BoundingObjectManager()
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}

BoundingObjectManager::~BoundingObjectManager()
{
}

BoundingObjectManager* BoundingObjectManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new BoundingObjectManager();
	}
	return instance;
}

void BoundingObjectManager::ReleaseInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void BoundingObjectManager::CheckColliding() {
	for (int i = 0; i < objects.size() - 1; i++) {
		for (int k = 1; k < objects.size(); k++) {
			if(objects[i]->CheckCollision(objects[k]) == 0){
				objects[i]->SetColor(RERED);
				objects[k]->SetColor(RERED);
			}
			else if (objects[i]->CheckCollision(objects[k]) >= 4) {
				m_pMeshMngr->AddPlaneToQueue(objects[k]->worldMatrix, REBLUE);
				objects[i]->SetColor(REWHITE);
				objects[k]->SetColor(REWHITE);
			}
			else if (objects[i]->CheckCollision(objects[k]) >= 2) {
				m_pMeshMngr->AddPlaneToQueue(objects[k]->worldMatrix, REGREEN);
				objects[i]->SetColor(REWHITE);
				objects[k]->SetColor(REWHITE);
			}
			else{
				m_pMeshMngr->AddPlaneToQueue(objects[k]->worldMatrix, RERED);
				objects[i]->SetColor(REWHITE);
				objects[k]->SetColor(REWHITE);
				
			}
		}
	}
}