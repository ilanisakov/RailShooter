/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef _MYBOUNDINGOBJECTCLASS_H_
#define _MYBOUNDINGOBJECTCLASS_H_

#include "RE\ReEng.h"


//System Class
class MyBoundingObjectClass
{
	MeshManagerSingleton* m_pMeshMngr;

	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the box Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the box Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the box Class
	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides

	vector3 m_v3MinNEW = vector3(0.0f); //Store min/max for newBOX
	vector3 m_v3MaxNEW = vector3(0.0f);
	vector3 m_v3HalfWidthNEW = vector3(0.0f);

	float radius;

	bool bAABBVisible;
	bool bBOVisible;
	vector3 v3BOColor;

	

public:
	//debugging....
	String sName;

	/*
	Method: MyBoundingObjectClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	MyBoundingObjectClass(std::vector<vector3> a_lVectorList,String name);
	/*
	Method: MyBoundingObjectClass
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	MyBoundingObjectClass(MyBoundingObjectClass const& other);
	/*
	Method: operator=
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	MyBoundingObjectClass& operator=(MyBoundingObjectClass const& other);
	/*
	Method: ~MyBoundingObjectClass
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~MyBoundingObjectClass(void);

	/*
	Method: Swap
	Usage: Changes object contents for other object's
	Arguments:
	other -> object to swap content from
	Output: ---
	*/
	void Swap(MyBoundingObjectClass& other);

	/*
	Method: SetToWorldMatrix
	Usage: Sets the Bounding Box into world coordinates
	Arguments:
	matrix4 a_m4ToWorld -> Model to World matrix
	Output: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);

	/*
	Method: GetToWorldMatrix
	Usage: Gets the Bounding Box into world coordinates
	Arguments:---
	Output: matrix4 -> Model to World matrix
	*/
	matrix4 GetModelMatrix(void);

	/*
	Method: GetCenter
	Usage: Gets the Bounding Box's center in local coordinates
	Arguments: ---
	Output: vector3 -> Center's of the box in local coordinates
	*/
	vector3 GetCenterLocal(void);

	/*
	Method: GetCenterGlobal
	Usage: Gets the Bounding Box's center in global coordinates
	Arguments: ---
	Output: vector3 -> Center's of the box in global coordinates
	*/
	vector3 GetCenterGlobal(void);

	/*
	Method: GetHalfWidth
	Usage: Gets the Bounding Box sizes for all sides (divided in half)
	Arguments: ---
	Output: vector3 -> HalfWidth Vector

	bool aligned - whether axis oriented or axis re-aligned

	*/
	vector3 GetHalfWidth(bool alligned);

	/*
	Method: IsColliding
	Usage: Asks if there is a collision with another Bounding Box Object
	Arguments:
	MyBoundingObjectClass* const a_pOther -> Other object to check collision with
	Output: bool -> check of the collision
	*/
	bool IsColliding(MyBoundingObjectClass* const a_pOther);

	float GetRadius(void);

	/*
	Method: GetMax
	Usage: Gets max of the bounding object
	Arguments:
	Output: vector3 -> Max
	*/
	vector3 GetMax(bool global);


	/*
	Method: GetMin
	Usage: Gets min of the bounding object
	Arguments:
	Output: vector3 -> min
	*/
	vector3 GetMin(bool global);


	/////////////////////////////////////////////////////////////////
	// SetAABBVisible()
	/////////////////////////////////////////////////////////////////
	void SetAABBVisible(bool visible);

	/////////////////////////////////////////////////////////////////
	// SetBOColor()
	/////////////////////////////////////////////////////////////////
	void SetBOColor(vector3 v3color);

	/////////////////////////////////////////////////////////////////
	// SetBOVisible()
	/////////////////////////////////////////////////////////////////
	void SetBOVisible(bool visible);

	/////////////////////////////////////////////////////////////////
	// Render()
	/////////////////////////////////////////////////////////////////
	void UpdateRender();


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

#endif //_MYBOUNDINGOBJECTCLASS_H__