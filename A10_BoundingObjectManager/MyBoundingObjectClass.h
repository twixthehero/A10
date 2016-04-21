#pragma once
#include <vector>
#include "RE\ReEng.h"
#include "RE\ReEngAppClass.h"

using namespace ReEng;

class MyBoundingObjectClass : public ReEngAppClass
{
public:
    MyBoundingObjectClass(std::vector<vector3>);
    ~MyBoundingObjectClass();

    void SetVisible(bool);
    vector3 GetCenter();
    vector3 GetMin();
    vector3 GetMax();

	matrix4 GetSetWorld(matrix4);
	void SetColor(vector3);
	void Draw();
	bool CheckCollision(MyBoundingObjectClass* const a_pOther);
	typedef ReEngAppClass super;
private:
    std::vector<vector3> points;
    bool visible;

    vector3 center;
    vector3 min;
    vector3 max;
	matrix4 worldMatrix;
	vector3 color;
	vector3 size;

};

