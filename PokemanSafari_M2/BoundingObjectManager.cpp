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
	std::pair<objMapIt,bool> stat = objMap.insert(objMapPair(name, new MyBoundingObjectClass(VectorList,name)));
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
			if (it1->second->IsColliding(it2->second))
			{
				it1->second->SetBOColor(RERED);
				it2->second->SetBOColor(RERED);
			}
		}
	}

}

/////////////////////////////////////////////////////////////////////
// CheckCollisions - checks collosions with all chars/projs
/////////////////////////////////////////////////////////////////////
void BoundingObjectManager::CheckCollisions()
{
	/*POKEMAN SAFARI Collisoin Checks
	Pokeman <-> PokeCube
	Spaceship <-> Rock
	Player <-> Net
	*/
	charMapIt cIt1;
	projMapIt pIt1;
	//For every character
	for (cIt1 = charMap.begin(); cIt1 != charMap.end(); cIt1++)
	{
		if (cIt1->second->charType == CT_POKEMAN)
		{
			//Check against pokecube
			for (pIt1 = projMap.begin(); pIt1 != projMap.end(); pIt1++)
			{
				if (pIt1->second->projType == PJ_POKECUBE)
				{
					if (cIt1->second->IsColliding(pIt1->second))
					{
						//Update score manager?

						//Remove pokecube & pokeman
						delete cIt1->second;
						delete pIt1->second;
						charMap.erase(cIt1);
						projMap.erase(pIt1);
					}
				}
			}
		}
		else if (cIt1->second->charType == CT_SPACESHIP)
		{
			//Check against rocks
			for (pIt1 = projMap.begin(); pIt1 != projMap.end(); pIt1++)
			{
				if (pIt1->second->projType == PJ_ROCK)
				{
					if (cIt1->second->IsColliding(pIt1->second))
					{
						//Update score manager?

						//Remove spaceship & rock
						delete cIt1->second;
						delete pIt1->second;
						charMap.erase(cIt1);
						projMap.erase(pIt1);
					}
				}
			}
		}
		else   //CT_PLAYER
		{
			//Check against nets
			for (pIt1 = projMap.begin(); pIt1 != projMap.end(); pIt1++)
			{
				if (pIt1->second->projType == PJ_ROCK)
				{
					if (cIt1->second->IsColliding(pIt1->second))
					{
						//Update score manager?

						//Remove net
						delete pIt1->second;
						projMap.erase(pIt1);
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////
// UpdateCharacterRenderList()
/////////////////////////////////////////////////////////////////////
void BoundingObjectManager::UpdateCharacterRenderList(String name)
{

	//This also might be a good place to control what character
	//objects get updated. i.e not all pokeman need to be active
	//if totally out of sight/range/area

	charMapIt it;
	if (name.compare("ALL") == 0)
	{
		for (it = charMap.begin(); it != charMap.end(); it++)
		{
			it->second->UpdateRender();
		}
		return;
	}
	it = charMap.find(name);
	if (it == charMap.end())
		return;
	it->second->UpdateRender();
}

/////////////////////////////////////////////////////////////////////
// UpdateProjectileRenderList()
/////////////////////////////////////////////////////////////////////
void BoundingObjectManager::UpdateProjectileRenderList(String name)
{
	projMapIt it;
	if (name.compare("ALL") == 0)
	{
		for (it = projMap.begin(); it != projMap.end(); it++)
		{
			it->second->UpdateRender();
		}
		return;
	}
	it = projMap.find(name);
	if (it == projMap.end())
		return;
	it->second->UpdateRender();
}

/////////////////////////////////////////////////////////////////////
// AddCharacter
/////////////////////////////////////////////////////////////////////
int BoundingObjectManager::AddCharacter(String name, Character* c)
{
	std::pair<charMapIt, bool> stat = charMap.insert(charMapPair(name, c));
	if (stat.second == false) //check for failure
		return 0;

	return 1;
}

/////////////////////////////////////////////////////////////////
// AddProjectile
/////////////////////////////////////////////////////////////////
int BoundingObjectManager::AddProjectile(String name, Projectile* p)
{
	std::pair<projMapIt, bool> stat = projMap.insert(projMapPair(name, p));
	if (stat.second == false) //check for failure
		return 0;

	return 1;
}









