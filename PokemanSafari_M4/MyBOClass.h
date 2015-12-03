/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __MYBOCLASS_H_
#define __MYBOCLASS_H_

#include "RE\ReEng.h"


//System Class
class MyBOClass
{
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Object Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the Object Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the Object Class

	vector3 m_v3CenterG = vector3(0.0f); //Will store the center point of the Object Class
	vector3 m_v3MinG = vector3(0.0f); //Will store the minimum vector of the Object Class
	vector3 m_v3MaxG = vector3(0.0f); //Will store the maximum vector of the Object Class

	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides
	vector3 m_v3HalfWidthG = vector3(0.0f);//Will store half the size of all sides

	float m_fRadius = 0.0f; //Radius of the Bounding Object

public:
	/*
	Method: MyBOClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	MyBOClass(std::vector<vector3> a_lVectorList);
	/*
	Method: MyBOClass
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	MyBOClass(MyBOClass const& other);
	/*
	Method: operator=
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	MyBOClass& operator=(MyBOClass const& other);
	/*
	Method: ~MyBOClass
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~MyBOClass(void);

	/*
	Method: Swap
	Usage: Changes object contents for other object's
	Arguments:
	other -> object to swap content from
	Output: ---
	*/
	void Swap(MyBOClass& other);

	/*
	Method: SetToWorldMatrix
	Usage: Sets the Bounding Object into world coordinates
	Arguments:
	matrix4 a_m4ToWorld -> Model to World matrix
	Output: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);

	/*
	Method: GetToWorldMatrix
	Usage: Gets the Bounding Object into world coordinates
	Arguments:---
	Output: matrix4 -> Model to World matrix
	*/
	matrix4 GetModelMatrix(void);

	/*
	Method: GetRadius
	Usage: Gets the Bounding Object's radius
	Arguments: ---
	Output: float -> Radous of the BO
	*/
	float GetRadius(void);

	/*
	Method: GetCenter
	Usage: Gets the Bounding Object's center in local coordinates
	Arguments: ---
	Output: vector3 -> Center's of the Object in local coordinates
	*/
	vector3 GetCenterLocal(void);

	/*
	Method: GetCenterGlobal
	Usage: Gets the Bounding Object's center in global coordinates
	Arguments: ---
	Output: vector3 -> Center's of the Object in global coordinates
	*/
	vector3 GetCenterGlobal(void);

	/*
	Method: GetHalfWidth
	Usage: Gets the Bounding Object sizes for all sides (divided in half)
	Arguments: ---
	Output: vector3 -> HalfWidth Vector
	*/
	vector3 GetHalfWidth(void);

	/*
	Method: GetHalfWidthG
	Usage: Gets the Bounding Object sizes for all sides (divided in half) reoriented
	Arguments: ---
	Output: vector3 -> HalfWidth Vector
	*/
	vector3 GetHalfWidthG(void);

	/*
	Method: IsColliding
	Usage: Asks if there is a collision with another Bounding Object Object
	Arguments:
	MyBOClass* const a_pOther -> Other object to check collision with
	Output: bool -> check of the collision
	*/
	bool IsColliding(MyBOClass* const a_pOther);

private:
	/*
	Method: Release
	Usage: Deallocates member fields
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Method: Init
	Usage: Allocates member fields
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};

#endif //__MYBOCLASS_H__