#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingObjectClass.h"
#include <cstring>

class BoundingObjectManager
{
public:
	MeshManagerSingleton* m_pMeshMngr;

	BoundingObjectManager();
	~BoundingObjectManager();
	static BoundingObjectManager* instance;
	static BoundingObjectManager* GetInstance();
	static void ReleaseInstance();
	void AddObject(String,String);
	void SwitchAABBVisibility();
	void SetVisibility(int, bool);
	int GetNumberObjects();
	void SetColor(int, vector3);
	void Render();
	void Render(int);
	void CheckColliding();
	std::vector<MyBoundingObjectClass*> objects;

private:
	bool AABBvisibility;
};

