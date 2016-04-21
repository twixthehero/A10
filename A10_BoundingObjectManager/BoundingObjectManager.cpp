#include "BoundingObjectManager.h"

BoundingObjectManager* BoundingObjectManager::instance = nullptr;

BoundingObjectManager::BoundingObjectManager()
{
	AABBvisibility = true;
}


BoundingObjectManager::~BoundingObjectManager()
{
}

void BoundingObjectManager::AddObject(String model)
{
	m_pMeshMngr->LoadModel(model, "Model");
	objects.push_back(MyBoundingObjectClass(m_pMeshMngr->GetVertexList("Model")));
}

void BoundingObjectManager::SwitchAABBVisibility()
{
	if (AABBvisibility) AABBvisibility = false;
	else AABBvisibility = true;
}

void BoundingObjectManager::SetVisibility(int index, bool vis)
{
	objects[index].SetVisible(vis);
}

int BoundingObjectManager::GetNumberObjects()
{
	return objects.size();
}

void BoundingObjectManager::SetColor(int index,vector3 color)
{
	objects[index].SetColor(color);
}

void BoundingObjectManager::Render()
{
	for (int i = 0; i < objects.size(); i++) {
		objects[i].Draw();
	}
}

void BoundingObjectManager::Render(int index)
{
	objects[index].Draw();
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