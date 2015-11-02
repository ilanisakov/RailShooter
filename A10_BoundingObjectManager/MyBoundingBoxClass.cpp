/*
GROUP:
Ilan Isakov
Marty Kurtz
Mary Spencer
*/


#include "MyBoundingBoxClass.h"
//  MyBoundingBoxClass
void MyBoundingBoxClass::Init(void)
{
	m_m4ToWorld = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_v3HalfWidth = vector3(0.0f);
}
void MyBoundingBoxClass::Swap(MyBoundingBoxClass& other)
{
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
}
void MyBoundingBoxClass::Release(void)
{

}
//The big 3
MyBoundingBoxClass::MyBoundingBoxClass(std::vector<vector3> a_lVectorList)
{
	//Init the default values
	Init();

	//Count the points of the incoming list
	uint nVertexCount = a_lVectorList.size();

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3Max = m_v3Min = a_lVectorList[0];

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (m_v3Min.x > a_lVectorList[nVertex].x) //If min is larger than current
			m_v3Min.x = a_lVectorList[nVertex].x;
		else if (m_v3Max.x < a_lVectorList[nVertex].x)//if max is smaller than current
			m_v3Max.x = a_lVectorList[nVertex].x;

		if (m_v3Min.y > a_lVectorList[nVertex].y) //If min is larger than current
			m_v3Min.y = a_lVectorList[nVertex].y;
		else if (m_v3Max.y < a_lVectorList[nVertex].y)//if max is smaller than current
			m_v3Max.y = a_lVectorList[nVertex].y;

		if (m_v3Min.z > a_lVectorList[nVertex].z) //If min is larger than current
			m_v3Min.z = a_lVectorList[nVertex].z;
		else if (m_v3Max.z < a_lVectorList[nVertex].z)//if max is smaller than current
			m_v3Max.z = a_lVectorList[nVertex].z;
	}

	//with the max and the min we calculate the center
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth.x = glm::distance(vector3(m_v3Min.x, 0.0f, 0.0f), vector3(m_v3Max.x, 0.0f, 0.0f)) / 2.0f;
	m_v3HalfWidth.y = glm::distance(vector3(0.0f, m_v3Min.y, 0.0f), vector3(0.0f, m_v3Max.y, 0.0f)) / 2.0f;
	m_v3HalfWidth.z = glm::distance(vector3(0.0f, 0.0f, m_v3Min.z), vector3(0.0f, 0.0f, m_v3Max.z)) / 2.0f;
	
}
MyBoundingBoxClass::MyBoundingBoxClass(MyBoundingBoxClass const& other)
{
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3HalfWidth = other.m_v3HalfWidth;
}
MyBoundingBoxClass& MyBoundingBoxClass::operator=(MyBoundingBoxClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyBoundingBoxClass temp(other);
		Swap(temp);
	}
	return *this;
}
MyBoundingBoxClass::~MyBoundingBoxClass(){ Release(); };
//Accessors
void MyBoundingBoxClass::SetModelMatrix(matrix4 a_m4ToWorld)
{ 
	m_m4ToWorld = a_m4ToWorld;

	//compute aligned box points
	vector3 boxVec[8];
	boxVec[0] = m_v3Min;
	boxVec[1] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	boxVec[2] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	boxVec[3] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	boxVec[4] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	boxVec[5] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	boxVec[6] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);
	boxVec[7] = m_v3Max;

	//Change to WOrld Coords
	for (int i = 0; i < 8; i++)
	{
		//printf("BOX_I[%d] X[%.3f] Y[%.3f] Z[%.3f]\n", i,boxVec[i].x,boxVec[i].y,boxVec[i].z);
		boxVec[i] = vector3(m_m4ToWorld * vector4(boxVec[i], 1.0f));
		//printf("BOXNEW_I[%d] X[%.3f] Y[%.3f] Z[%.3f]\n", i, boxVec[i].x, boxVec[i].y, boxVec[i].z);
	}

	m_v3MinNEW = m_v3MaxNEW = boxVec[0];

	//Get the max and min out of the list
	for (uint i = 0; i < 8; i++)
	{
		if (m_v3MinNEW.x > boxVec[i].x) //If min is larger than current
			m_v3MinNEW.x = boxVec[i].x;
		else if (m_v3MaxNEW.x < boxVec[i].x)//if max is smaller than current
			m_v3MaxNEW.x = boxVec[i].x;

		if (m_v3MinNEW.y > boxVec[i].y) //If min is larger than current
			m_v3MinNEW.y = boxVec[i].y;
		else if (m_v3MaxNEW.y < boxVec[i].y)//if max is smaller than current
			m_v3MaxNEW.y = boxVec[i].y;

		if (m_v3MinNEW.z > boxVec[i].z) //If min is larger than current
			m_v3MinNEW.z = boxVec[i].z;
		else if (m_v3MaxNEW.z < boxVec[i].z)//if max is smaller than current
			m_v3MaxNEW.z = boxVec[i].z;
	}

	//Center is the same
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;
	//Update halfWidth for new box
	m_v3HalfWidthNEW.x = glm::distance(vector3(m_v3MinNEW.x, 0.0f, 0.0f), vector3(m_v3MaxNEW.x, 0.0f, 0.0f)) / 2.0f;
	m_v3HalfWidthNEW.y = glm::distance(vector3(0.0f, m_v3MinNEW.y, 0.0f), vector3(0.0f, m_v3MaxNEW.y, 0.0f)) / 2.0f;
	m_v3HalfWidthNEW.z = glm::distance(vector3(0.0f, 0.0f, m_v3MinNEW.z), vector3(0.0f, 0.0f, m_v3MaxNEW.z)) / 2.0f;

}
matrix4 MyBoundingBoxClass::GetModelMatrix(void){ return m_m4ToWorld; }
vector3 MyBoundingBoxClass::GetCenterLocal(void){ return m_v3Center; }
vector3 MyBoundingBoxClass::GetCenterGlobal(void){ return vector3(m_m4ToWorld * vector4(m_v3Center,1.0f)); }
vector3 MyBoundingBoxClass::GetHalfWidth(bool aligned)
{
	if (aligned)
		return m_v3HalfWidthNEW;
	else
		return m_v3HalfWidth;
}
//--- Non Standard Singleton Methods
bool MyBoundingBoxClass::IsColliding(MyBoundingBoxClass* const a_pOther)
{
	//Get all vectors in global space
//	vector3 v3Min = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
//	vector3 v3Max = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

//	vector3 v3MinO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Min, 1.0f));
//	vector3 v3MaxO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Max, 1.0f));

	//New box is already is global space
	vector3 v3Min = m_v3MinNEW;
	vector3 v3Max = m_v3MaxNEW;
	vector3 v3MinO = a_pOther->m_v3MinNEW;
	vector3 v3MaxO = a_pOther->m_v3MaxNEW;

	/*
	Are they colliding?
	For boxes we will assume they are colliding, unless at least one of the following conditions is not met
	*/
	bool bColliding = true;
	
	//Check for X
	if (v3Max.x < v3MinO.x)
		bColliding = false;
	if (v3Min.x > v3MaxO.x)
		bColliding = false;

	//Check for Y
	if (v3Max.y < v3MinO.y)
		bColliding = false;
	if (v3Min.y > v3MaxO.y)
		bColliding = false;

	//Check for Z
	if (v3Max.z < v3MinO.z)
		bColliding = false;
	if (v3Min.z > v3MaxO.z)
		bColliding = false;

	return bColliding;
}