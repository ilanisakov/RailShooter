/////////////////////////////////////////////////////////////////////
// File: MyBOClass.cpp
// DSA2 PokemanSafari_M4
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////
#include "MyBOClass.h"

/////////////////////////////////////////////////////////////////////
//Method: Init
//Usage: Allocates member fields
//Arguments: ---
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOClass::Init(void)
{
	m_m4ToWorld = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_v3CenterG = vector3(0.0f);
	m_v3MinG = vector3(0.0f);
	m_v3MaxG = vector3(0.0f);

	m_v3HalfWidth = vector3(0.0f);
	m_v3HalfWidthG = vector3(0.0f);

	m_fRadius = 0.0f;

	m_nStoredIndex = 0;
}

/////////////////////////////////////////////////////////////////////
//Method: Swap
//Usage: Changes object contents for other object's
//Arguments:
//other -> object to swap content from
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOClass::Swap(MyBOClass& other)
{
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_v3CenterG, other.m_v3CenterG);
	std::swap(m_v3MinG, other.m_v3MinG);
	std::swap(m_v3MaxG, other.m_v3MaxG);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
	std::swap(m_v3HalfWidthG, other.m_v3HalfWidthG);

	std::swap(m_fRadius, other.m_fRadius);
	std::swap(m_sName, other.m_sName);
	std::swap(m_nStoredIndex, other.m_nStoredIndex);
}

/////////////////////////////////////////////////////////////////////
//Method: Release
//Usage: Deallocates member fields
//Arguments: ---
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOClass::Release(void)
{
	//Nothing todo...
}

/////////////////////////////////////////////////////////////////////
//Method: MyBOClass
//Usage: Constructor
//Arguments: 
//   a_lVectorList - list object verts
//   name - object name
//Output: class object
/////////////////////////////////////////////////////////////////////
MyBOClass::MyBOClass(std::vector<vector3> a_lVectorList, String name)
{
	//Init the default values
	Init();
	m_sName = name;
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

	m_fRadius = glm::distance(m_v3Center, m_v3Max);
	//another way of doing this, except that with it the sphere just surrounds the object making the
	//pretest kind of useless
	//m_fRadius = 0;
	//for (uint nVertex = 0; nVertex < nVertexCount; nVertex++)
	//{
	//	float fDistance = glm::distance(m_v3Center, a_lVectorList[nVertex]);
	//	if (m_fRadius < fDistance)
	//		m_fRadius = fDistance;
	//}

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth = (m_v3Max - m_v3Min) / 2.0f;

	m_v3MaxG = m_v3Max;
	m_v3MinG = m_v3Min;
	m_v3CenterG = m_v3Center;
	m_v3HalfWidthG = m_v3HalfWidth;
}

/////////////////////////////////////////////////////////////////////
//Method: MyBOClass
//Usage: Copy Constructor
//Arguments: class object to copy
//Output: class object instance
/////////////////////////////////////////////////////////////////////
MyBOClass::MyBOClass(MyBOClass const& other)
{
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3CenterG = other.m_v3CenterG;
	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;
	m_v3HalfWidthG = other.m_v3HalfWidthG;

	m_fRadius = other.m_fRadius;
	m_sName = other.m_sName;
	m_nStoredIndex = other.m_nStoredIndex;
}

/////////////////////////////////////////////////////////////////////
//Method: operator=
//Usage: Copy Assignment Operator
//Arguments: class object to copy
//Output: ---
/////////////////////////////////////////////////////////////////////
MyBOClass& MyBOClass::operator=(MyBOClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyBOClass temp(other);
		Swap(temp);
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////
//Method: ~MyBOClass
//Usage: Destructor
//Arguments: ---
//Output: ---
/////////////////////////////////////////////////////////////////////
MyBOClass::~MyBOClass()
{
	Release(); 
}

/////////////////////////////////////////////////////////////////////
//Method: SetToWorldMatrix
//Usage: Sets the Bounding Object into world coordinates
//Arguments:
//matrix4 a_m4ToWorld -> Model to World matrix
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	//If there are no changes in the Model Matrix there is no need
	//of doing further calculations
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	//Calculate the vertex that makes the Object
	vector3 v3Corner[8];
	v3Corner[0] = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z);
	v3Corner[1] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	v3Corner[2] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	v3Corner[3] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);

	v3Corner[4] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	v3Corner[5] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	v3Corner[6] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	v3Corner[7] = vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z);
	//Get vectors in global space
	for (uint nVertex = 0; nVertex < 8; nVertex++)
	{
		v3Corner[nVertex] = vector3(m_m4ToWorld * vector4(v3Corner[nVertex], 1.0f));
	}

	//Get the max and min out of the list
	m_v3MaxG = m_v3MinG = v3Corner[0];
	for (uint nVertex = 1; nVertex < 8; nVertex++)
	{
		if (m_v3MinG.x > v3Corner[nVertex].x) //If min is larger than current
			m_v3MinG.x = v3Corner[nVertex].x;
		else if (m_v3MaxG.x < v3Corner[nVertex].x)//if max is smaller than current
			m_v3MaxG.x = v3Corner[nVertex].x;

		if (m_v3MinG.y > v3Corner[nVertex].y) //If min is larger than current
			m_v3MinG.y = v3Corner[nVertex].y;
		else if (m_v3MaxG.y < v3Corner[nVertex].y)//if max is smaller than current
			m_v3MaxG.y = v3Corner[nVertex].y;

		if (m_v3MinG.z > v3Corner[nVertex].z) //If min is larger than current
			m_v3MinG.z = v3Corner[nVertex].z;
		else if (m_v3MaxG.z < v3Corner[nVertex].z)//if max is smaller than current
			m_v3MaxG.z = v3Corner[nVertex].z;
	}
	m_v3CenterG = (m_v3MinG + m_v3MaxG) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidthG = (m_v3MaxG - m_v3MinG) / 2.0f;

	m_fRadius = glm::distance(m_v3CenterG, m_v3MaxG);
}

/////////////////////////////////////////////////////////////////////
//Method: GetRadius
//Usage: Gets the Bounding Object's radius
//Arguments: ---
//Output: float -> Radous of the BO
/////////////////////////////////////////////////////////////////////
float MyBOClass::GetRadius(void)
{ 
	return m_fRadius; 
}

/////////////////////////////////////////////////////////////////////
//Method: GetToWorldMatrix
//Usage: Gets the Bounding Object into world coordinates
//Arguments:---
//Output: matrix4 -> Model to World matrix
/////////////////////////////////////////////////////////////////////
matrix4 MyBOClass::GetModelMatrix(void)
{ 
	return m_m4ToWorld; 
}

/////////////////////////////////////////////////////////////////////
//Method: GetCenter
//Usage: Gets the Bounding Object's center in local coordinates
//Arguments: ---
//Output: vector3 -> Center's of the Object in local coordinates
/////////////////////////////////////////////////////////////////////
vector3 MyBOClass::GetCenterLocal(void)
{ 
	return m_v3Center; 
}

/////////////////////////////////////////////////////////////////////
//Method: GetCenterGlobal
//Usage: Gets the Bounding Object's center in global coordinates
//Arguments: ---
//Output: vector3 -> Center's of the Object in global coordinates
/////////////////////////////////////////////////////////////////////
vector3 MyBOClass::GetCenterGlobal(void)
{ 
	return m_v3CenterG; 
}

/////////////////////////////////////////////////////////////////////
//Method: GetHalfWidth
//Usage: Gets the Bounding Object sizes for all sides (divided in half)
//Arguments: ---
//Output: vector3 -> HalfWidth Vector
/////////////////////////////////////////////////////////////////////
vector3 MyBOClass::GetHalfWidth(void)
{ 
	return m_v3HalfWidth; 
}

/////////////////////////////////////////////////////////////////////
//Method: GetHalfWidthG
//Usage: Gets the Bounding Object sizes for all sides (divided in half) reoriented
//Arguments: ---
//Output: vector3 -> HalfWidth Vector
/////////////////////////////////////////////////////////////////////
vector3 MyBOClass::GetHalfWidthG(void)
{ 
	return m_v3HalfWidthG; 
}

/////////////////////////////////////////////////////////////////////
// GetMaxG() - returns max corner point of BO
//
// @return - max point of BO
/////////////////////////////////////////////////////////////////////
vector3 MyBOClass::GetMaxG()
{
	return m_v3MaxG;
}

/////////////////////////////////////////////////////////////////////
// GetMinG() - returns min corner point of BO
//
// @return - min point of BO
/////////////////////////////////////////////////////////////////////
vector3 MyBOClass::GetMinG()
{
	return m_v3MinG;
}

/////////////////////////////////////////////////////////////////////
// GetName() - returns BO's name
//
// @return - BO's unique name
/////////////////////////////////////////////////////////////////////
String MyBOClass::GetName()
{
	return m_sName;
}

/////////////////////////////////////////////////////////////////////
// SetStoredIndex() - saves the index BO is stored in in manager
//
// @param - (idx) the stored index of the BO in the manager
/////////////////////////////////////////////////////////////////////
void MyBOClass::SetStoredIndex(int idx)
{
	if (idx > -1)
	    m_nStoredIndex = idx;
}

/////////////////////////////////////////////////////////////////////
// GetStoredIndex() - returns index of BO stored in manager
//
// @return - idx in manager list
/////////////////////////////////////////////////////////////////////
int MyBOClass::GetStoredIndex()
{
	return m_nStoredIndex;
}

/////////////////////////////////////////////////////////////////////
//Method: IsColliding
//Usage: Asks if there is a collision with another Bounding Object Object
//Arguments:
//MyBOClass* const a_pOther -> Other object to check collision with
//Output: bool -> check of the collision
/////////////////////////////////////////////////////////////////////
bool MyBOClass::IsColliding(MyBOClass* const a_pOther)
{
	//Get all vectors in global space
	vector3 v3Min = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 v3Max = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	vector3 v3MinO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Min, 1.0f));
	vector3 v3MaxO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Max, 1.0f));

	/*
	Are they colliding?
	For Objects we will assume they are colliding, unless at least one of the following conditions is not met
	*/
	//first check the bounding sphere, if that is not colliding we can guarantee that there are no collision
	//if ((m_fRadius + a_pOther->m_fRadius) < glm::distance(m_v3CenterG, a_pOther->m_v3CenterG))
	//	return false;
	//If the distance was smaller it might be colliding


	//Do precheck with AABO
	bool bColliding = true;
	
	//Check for X
	if (m_v3MaxG.x < a_pOther->m_v3MinG.x)
		bColliding = false;
	if (m_v3MinG.x > a_pOther->m_v3MaxG.x)
		bColliding = false;

	//Check for Y
	if (m_v3MaxG.y < a_pOther->m_v3MinG.y)
		bColliding = false;
	if (m_v3MinG.y > a_pOther->m_v3MaxG.y)
		bColliding = false;

	//Check for Z
	if (m_v3MaxG.z < a_pOther->m_v3MinG.z)
		bColliding = false;
	if (m_v3MinG.z > a_pOther->m_v3MaxG.z)
		bColliding = false;

	if (bColliding == false)
		return false;

	return SAT(a_pOther);
}

/////////////////////////////////////////////////////////////////////
//USAGE: Determines the collision with an incoming object using the SAT
// ARGUMENTS :
//- MyBOClass* const a_pOther->Other object to check collision with
//OUTPUT : result of the collision
/////////////////////////////////////////////////////////////////////
bool MyBOClass::SAT(MyBOClass* const a_pOther)
{
	// Get the information of this object
	vector3 v3CenterGlobalA = GetCenterGlobal();
	matrix4 mToWorldA = GetModelMatrix();
	vector3 v3RotationA[3];
	v3RotationA[0] = vector3(mToWorldA[0][0], mToWorldA[0][1], mToWorldA[0][2]);
	v3RotationA[1] = vector3(mToWorldA[1][0], mToWorldA[1][1], mToWorldA[1][2]);
	v3RotationA[2] = vector3(mToWorldA[2][0], mToWorldA[2][1], mToWorldA[2][2]);

	//Get the information of the other object
	vector3 v3CenterGlobalB = a_pOther->GetCenterGlobal();
	matrix4 mToWorldB = a_pOther->GetModelMatrix();
	vector3 v3RotationB[3];
	v3RotationB[0] = vector3(mToWorldB[0][0], mToWorldB[0][1], mToWorldB[0][2]);
	v3RotationB[1] = vector3(mToWorldB[1][0], mToWorldB[1][1], mToWorldB[1][2]);
	v3RotationB[2] = vector3(mToWorldB[2][0], mToWorldB[2][1], mToWorldB[2][2]);

	float fCenterAToMiddle, fCenterBToMiddle;
	glm::mat3 m3Rotation, m3RotationAbs;

	// Compute rotation matrix expressing b in a's coordinate frame
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
		m3Rotation[i][j] = glm::dot(v3RotationA[i], v3RotationB[j]);

	// Compute translation vector v3Distance (this is the distance between both centers)
	vector3 v3Distance = v3CenterGlobalB - v3CenterGlobalA; //distance in global space
	// Bring translation into a's coordinate frame
	v3Distance = vector3(glm::dot(v3Distance, v3RotationA[0]), glm::dot(v3Distance, v3RotationA[1]), glm::dot(v3Distance, v3RotationA[2])); //distance in A's local
	// their cross product is (near) null (see the orange book for details)
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
		m3RotationAbs[i][j] = std::abs(m3Rotation[i][j]) + 0.0001f;

	// Test axes L = AX <- 0
	fCenterAToMiddle = m_v3HalfWidth.x;
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[0][0] + a_pOther->m_v3HalfWidth.y * m3RotationAbs[0][1] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[0][2];
	if (std::abs(v3Distance.x) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		vector3 v3Center;
		matrix4 m4WorldToLocal = glm::inverse(m_m4ToWorld);
		if (m_v3CenterG.x < a_pOther->m_v3CenterG.x)
		{
			vector3 v3OtherMinInA = vector3(m4WorldToLocal * vector4(a_pOther->m_v3MinG, 1.0f));
			v3Center = vector3(m4WorldToLocal * vector4(m_v3MaxG, 1.0f)) + v3OtherMinInA;
		}
		else
		{
			vector3 v3OtherMaxInA = vector3(m4WorldToLocal * vector4(a_pOther->m_v3MaxG, 1.0f));
			v3Center = vector3(m4WorldToLocal * vector4(m_v3MinG, 1.0f)) + v3OtherMaxInA;
		}
		v3Center /= 2.0f;

		matrix4 m4Space = glm::translate(m_m4ToWorld, v3Center) * glm::rotate(IDENTITY_M4, 90.0f, REAXISY);
		m_pMeshMngr->AddPlaneToQueue(m4Space * glm::scale(vector3(5.0f)), RERED);
#endif
		return false;
	}

	// Test axes L = AY <- 1
	fCenterAToMiddle = m_v3HalfWidth.y;
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[1][0] + a_pOther->m_v3HalfWidth.y * m3RotationAbs[1][1] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[1][2];
	if (std::abs(v3Distance.y) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		vector3 v3Center;
		matrix4 m4WorldToLocal = glm::inverse(m_m4ToWorld);
		if (m_v3CenterG.y < a_pOther->m_v3CenterG.y)
		{
			vector3 v3OtherMinInA = vector3(m4WorldToLocal * vector4(a_pOther->m_v3MinG, 1.0f));
			v3Center = vector3(m4WorldToLocal * vector4(m_v3MaxG, 1.0f)) + v3OtherMinInA;
		}
		else
		{
			vector3 v3OtherMaxInA = vector3(m4WorldToLocal * vector4(a_pOther->m_v3MaxG, 1.0f));
			v3Center = vector3(m4WorldToLocal * vector4(m_v3MinG, 1.0f)) + v3OtherMaxInA;
		}
		v3Center /= 2.0f;
		matrix4 m4Space = glm::translate(m_m4ToWorld, v3Center) * glm::rotate(IDENTITY_M4, 90.0f, REAXISX);
		m_pMeshMngr->AddPlaneToQueue(m4Space * glm::scale(vector3(5.0f)), REGREEN);
#endif
		return false;
	}

	// Test axes L = AZ <- 2
	fCenterAToMiddle = m_v3HalfWidth.z;
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[2][0] + a_pOther->m_v3HalfWidth.y * m3RotationAbs[2][1] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[2][2];
	if (std::abs(v3Distance.z) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		vector3 v3Center;
		matrix4 m4WorldToLocal = glm::inverse(m_m4ToWorld);
		if (m_v3CenterG.z < a_pOther->m_v3CenterG.z)
		{
			vector3 v3OtherMinInA = vector3(m4WorldToLocal * vector4(a_pOther->m_v3MinG, 1.0f));
			v3Center = vector3(m4WorldToLocal * vector4(m_v3MaxG, 1.0f)) + v3OtherMinInA;
		}
		else
		{
			vector3 v3OtherMaxInA = vector3(m4WorldToLocal * vector4(a_pOther->m_v3MaxG, 1.0f));
			v3Center = vector3(m4WorldToLocal * vector4(m_v3MinG, 1.0f)) + v3OtherMaxInA;
		}
		v3Center /= 2.0f;
		matrix4 m4Space = glm::translate(m_m4ToWorld, v3Center);
		m_pMeshMngr->AddPlaneToQueue(m4Space * glm::scale(vector3(5.0f)), REBLUE);
#endif
		return false;
	}

	// Test axes L = BX <- 3
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[0][0] + m_v3HalfWidth.y * m3RotationAbs[1][0] + m_v3HalfWidth.z * m3RotationAbs[2][0];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x;
	if (std::abs(v3Distance.x * m3Rotation[0][0] + v3Distance.y * m3Rotation[1][0] + v3Distance.z * m3Rotation[2][0]) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		matrix4 m4Space = glm::translate(IDENTITY_M4, a_pOther->m_v3CenterG) * glm::rotate(IDENTITY_M4, 90.0f, REAXISY);
		m_pMeshMngr->AddPlaneToQueue(m4Space * glm::scale(vector3(5.0f)), RERED * 0.33f);
#endif
		return false;
	}

	// Test axes L = BY <- 4
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[0][1] + m_v3HalfWidth.y * m3RotationAbs[1][1] + m_v3HalfWidth.z * m3RotationAbs[2][1];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.y;
	if (std::abs(v3Distance.x * m3Rotation[0][1] + v3Distance.y * m3Rotation[1][1] + v3Distance.z * m3Rotation[2][1]) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		matrix4 m4Space = glm::translate(IDENTITY_M4, a_pOther->m_v3CenterG) * glm::rotate(IDENTITY_M4, 90.0f, REAXISX);
		m_pMeshMngr->AddPlaneToQueue(m4Space * glm::scale(vector3(5.0f)), REGREEN * 0.33f);
#endif
		return false;
	}

	// Test axes L = BZ <- 5
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[0][2] + m_v3HalfWidth.y * m3RotationAbs[1][2] + m_v3HalfWidth.z * m3RotationAbs[2][2];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.z;
	if (std::abs(v3Distance.x * m3Rotation[0][2] + v3Distance.y * m3Rotation[1][2] + v3Distance.z * m3Rotation[2][2]) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		matrix4 m4Space = glm::translate(IDENTITY_M4, a_pOther->m_v3CenterG);
		m_pMeshMngr->AddPlaneToQueue(m4Space * glm::scale(vector3(5.0f)), REBLUE * 0.33f);
#endif
		return false;
	}

	// Test axis L = AX x BX <- 6
	fCenterAToMiddle = m_v3HalfWidth.y * m3RotationAbs[2][0] + m_v3HalfWidth.z * m3RotationAbs[1][0];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.y * m3RotationAbs[0][2] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[0][1];
	if (std::abs(v3Distance.z * m3Rotation[1][0] - v3Distance.y * m3Rotation[2][0]) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		vector3 v3Center;
		matrix4 m4WorldToLocal = glm::inverse(m_m4ToWorld);
		if (m_v3CenterG.z < a_pOther->m_v3CenterG.z)
		{
			vector3 v3OtherMinInA = vector3(m4WorldToLocal * vector4(a_pOther->m_v3MinG, 1.0f));
			v3Center = vector3(m4WorldToLocal * vector4(m_v3MaxG, 1.0f)) + v3OtherMinInA;
		}
		else
		{
			vector3 v3OtherMaxInA = vector3(m4WorldToLocal * vector4(a_pOther->m_v3MaxG, 1.0f));
			v3Center = vector3(m4WorldToLocal * vector4(m_v3MinG, 1.0f)) + v3OtherMaxInA;
		}
		v3Center /= 2.0f;
		matrix4 m4Space = glm::translate(m_m4ToWorld, v3Center);
		m_pMeshMngr->AddSphereToQueue(m4Space * glm::scale(vector3(0.10f)), REYELLOW, SOLID);
#endif
		return false;
	}

	// Test axis L = AX x BY <- 7
	fCenterAToMiddle = m_v3HalfWidth.y * m3RotationAbs[2][1] + m_v3HalfWidth.z * m3RotationAbs[1][1];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[0][2] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[0][0];
	if (std::abs(v3Distance.z * m3Rotation[1][1] - v3Distance.y * m3Rotation[2][1]) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		vector3 v3Center = (m_v3CenterG + a_pOther->m_v3CenterG) / 2.0f;
		matrix4 m4Space = glm::translate(IDENTITY_M4, v3Center);
		m_pMeshMngr->AddSphereToQueue(m4Space * glm::scale(vector3(0.10f)), REYELLOW, SOLID);
#endif
		return false;
	}

	// Test axis L = AX x BZ <- 8
	fCenterAToMiddle = m_v3HalfWidth.y * m3RotationAbs[2][2] + m_v3HalfWidth.z * m3RotationAbs[1][2];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[0][1] + a_pOther->m_v3HalfWidth.y * m3RotationAbs[0][0];
	if (std::abs(v3Distance.z * m3Rotation[1][2] - v3Distance.y * m3Rotation[2][2]) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		vector3 v3Center = (m_v3CenterG + a_pOther->m_v3CenterG) / 2.0f;
		matrix4 m4Space = glm::translate(IDENTITY_M4, v3Center);
		m_pMeshMngr->AddSphereToQueue(m4Space * glm::scale(vector3(0.10f)), REYELLOW, SOLID);
#endif
		return false;
	}

	// Test axis L = AY x BX <- 9
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[2][0] + m_v3HalfWidth.z * m3RotationAbs[0][0];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.y * m3RotationAbs[1][2] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[1][1];
	if (std::abs(v3Distance.x * m3Rotation[2][0] - v3Distance.z * m3Rotation[0][0]) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		vector3 v3Center = (m_v3CenterG + a_pOther->m_v3CenterG) / 2.0f;
		matrix4 m4Space = glm::translate(IDENTITY_M4, v3Center);
		m_pMeshMngr->AddSphereToQueue(m4Space * glm::scale(vector3(0.10f)), REYELLOW, SOLID);
#endif
		return false;
	}

	// Test axis L = AY x BY <- 10
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[2][1] + m_v3HalfWidth.z * m3RotationAbs[0][1];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[1][2] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[1][0];
	if (std::abs(v3Distance.x * m3Rotation[2][1] - v3Distance.z * m3Rotation[0][1]) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		vector3 v3Center = (m_v3CenterG + a_pOther->m_v3CenterG) / 2.0f;
		matrix4 m4Space = glm::translate(IDENTITY_M4, v3Center);
		m_pMeshMngr->AddSphereToQueue(m4Space * glm::scale(vector3(0.10f)), REYELLOW, SOLID);
#endif
		return false;
	}

	// Test axis L = AY x BZ <- 11
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[2][2] + m_v3HalfWidth.z * m3RotationAbs[0][2];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[1][1] + a_pOther->m_v3HalfWidth.y * m3RotationAbs[1][0];
	if (std::abs(v3Distance.x * m3Rotation[2][2] - v3Distance.z * m3Rotation[0][2]) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		vector3 v3Center = (m_v3CenterG + a_pOther->m_v3CenterG) / 2.0f;
		matrix4 m4Space = glm::translate(IDENTITY_M4, v3Center);
		m_pMeshMngr->AddSphereToQueue(m4Space * glm::scale(vector3(0.10f)), REYELLOW, SOLID);
#endif
		return false;
	}

	// Test axis L = AZ x BX <- 12
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[1][0] + m_v3HalfWidth.y * m3RotationAbs[0][0];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.y * m3RotationAbs[2][2] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[2][1];
	if (std::abs(v3Distance.y * m3Rotation[0][0] - v3Distance.x * m3Rotation[1][0]) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		vector3 v3Center = (m_v3CenterG + a_pOther->m_v3CenterG) / 2.0f;
		matrix4 m4Space = glm::translate(IDENTITY_M4, v3Center);
		m_pMeshMngr->AddSphereToQueue(m4Space * glm::scale(vector3(0.10f)), REYELLOW, SOLID);
#endif
		return false;
	}

	// Test axis L = AZ x BY <- 13
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[1][1] + m_v3HalfWidth.y * m3RotationAbs[0][1];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[2][2] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[2][0];
	if (std::abs(v3Distance.y * m3Rotation[0][1] - v3Distance.x * m3Rotation[1][1]) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		vector3 v3Center = (m_v3CenterG + a_pOther->m_v3CenterG) / 2.0f;
		matrix4 m4Space = glm::translate(IDENTITY_M4, v3Center);
		m_pMeshMngr->AddSphereToQueue(m4Space * glm::scale(vector3(0.10f)), REYELLOW, SOLID);
#endif
		return false;
	}

	// Test axis L = AZ x BZ <- 14
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[1][2] + m_v3HalfWidth.y * m3RotationAbs[0][2];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[2][1] + a_pOther->m_v3HalfWidth.y * m3RotationAbs[2][0];
	if (std::abs(v3Distance.y * m3Rotation[0][2] - v3Distance.x * m3Rotation[1][2]) > fCenterAToMiddle + fCenterBToMiddle)
	{
#ifdef SHOWPLANES
		vector3 v3Center = (m_v3CenterG + a_pOther->m_v3CenterG) / 2.0f;
		matrix4 m4Space = glm::translate(IDENTITY_M4, v3Center);
		m_pMeshMngr->AddSphereToQueue(m4Space * glm::scale(vector3(0.10f)), REYELLOW, SOLID);
#endif
		return false;
	}

	// Since no separating axis found, the OBBs must a_pOther->m_v3HalfWidth intersecting
	return true;
}