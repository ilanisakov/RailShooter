/////////////////////////////////////////////////////////////////////
// File: MyBOManager.cpp
// DSA2 PokemanSafari_M4
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////

#include "MyBOManager.h"

//Singleton Instance
MyBOManager* MyBOManager::m_pInstance = nullptr;

/////////////////////////////////////////////////////////////////////
//Method: Init
//Usage: allocates the memory of the method
//Arguments: ---
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOManager::Init(void)
{
	m_nObjectCount = 0;
	pMeshMngr = MeshManagerSingleton::GetInstance();
}

/////////////////////////////////////////////////////////////////////
// InitOctTree() - builds and populates the octal tree
//
// @param - depth of the tree
/////////////////////////////////////////////////////////////////////
void MyBOManager::InitOctTree(int depth)
{
	if (m_pOctTree != nullptr)
		return; 

	m_pOctTree = new MyOctTree(vector3(-2.0f,12.0f,0.0f),depth,150.0f);
	//Add all objects to the tree
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		//printf("%s 's Octant> ", m_lObject[nObject]->GetName().c_str());
		m_pOctTree->AddObject(m_pOctTree, m_lObject[nObject]);
	}
}

/////////////////////////////////////////////////////////////////////
// UpdateTree() - updates a dynamic object in the octal tree
//
// @param - name of the object
/////////////////////////////////////////////////////////////////////
void MyBOManager::UpdateTree(String name)
{
	int idx = GetIndex(name);
	if (idx >= 0)
	{
		MyBOClass* obj = GetObject(idx);
		if (obj != nullptr)
			m_pOctTree->UpdateObject(m_pOctTree, obj);
	}

}

/////////////////////////////////////////////////////////////////////
// DisplayOctTree() - displays the octal tree grids
/////////////////////////////////////////////////////////////////////
void MyBOManager::DisplayOctTree()
{
	m_pOctTree->DisplayBox();
}

/////////////////////////////////////////////////////////////////////
//Method: Release
//Usage: deallocates the memory of the method
//Arguments: ---
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOManager::Release(void)
{
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		if (m_lObject[nObject] != nullptr)
		{
			delete m_lObject[nObject];
			m_lObject[nObject] = nullptr;
		}
		m_llCollidingIndices[nObject].clear();
	}
	m_lObject.clear();
	m_llCollidingIndices.clear();

	m_pOctTree->Release(m_pOctTree);
	delete m_pOctTree;
}

/////////////////////////////////////////////////////////////////////
//Method: GetInstance
//Usage: Gets the static instance of the class
//Arguments: ---
//Output: static pointer to class
/////////////////////////////////////////////////////////////////////
MyBOManager* MyBOManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new MyBOManager();
	}
	return m_pInstance;
}

/////////////////////////////////////////////////////////////////////
//Method: ReleaseInstance
//Usage: releases the static pointer to class
//Arguments: ---
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

/////////////////////////////////////////////////////////////////////
//Method: Constructor
//Usage: instantiates the object
//Arguments: ---
//Output: ---
/////////////////////////////////////////////////////////////////////
MyBOManager::MyBOManager()
{
	Init();
}

/////////////////////////////////////////////////////////////////////
//Method: Copy constructor
//Usage: does nothing (singleton behavior)
//Arguments: other instance to copy
//Output: ---
/////////////////////////////////////////////////////////////////////
MyBOManager::MyBOManager(MyBOManager const& other)
{ 
}

/////////////////////////////////////////////////////////////////////
//Method: Copy assigment operator
//Usage: does nothing (singleton behavior)
//Arguments: other instance to copy
//Output: ---
/////////////////////////////////////////////////////////////////////
MyBOManager& MyBOManager::operator=(MyBOManager const& other) 
{ 
	return *this; 
}

/////////////////////////////////////////////////////////////////////
//Method: Destructor
//Usage: releases the instance
//Arguments: ---
//Output: ---
/////////////////////////////////////////////////////////////////////
MyBOManager::~MyBOManager()
{
	Release();
}

/////////////////////////////////////////////////////////////////////
//Method: GetObject
//Usage: returns the element specified by the index
//Arguments: ---
//Output: MyBOClass* from the list
/////////////////////////////////////////////////////////////////////
MyBOClass* MyBOManager::GetObject(uint a_nIndex)
{
	if (a_nIndex < m_nObjectCount)
		return m_lObject[a_nIndex];

	return nullptr;
}

/////////////////////////////////////////////////////////////////////
//Method: AddObject
//Usage: Creates a Object from a list of vertices and adds it to the
//		Object list.
//Arguments:
//	vector3 a_lVertex -> list of vertex to create a Object from
//  name - the objects name
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOManager::AddObject(std::vector<vector3> a_lVertex, String a_sName)
{
	MyBOClass* pObject = new MyBOClass(a_lVertex, a_sName);
	if (pObject != nullptr)
	{
		m_lObject.push_back(pObject);//Add the Object
		m_mapIndex[a_sName] = m_nObjectCount; //Add entry to the dictionary
	}
	m_nObjectCount = m_lObject.size();
	std::vector<int> lVector;
	m_llCollidingIndices.push_back(lVector);

	pObject->SetStoredIndex(GetIndex(a_sName));
}

/////////////////////////////////////////////////////////////////////
//Method: SetModelMatrix
//Usage: Sets the model matrix to the specified index
//Arguments:
//	matrix4 a_mModelMatrix -> ModelToWorld matrix to set
//	String a_sIndex -> Index to set into, will find the related
//						uint through a dictionary
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOManager::SetModelMatrix(matrix4 a_mModelMatrix, String a_sIndex)
{
	//find the object
	int nIndex = this->GetIndex(a_sIndex);
	if (nIndex < 0) //if not found return
		return;

	m_lObject[nIndex]->SetModelMatrix(a_mModelMatrix);//set the matrix for the indexed Object
}

/////////////////////////////////////////////////////////////////////
//Method: DisplaySphere
//Usage: Displays the Bounding Sphere of the model in the specified color
//Arguments:
//	int a_nIndex = -1 ->	Index of Object to be displayed, a negative index indicate
//	that all Objects will be drawn
//	vector3 a_v3Color = REDEFAULT ->	Color of the Object to display if the value is
//	REDEFAULT it will display Objects in white and
//colliding ones in red
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOManager::DisplaySphere(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		bool bColliding = false;
		for (uint n = 0; n < m_nObjectCount; n++)
		{
			if (m_llCollidingIndices[n].size() > 0)
			{
				bColliding = true;
				break;
			}
		}

		if (v3Color == REDEFAULT)
		{
			if (!bColliding)
				v3Color = REWHITE;
			else
				v3Color = RERED;
		}

		pMeshMngr->AddSphereToQueue(
			m_lObject[a_nIndex]->GetModelMatrix() *
			glm::translate(IDENTITY_M4, m_lObject[a_nIndex]->GetCenterLocal()) *
			glm::scale(vector3(m_lObject[a_nIndex]->GetRadius() * 2.0f)),
			v3Color,
			WIRE);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			bool bColliding = false;
			for (uint n = 0; n < m_nObjectCount; n++)
			{
				if (m_llCollidingIndices[n].size() > 0)
				{
					bColliding = true;
					break;
				}
			}

			if (v3Color == REDEFAULT)
			{
				if (!bColliding)
					v3Color = REWHITE;
				else
					v3Color = RERED;
			}
			pMeshMngr->AddSphereToQueue(
				m_lObject[nObject]->GetModelMatrix() *
				glm::translate(IDENTITY_M4, m_lObject[nObject]->GetCenterLocal()) *
				glm::scale(vector3(m_lObject[nObject]->GetRadius() * 2.0f)),
				v3Color,
				WIRE);
		}
	}
}

/////////////////////////////////////////////////////////////////////
//Method: DisplayOriented
//Usage: Displays the Oriented Bounding Object of the model in the specified color
//Arguments:
//	int a_nIndex = -1 ->	Index of Object to be displayed, a negative index indicate
//						that all Objects will be drawn
//	vector3 a_v3Color = REDEFAULT ->	Color of the Object to display if the value is
//									REDEFAULT it will display Objects in white and
//									colliding ones in red
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOManager::DisplayOriented(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		bool bColliding = false;
		for (uint n = 0; n < m_nObjectCount; n++)
		{
			if (m_llCollidingIndices[n].size() > 0)
			{
				bColliding = true;
				break;
			}
		}

		if (v3Color == REDEFAULT)
		{
			if (!bColliding)
				v3Color = REWHITE;
			else
				v3Color = RERED;
		}

		pMeshMngr->AddCubeToQueue(
			m_lObject[a_nIndex]->GetModelMatrix() *
			glm::translate(IDENTITY_M4, m_lObject[a_nIndex]->GetCenterLocal()) *
			glm::scale(m_lObject[a_nIndex]->GetHalfWidth() * 2.0f),
			v3Color,
			WIRE);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			bool bColliding = false;
			for (uint n = 0; n < m_nObjectCount; n++)
			{
				if (m_llCollidingIndices[n].size() > 0)
				{
					bColliding = true;
					break;
				}
			}

			if (v3Color == REDEFAULT)
			{
				if (!bColliding)
					v3Color = REWHITE;
				else
					v3Color = RERED;
			}
			pMeshMngr->AddCubeToQueue(
				m_lObject[nObject]->GetModelMatrix() *
				glm::translate(IDENTITY_M4, m_lObject[nObject]->GetCenterLocal()) *
				glm::scale(m_lObject[nObject]->GetHalfWidth() * 2.0f),
				v3Color,
				WIRE);
		}
	}
}

/////////////////////////////////////////////////////////////////////
//Method: DisplayReAlligned
//Usage: Displays the ReAlligned Bounding Object of the model in the specified color
//Arguments:
//	int a_nIndex = -1 -> Index of Object to be displayed, a negative index indicate
//		that all Objects will be drawn.
///	vector3 a_v3Color = REDEFAULT ->	Color of the Object to display if the value is
//		REDEFAULT it will display Objects in white and colliding ones in red.
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOManager::DisplayReAlligned(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		bool bColliding = false;
		for (uint n = 0; n < m_nObjectCount; n++)
		{
			if (m_llCollidingIndices[n].size() > 0)
			{
				bColliding = true;
				break;
			}
		}

		if (v3Color == REDEFAULT)
		{
			if (!bColliding)
				v3Color = REWHITE;
			else
				v3Color = RERED;
		}
		pMeshMngr->AddCubeToQueue(
			glm::translate(m_lObject[a_nIndex]->GetCenterGlobal()) * 
			glm::scale(m_lObject[a_nIndex]->GetHalfWidthG() * 2.0f),
			v3Color,
			WIRE);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			bool bColliding = false;
			for (uint n = 0; n < m_nObjectCount; n++)
			{
				if (m_llCollidingIndices[n].size() > 0)
				{
					bColliding = true;
					break;
				}
			}

			if (v3Color == REDEFAULT)
			{
				if (!bColliding)
					v3Color = REWHITE;
				else
					v3Color = RERED;
			}
			pMeshMngr->AddCubeToQueue(
				glm::translate(m_lObject[nObject]->GetCenterGlobal()) *
				glm::scale(m_lObject[nObject]->GetHalfWidthG() * 2.0f),
				v3Color,
				WIRE);
		}
	}
}

/////////////////////////////////////////////////////////////////////
//Method: Update
//Usage: Calculates the intermediary states of all the members in the variables
//Arguments: ---
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOManager::Update(void)
{
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		m_llCollidingIndices[nObject].clear();
	}
	CheckCollisions();
}

/////////////////////////////////////////////////////////////////////
//Method: CheckCollisions
//Usage: Calculates the collision between all AABBs
//Arguments: ---
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyBOManager::CheckCollisions(void)
{
  /*for (uint nObjectA = 0; nObjectA < m_nObjectCount -1; nObjectA++)
	{
		for (uint nObjectB = nObjectA + 1; nObjectB < m_nObjectCount; nObjectB++)
		{
			if (m_lObject[nObjectA]->IsColliding(m_lObject[nObjectB]))
			{
				m_llCollidingIndices[nObjectA].push_back(nObjectB);
				m_llCollidingIndices[nObjectB].push_back(nObjectA);
			}
		}
	}*/

	//Process Collisions using OctalTree!
	m_pOctTree->CollisionTraverse( &m_llCollidingIndices );
}

/////////////////////////////////////////////////////////////////////
//Method: GetCollingVector
//Usage: Returns the list of indices of object for which the BO (specified by name) is colliding with
//Arguments:
//--- String a_sIndex -> Name of the bounding object (index)
//Output: list of colliding objects index
/////////////////////////////////////////////////////////////////////
std::vector<int> MyBOManager::GetCollidingVector(String a_sIndex)
{
	int nIndex = GetIndex(a_sIndex);
	if (nIndex < 0)
	{
		std::vector<int> empty;
		return empty;
	}
	return GetCollidingVector(static_cast<uint>(nIndex));
}

/////////////////////////////////////////////////////////////////////
//Method: GetCollingVector
//Usage: Returns the list of indices of object for which the BO (specified by index) is colliding with
//Arguments:
//--- uint a_nIndex -> index of the bounding object
//Output: list of colliding objects index
/////////////////////////////////////////////////////////////////////
std::vector<int> MyBOManager::GetCollidingVector(uint a_nIndex)
{
	if (a_nIndex >= m_nObjectCount)
	{
		std::vector<int> empty;
		return empty;
	}
	return m_llCollidingIndices[a_nIndex];
}

/////////////////////////////////////////////////////////////////////
//Method: GetIndex
//Usage: Returns the index of the BO specified by name from the dictionary
//Arguments:
//	String a_sIndex -> name of the index
//Output: index of the BO specified by name, -1 if not found
/////////////////////////////////////////////////////////////////////
int MyBOManager::GetIndex(String a_sIndex)
{
	//Find the related index
	auto var = m_mapIndex.find(a_sIndex);
	//If not found return -1
	if (var == m_mapIndex.end())
		return -1;
	return var->second;//Get the index
}