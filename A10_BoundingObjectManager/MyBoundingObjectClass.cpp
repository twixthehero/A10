#include "MyBoundingObjectClass.h"
#include "limits"

MyBoundingObjectClass::MyBoundingObjectClass(std::vector<vector3> pts)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	points = pts;

	if (points.size() > 0)
	{
		min = points[0];
		max = points[0];
	}

	for (uint i = 0; i < points.size(); i++)
	{
		if (points[i].x > max.x)
			max.x = points[i].x;
		else if (points[i].x < min.x)
			min.x = points[i].x;

		if (points[i].y > max.y)
			max.y = points[i].y;
		else if (points[i].y < min.y)
			min.y = points[i].y;

		if (points[i].z > max.z)
			max.z = points[i].z;
		else if (points[i].z < min.z)
			min.z = points[i].z;
	}

	center = (max + min) / 2.0f;
	//radius = glm::distance(m_v3Center, max);
	size.x = glm::distance(vector3(min.x, 0.0, 0.0), vector3(max.x, 0.0, 0.0));
	size.y = glm::distance(vector3(0.0, min.y, 0.0), vector3(0.0, max.y, 0.0));
	size.z = glm::distance(vector3(0.0f, 0.0, min.z), vector3(0.0, 0.0, max.z));
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

//Get and Set the "Model to World" matrix of the BO
matrix4 MyBoundingObjectClass::GetSetWorld(matrix4 arg_World)
{
	worldMatrix = arg_World;
	//recalc min/max
	for (uint i = 0; i < points.size(); i++)
	{
		vector3 point = vector3(worldMatrix * vector4(points[i], 1.0f));

		if (i == 0)
			min = max = vector3(point.x, point.y, point.z);

		if (point.x > max.x)
			max.x = point.x;
		else if (point.x < min.x)
			min.x = point.x;

		if (point.y > max.y)
			max.y = point.y;
		else if (point.y < min.y)
			min.y = point.y;

		if (point.z > max.z)
			max.z = point.z;
		else if (point.z < min.z)
			min.z = point.z;
	}

	float tmp;

	//fix issue where max goes under min and vice versa
	if (max.x < min.x)
	{
		tmp = min.x;
		min.x = max.x;
		max.x = tmp;
	}
	if (max.y < min.y)
	{
		tmp = min.y;
		min.y = max.y;
		max.y = tmp;
	}
	if (max.z < min.z)
	{
		tmp = min.z;
		min.z = max.z;
		max.z = tmp;
	}

	center = (max + min) / 2.0f;
	//m_fRadius = glm::distance(m_v3Center, max);
	size.x = glm::distance(vector3(min.x, 0.0, 0.0), vector3(max.x, 0.0, 0.0));
	size.y = glm::distance(vector3(0.0, min.y, 0.0), vector3(0.0, max.y, 0.0));
	size.z = glm::distance(vector3(0.0f, 0.0, min.z), vector3(0.0, 0.0, max.z));

	return worldMatrix;
}

//sets color of the BO
void MyBoundingObjectClass::SetColor(vector3 arg_Color)
{
	color = arg_Color;
}

void MyBoundingObjectClass::Draw()
{
	m_pMeshMngr->AddCubeToQueue(
		glm::translate(center) *
		glm::scale(size), color, WIRE);
}

bool MyBoundingObjectClass::CheckCollision(MyBoundingObjectClass* const a_pOther)
{
	vector3 vMin1 = min;
	vector3 vMax1 = max;
	vector3 vMin2 = a_pOther->min;
	vector3 vMax2 = a_pOther->max;
    bool collide = true;

	//Check for X
    if (vMax1.x < vMin2.x || vMin1.x > vMax2.x)
        collide = false;

	//Check for Y
	if (vMax1.y < vMin2.y || vMin1.y > vMax2.y)
		collide = false;

	//Check for Z
	if (vMax1.z < vMin2.z || vMin1.z > vMax2.z)
		collide = false;

    //if arbb collides
    if (collide)
    {
        //sat
        std::vector<vector3> normals = std::vector<vector3>();
        std::vector<vector3> corners = CalcPoints();
        std::vector<vector3> corners2 = a_pOther->CalcPoints();

        //calc normals with no duplicates b1
        for (int i = 1; i <= corners.size(); i++)
        {
            vector3 n = corners[i % corners.size()] - corners[i - 1];
            float tmp = n.x;
            n.x = n.y;
            n.y = -tmp;
            bool add = true;

            for (int k = 0; k < normals.size(); k++)
            {
                if (normals[k] == n || normals[k] == -n)
                {
                    add = false;
                    break;
                }
            }

            if (add)
            {
                normals.push_back(n);
            }
        }

        //calc normals with no duplicates b2
        for (int i = 1; i <= corners2.size(); i++)
        {
            vector3 n = corners2[i % corners2.size()] - corners2[i - 1];
            float tmp = n.x;
            n.x = n.y;
            n.y = -tmp;
            bool add = true;

            for (int k = 0; k < normals.size(); k++)
            {
                if (normals[k] == n || normals[k] == -n)
                {
                    add = false;
                    break;
                }
            }

            if (add)
            {
                normals.push_back(n);
            }
        }

        //for each normal, proj each other normal and see if touching
        for (int i = 0; i < normals.size(); i++)
        {
            if (Intersection(corners, corners2, normals[i]))
            {
                collide = true;
                break;
            }
        }
    }

	return collide;
}

std::vector<vector3> MyBoundingObjectClass::CalcPoints()
{
	std::vector<vector3> pts;
	//000
	pts.push_back(min);
	//001
	pts.push_back(vector3(min.x, min.y, max.z));
    //101
    pts.push_back(vector3(max.x, min.y, max.z));
    //100
    pts.push_back(vector3(max.x, min.y, min.z));
	//110
	pts.push_back(vector3(max.x, max.y, min.z));
    //111
    pts.push_back(max);
	//011
	pts.push_back(vector3(min.x, max.y, max.z));
    //010
    pts.push_back(vector3(min.x, max.y, min.z));
	return pts;
}

bool MyBoundingObjectClass::Intersection(std::vector<vector3> aPoints, std::vector<vector3> bPoints, vector3 axis)
{
    //checks for cross product of (0,0,0)
    if (axis == vector3(0, 0, 0))
    {
        return true;
    }

    //sets some Min and Max
    float aMin = std::numeric_limits<float>::max();
    float aMax = -std::numeric_limits<float>::max();
    float bMin = std::numeric_limits<float>::max();
    float bMax = -std::numeric_limits<float>::max();

    //calculate min and max
    for (int i = 0; i < 8; i++)
    {
        float aDistance = glm::dot(aPoints[i], axis);
        aMin = (aDistance < aMin) ? aDistance : aMin;
        aMax = (aDistance > aMax) ? aDistance : aMax;

        float bDistance = glm::dot(bPoints[i], axis);
        bMin = (bDistance < bMin) ? bDistance : bMin;
        bMax = (bDistance > bMax) ? bDistance : bMax;
    }

    //check intersection
    float longDis = glm::max(aMax, bMax) - glm::min(aMin, bMin);
    float sumDis = aMax - aMin + bMax - bMin;

    //return true/false
    return longDis < sumDis;
}