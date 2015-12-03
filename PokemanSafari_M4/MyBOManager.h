/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MYBOMANAGER_H_
#define __MYBOMANAGER_H_

#include "MyBOClass.h"

//System Class
class MyBOManager
{
	uint m_nObjectCount = 0; //number of AABB in the list
	static MyBOManager* m_pInstance; // Singleton pointer
	std::vector<MyBOClass*> m_lObject; //list of AABB
	MeshManagerSingleton* pMeshMngr;//Mesh Manager Singleton
	std::vector<std::vector<int>> m_llCollidingIndices; //List of list of colliding indices.
	std::map<String, uint> m_mapIndex;//Map relating the mesh and the index
public:
	/*
	Method: GetInstance
	Usage: Gets the static instance of the class
	Arguments: ---
	Output: static pointer to class
	*/
	static MyBOManager* GetInstance();
	/*
	Method: ReleaseInstance
	Usage: releases the static pointer to class
	Arguments: ---
	Output: ---
	*/
	static void ReleaseInstance(void);

	/*
	Method: AddObject
	Usage: Creates a Object from a list of vertices and adds it to the
			Object list.
	Arguments:
		vector3 a_lVertex -> list of vertex to create a Object from
	Output: ---
	*/
	void AddObject(std::vector<vector3> a_lVertex, String a_sName);

	/*
	Method: SetModelMatrix
	Usage: Sets the model matrix to the specified index
	Arguments:
		matrix4 a_mModelMatrix -> ModelToWorld matrix to set
		String a_sIndex -> Index to set into, will find the related
							uint through a dictionary
	Output: ---
	*/
	void SetModelMatrix(matrix4 a_mModelMatrix, String a_sIndex);

	/*
	Method: DisplaySphere
	Usage: Displays the Bounding Sphere of the model in the specified color
	Arguments:
		int a_nIndex = -1 ->	Index of Object to be displayed, a negative index indicate
		that all Objects will be drawn
		vector3 a_v3Color = REDEFAULT ->	Color of the Object to display if the value is
		REDEFAULT it will display Objects in white and
	colliding ones in red
	Output: ---
	*/
	void DisplaySphere(int a_nIndex = -1, vector3 a_v3Color = REDEFAULT);

	/*
	Method: DisplayOriented
	Usage: Displays the Oriented Bounding Object of the model in the specified color
	Arguments:
		int a_nIndex = -1 ->	Index of Object to be displayed, a negative index indicate
							that all Objects will be drawn
		vector3 a_v3Color = REDEFAULT ->	Color of the Object to display if the value is
										REDEFAULT it will display Objects in white and
										colliding ones in red
	Output: ---
	*/
	void DisplayOriented(int a_nIndex = -1, vector3 a_v3Color = REDEFAULT);

	/*
	Method: DisplayReAlligned
	Usage: Displays the ReAlligned Bounding Object of the model in the specified color
	Arguments:
		int a_nIndex = -1 -> Index of Object to be displayed, a negative index indicate
			that all Objects will be drawn.
		vector3 a_v3Color = REDEFAULT ->	Color of the Object to display if the value is
			REDEFAULT it will display Objects in white and colliding ones in red.
	Output: ---
	*/
	void DisplayReAlligned(int a_nIndex = -1, vector3 a_v3Color = REDEFAULT);

	/*
	Method: GetCollingVector
	Usage: Returns the list of indices of object for which the BO (specified by name) is colliding with
	Arguments:
	--- String a_sIndex -> Name of the bounding object (index)
	Output: list of colliding objects index
	*/
	std::vector<int> GetCollidingVector(String a_sIndex);

	/*
	Method: GetCollingVector
	Usage: Returns the list of indices of object for which the BO (specified by index) is colliding with
	Arguments:
	--- uint a_nIndex -> index of the bounding object
	Output: list of colliding objects index
	*/
	std::vector<int> GetCollidingVector(uint a_nIndex);

	/*
	Method: GetIndex
	Usage: Returns the index of the BO specified by name from the dictionary
	Arguments:
		String a_sIndex -> name of the index
	Output: index of the BO specified by name, -1 if not found
	*/
	int GetIndex(String a_sIndex);

	/*
	Method: GetObject
	Usage: returns the element specified by the index
	Arguments: ---
	Output: MyBOClass* from the list
	*/
	MyBOClass* GetObject(uint a_nIndex);

	/*
	Method: Update
	Usage: Calculates the intermediary states of all the members in the variables
	Arguments: ---
	Output: ---
	*/
	void Update(void);
	
private:
	/*
	Method: Constructor
	Usage: instantiates the object
	Arguments: ---
	Output: ---
	*/
	MyBOManager(void);
	/*
	Method: Copy constructor
	Usage: does nothing (singleton behavior)
	Arguments: other instance to copy
	Output: ---
	*/
	MyBOManager(MyBOManager const& other);
	/*
	Method: Copy assigment operator
	Usage: does nothing (singleton behavior)
	Arguments: other instance to copy
	Output: ---
	*/
	MyBOManager& operator=(MyBOManager const& other);
	/*
	Method: Destructor
	Usage: releases the instance
	Arguments: ---
	Output: ---
	*/
	~MyBOManager(void);
	/*
	Method: Release
	Usage: deallocates the memory of the method
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Method: Init
	Usage: allocates the memory of the method
	Arguments: ---
	Output: ---
	*/
	void Init(void);
	/*
	Method: CheckCollisions
	Usage: Calculates the collision between all AABBs
	Arguments: ---
	Output: ---
	*/
	void CheckCollisions(void);
};

#endif //__MYBOMANAGER_H_