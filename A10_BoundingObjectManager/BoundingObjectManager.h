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
	
private:
	BoundingObjectManager();
	~BoundingObjectManager();
<<<<<<< HEAD
	std::vector<MyBoundingObjectClass> objects;
	bool AABBvisibility;
=======
	void AddObject(String);
	void SwitchVisibility(int);
	int GetNumberObjects();
	void SetColor(int);
	void checkColliding();
	

>>>>>>> 092a56c32d4c22e2097b604451c1fa576c1cd7e4
};

