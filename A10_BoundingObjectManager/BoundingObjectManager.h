#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingObjectClass.h"
#include <cstring>

class BoundingObjectManager : public ReEngAppClass
{
public:
	typedef ReEngAppClass super;
	static BoundingObjectManager* instance;
	static BoundingObjectManager* GetInstance();
	static void ReleaseInstance();
	void AddObject(String);
	void SwitchAABBVisibility();
	void SetVisibility(int, bool);
	int GetNumberObjects();
	void SetColor(int, vector3);
	void Render();
	void Render(int);
	void checkColliding();
	
private:
	BoundingObjectManager();
	~BoundingObjectManager();
	std::vector<MyBoundingObjectClass> objects;
	bool AABBvisibility;
};

