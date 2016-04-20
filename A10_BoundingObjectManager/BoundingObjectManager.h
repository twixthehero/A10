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
	std::vector<MyBoundingObjectClass> objects;
private:
	BoundingObjectManager();
	~BoundingObjectManager();
	void AddObject(String);
	void SwitchVisibility(int);
	int GetNumberObjects();
	void SetColor(int);
};

