#pragma once
#include <vector>
#include "RE\ReEng.h"
class MyBoundingObjectClass
{
public:
    MyBoundingObjectClass(std::vector<vector3>);
    ~MyBoundingObjectClass();

    void SetVisible(bool);
    vector3 GetCenter();
    vector3 GetMin();
    vector3 GetMax();
private:
    std::vector<vector3> points;
    bool visible;
    vector3 center;
    vector3 min;
    vector3 max;
};

