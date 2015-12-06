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

MyEntityManager* MyEntityManager::m_pInstance = nullptr;

MyEntityManager* MyEntityManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyEntityManager();
	}
	return m_pInstance;
}

void MyEntityManager::ReleaseInstance()
{
//TODO delete entity list
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//TODOOOOOOOOO
MyEntityManager::MyEntityManager()
{
	m_pBOMngr = MyBOManager::GetInstance();
	m_nEntityCount = 0;
}
MyEntityManager::MyEntityManager(MyEntityManager const& other)
{

}
MyEntityManager& MyEntityManager::operator = (MyEntityManager const& other)
{
	return *this;
}
MyEntityManager::~MyEntityManager()
{
	ReleaseInstance();
}


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

int MyEntityManager::AddEntity(String name, ET_TYPE type, 
	float time, std::vector<vector3> movementPath)
{
	MyEntityClass* ent = new MyEntityClass(name,type,time,movementPath);
	//MyEntityClass* ent = new MyEntityClass(name);
	if (ent == nullptr)
		return 0;
	
	m_lEntity.push_back(ent);
	entMap[name] = m_nEntityCount;
	m_nEntityCount++;
	return 1;
}

int MyEntityManager::AddEntity(String name, ET_TYPE type, std::vector<vector3> verts)
{
	MyEntityClass* ent = new MyEntityClass(name, type, verts);
	//MyEntityClass* ent = new MyEntityClass(name);
	if (ent == nullptr)
		return 0;

	m_lEntity.push_back(ent);
	entMap[name] = m_nEntityCount;
	m_nEntityCount++;
	return 1;
}

//TODO FIXME ---BAD
int MyEntityManager::AddEntity(MyEntityClass* entity, String name)
{
	if (entity == nullptr)
		return 0;

	m_lEntity.push_back(entity);
	entMap[name] = m_nEntityCount;
	m_nEntityCount++;
	return 1;
}

MyEntityClass* MyEntityManager::GetEntity(String name)
{
	//Find the related index
	auto var = entMap.find(name);
	//If not found return -1
	if (var == entMap.end())
		return NULL;

	return m_lEntity[static_cast<uint>(var->second)];
}

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
void MyEntityManager::processCollisions(int idx)
{
	//if (idx >(m_nEntityCount - 1) || idx < 0)
	//	return;
	//Else process 
	//IDxs will be the same in BOmanager!!
	//std::vector<int> collisionList = m_pBOMngr->GetCollidingVector(idx);
	
	//for (int i = 0; i < collisionList.size(); i++)
	//{
	//	//wwwwaprintf("COLLISION>");
	//	m_lEntity[idx]->ApplyCollision(m_lEntity[i]);
	//}
	//m_lEntity[idx]

	std::vector<int> collisions = m_pBOMngr->GetCollidingVector(idx);
	//printf("\t collVecSize [%d]\n", collisions.size());
	for (int i = 0; i < collisions.size(); i++)
	{
		m_lEntity[idx]->ApplyCollision(m_lEntity[collisions[i]]);
	}
}

int MyEntityManager::GetIndex(String name)
{
	//Find the related index
	auto var = entMap.find(name);
	//If not found return -1
	if (var == entMap.end())
		return -1;
	return var->second;//Get the index
}

void MyEntityManager::SetRenderGeometry(bool display)
{
	for (uint i = 0; i < m_nEntityCount; i++)
	{
		m_lEntity[i]->SetRenderGeometry(display);
	}
}

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

void MyEntityManager::UpdateCollisions()
{
	//m_pBOMngr->Update();


}



