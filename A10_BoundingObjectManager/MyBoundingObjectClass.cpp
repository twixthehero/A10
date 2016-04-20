#include "MyBoundingObjectClass.h"



MyBoundingObjectClass::MyBoundingObjectClass(std::vector<vector3> pts)
{
    points = pts;
}


MyBoundingObjectClass::~MyBoundingObjectClass()
{
}

void MyBoundingObjectClass::SetVisible(bool vis)
{
    visible = vis;
}

vector3 MyBoundingObjectClass::GetCenter()
{
    return center;
}

vector3 MyBoundingObjectClass::GetMin()
{
    return min;
}

vector3 MyBoundingObjectClass::GetMax()
{
    return max;
}
