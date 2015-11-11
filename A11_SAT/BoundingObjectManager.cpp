/////////////////////////////////////////////////////////////////////
// File: BoundingObjectManager.cpp
// DSA2 A10_BoundingObjectManager
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////

#include "BoundingObjectManager.h"
#include "AppClass.h"

BoundingObjectManager* BoundingObjectManager::inst = nullptr;

/////////////////////////////////////////////////////////////////////
//  BoundingObjectManager() - Private singleton constructor
/////////////////////////////////////////////////////////////////////
BoundingObjectManager::BoundingObjectManager()
{
	//	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}

/////////////////////////////////////////////////////////////////////
// GetInstance() - return the singleton inst of BO manager
/////////////////////////////////////////////////////////////////////
BoundingObjectManager* BoundingObjectManager::GetInstance()
{
	if (inst == nullptr)
	{
		inst = new BoundingObjectManager();
	}
	return inst;
}

/////////////////////////////////////////////////////////////////////
// ReleaseInst() - Release the BO manager singleton instance
/////////////////////////////////////////////////////////////////////
void BoundingObjectManager::ReleaseInst()
{
	if (inst != nullptr)
	{
		delete inst;
		inst = nullptr;
	}
}

/////////////////////////////////////////////////////////////////////
// ~BoundingObjectManager()
/////////////////////////////////////////////////////////////////////
BoundingObjectManager::~BoundingObjectManager()
{
	for (objMapIt it = objMap.begin(); it != objMap.end(); it++)
	{
		delete it->second;
	}
	objMap.erase(objMap.begin(), objMap.end());
	ReleaseInst();
}

/////////////////////////////////////////////////////////////////////
// AddBox - names must be unique
//    name - unique key for BO
//    VectorList - vertices to generate BOClass
/////////////////////////////////////////////////////////////////////
int BoundingObjectManager::AddBox(String name, std::vector<vector3> VectorList)
{
	//insert into map
	std::pair<objMapIt, bool> stat = objMap.insert(objMapPair(name, new MyBoundingObjectClass(VectorList, name)));
	if (stat.second == false) //check for failure
		return 0;
	//	objMap[name] = new MyBoundingObjectClass(VectorList, name);



	//Debugging print all members name
	//	printf("\nManager List:\n");
	//	for (objMapIt it = objMap.begin(); it != objMap.end(); it++)
	//	{
	//		std::cout << it->first << "   "<< it->second->sName <<std::endl;
	//		//std::cout << it->second.sName << std::endl;
	//	}
	return 1;
}

/////////////////////////////////////////////////////////////////////
// SetAABBVisible 
//    visible - whether spehere/axis re-aligned is visible for ALL
/////////////////////////////////////////////////////////////////////
void BoundingObjectManager::SetAABBVisible(bool visible)
{
	for (objMapIt it = objMap.begin(); it != objMap.end(); it++)
	{
		it->second->SetAABBVisible(visible);
	}

	aabbVisible = visible;
}

/////////////////////////////////////////////////////////////////////
// GetNumberBO() - return number of BO objs in manager
/////////////////////////////////////////////////////////////////////
int BoundingObjectManager::GetNumberBO()
{
	return objMap.size();
}

/////////////////////////////////////////////////////////////////////
// SetModelMatrix
//    name - unique key for BO
//    mToWorld matrix
/////////////////////////////////////////////////////////////////////
void BoundingObjectManager::SetModelMatrix(String name, matrix4 mToWorld)
{
	objMapIt it = objMap.find(name);
	if (it == objMap.end())
		return;
	it->second->SetModelMatrix(mToWorld);
}

/////////////////////////////////////////////////////////////////////
// SetBOColor()
//    name - unique key for BO
//    v3Color - color of BO box/sphere
/////////////////////////////////////////////////////////////////////
void BoundingObjectManager::SetBOColor(String name, vector3 v3color)
{
	objMapIt it = objMap.find(name);
	if (it == objMap.end())
		return;
	it->second->SetBOColor(v3color);
}


/////////////////////////////////////////////////////////////////////
// SetBOVisibile
//    name - unique key for BO
//    visible - whether all BO shapes are visible
/////////////////////////////////////////////////////////////////////
void BoundingObjectManager::SetBOVisible(String name, bool visible)
{
	objMapIt it = objMap.find(name);
	if (it == objMap.end())
		return;
	it->second->SetBOVisible(visible);

	boVisible = visible;
}


/////////////////////////////////////////////////////////////////////
// UpdateRenderList
//    name - unique key for BO
//         - "ALL" special case to render all BOs
/////////////////////////////////////////////////////////////////////
void BoundingObjectManager::UpdateRenderList(String name)
{
	objMapIt it;
	if (name.compare("ALL") == 0)
	{
		for (it = objMap.begin(); it != objMap.end(); it++)
		{
			it->second->UpdateRender();
		}
		return;
	}
	it = objMap.find(name);
	if (it == objMap.end())
		return;
	it->second->UpdateRender();
}

/////////////////////////////////////////////////////////////////////
// CheckCollision - checks collosions with all BOs
/////////////////////////////////////////////////////////////////////
void BoundingObjectManager::CheckCollision()
{
	objMapIt it1, it2, it3;
	//Reset color to neutral
	for (it1 = objMap.begin(); it1 != objMap.end(); it1++)
	{
		it1->second->SetBOColor(REWHITE);
	}
	//Check every BO with every other BO
	for (it1 = objMap.begin(); it1 != objMap.end(); it1++)
	{
		it3 = it1;
		it3++; //don't check withs self or previous
		for (it2 = (it3); it2 != objMap.end(); it2++)
		{

			//UNDO THIS
			//if (it1->second->IsColliding(it2->second))
			if (it2->second->IsColliding(it1->second))
			{
				it1->second->SetBOColor(RERED);
				it2->second->SetBOColor(RERED);
			}
		}
	}
}