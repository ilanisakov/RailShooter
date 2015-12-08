/////////////////////////////////////////////////////////////////////
// File: MyEntityManager.cpp
// DSA2 PokemanSafari_M4
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description: Modified Entity Manager Singleton Class
//
/////////////////////////////////////////////////////////////////////

#include "MyEntityManager.h"

//Singleton Instance
MyEntityManager* MyEntityManager::m_pInstance = nullptr;

/////////////////////////////////////////////////////////////////////
// GetInstance() - gets the static instance of manager
/////////////////////////////////////////////////////////////////////
MyEntityManager* MyEntityManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyEntityManager();
	}
	return m_pInstance;
}

/////////////////////////////////////////////////////////////////////
// ReleaseInstance() 0 release the static class pointer
/////////////////////////////////////////////////////////////////////
void MyEntityManager::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

/////////////////////////////////////////////////////////////////////
// Release()  - release the objects memory
/////////////////////////////////////////////////////////////////////
void MyEntityManager::Release()
{
	//Delete entity list
	for (int i = 0; i < m_nEntityCount; i++)
	{
		delete m_lEntity[i];
	}
	m_lEntity.clear();
}

/////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////
MyEntityManager::MyEntityManager()
{
	m_pBOMngr = MyBOManager::GetInstance();
	m_nEntityCount = 0;
}

/////////////////////////////////////////////////////////////////////
// Copy Constructor
/////////////////////////////////////////////////////////////////////
MyEntityManager::MyEntityManager(MyEntityManager const& other)
{
	//Nothing to do
}

/////////////////////////////////////////////////////////////////////
// Copy Assignment Operator
/////////////////////////////////////////////////////////////////////
MyEntityManager& MyEntityManager::operator = (MyEntityManager const& other)
{
	return *this;
}

/////////////////////////////////////////////////////////////////////
// Destructor
/////////////////////////////////////////////////////////////////////
MyEntityManager::~MyEntityManager()
{
	Release();
}

/////////////////////////////////////////////////////////////////////
//AddEntity() - adds projectile entity
//
// @param
//    name - entity name
//    type - entity type
// @return -  success
/////////////////////////////////////////////////////////////////////
int MyEntityManager::AddEntity(String name, ET_TYPE type)
{
	MyEntityClass* ent = new MyEntityClass(name, type);
	if (ent == nullptr)
		return 0;

	m_lEntity.push_back(ent);
	entMap[name] = m_nEntityCount;
	m_nEntityCount++;
	return 1;
}

/////////////////////////////////////////////////////////////////////
// AddEntity() - adds path following entity
//
// @param
//    name - entity name
//    type - entity type
//    time - entity path lap time
//    movementPath - predetermined entity path
// @return - success
/////////////////////////////////////////////////////////////////////
int MyEntityManager::AddEntity(String name, ET_TYPE type, 
	float time, std::vector<vector3> movementPath)
{
	MyEntityClass* ent = new MyEntityClass(name,type,time,movementPath);
	if (ent == nullptr)
		return 0;
	
	m_lEntity.push_back(ent);
	entMap[name] = m_nEntityCount;
	m_nEntityCount++;
	return 1;
}

/////////////////////////////////////////////////////////////////////
// AddEntity() -  environmental obj entity
//
// @param
//    name - entity name
//    type - entity type
//    verts - list of entity verts
// @return - success
/////////////////////////////////////////////////////////////////////
int MyEntityManager::AddEntity(String name, ET_TYPE type, std::vector<vector3> verts)
{
	MyEntityClass* ent = new MyEntityClass(name, type, verts);
	if (ent == nullptr)
		return 0;

	m_lEntity.push_back(ent);
	entMap[name] = m_nEntityCount;
	m_nEntityCount++;
	return 1;
}

/////////////////////////////////////////////////////////////////////
// AddEntity - Adds already created entity 
//
// @param
//   entity - entity ref
//   name - entity name
// @return - success
/////////////////////////////////////////////////////////////////////
int MyEntityManager::AddEntity(MyEntityClass* entity, String name)
{
	if (entity == nullptr)
		return 0;

	m_lEntity.push_back(entity);
	entMap[name] = m_nEntityCount;
	m_nEntityCount++;
	return 1;
}

/////////////////////////////////////////////////////////////////////
// GetEntity() - returns refernce to an entity
//
// @param - name of the entity
// @return - reference to entity
/////////////////////////////////////////////////////////////////////
MyEntityClass* MyEntityManager::GetEntity(String name)
{
	//Find the related index
	auto var = entMap.find(name);
	//If not found return -1
	if (var == entMap.end())
		return NULL;

	return m_lEntity[static_cast<uint>(var->second)];
}

/////////////////////////////////////////////////////////////////////
// processCollisions() - processes collision responces for given
//                       entity name or ALL
/////////////////////////////////////////////////////////////////////
void MyEntityManager::processCollisions(String name)
{
	//printf("Processing Collision for %s\n", name.c_str());
	if (name.compare("ALL") == 0)
	{
		//printf("doing all\n");
		for (uint i = 0; i < m_nEntityCount; i++)
		{
			processCollisions(i);
		}
		return;
	}
	int idx = this->GetIndex(name);
	if (idx < 0)
		return;
	processCollisions(idx);
}

/////////////////////////////////////////////////////////////////////
// processCollisions() - process collisions of entity of given id
/////////////////////////////////////////////////////////////////////
void MyEntityManager::processCollisions(int idx)
{
	//Get Colliding List
	std::vector<int> collisions = m_pBOMngr->GetCollidingVector(idx);
	//Apply Col
	for (int i = 0; i < collisions.size(); i++)
	{
		m_lEntity[idx]->ApplyCollision(m_lEntity[collisions[i]]);
	}
}

/////////////////////////////////////////////////////////////////////
// GetIndex() - return the list index of named entity
/////////////////////////////////////////////////////////////////////
int MyEntityManager::GetIndex(String name)
{
	//Find the related index
	auto var = entMap.find(name);
	//If not found return -1
	if (var == entMap.end())
		return -1;
	return var->second;//Get the index
}

/////////////////////////////////////////////////////////////////////
// SetRenderGeometry() - sets whether to display entity collision
//                       boxes
/////////////////////////////////////////////////////////////////////
void MyEntityManager::SetRenderGeometry(bool display)
{
	//Pass change on to all entities
	for (uint i = 0; i < m_nEntityCount; i++)
	{
		m_lEntity[i]->SetRenderGeometry(display);
	}
}

/////////////////////////////////////////////////////////////////////
//Update() - update manager and all of its entities
/////////////////////////////////////////////////////////////////////
void MyEntityManager::Update()
{
	//UPdate each entity
	for (uint i = 0; i < m_nEntityCount; i++)
	{
		m_lEntity[i]->Update();
	}

	//Update the BO collisions
	m_pBOMngr->Update();	
}



