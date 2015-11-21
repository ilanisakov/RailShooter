/////////////////////////////////////////////////////////////////////
// E14 - Entity Manager
// Team: Ilan Isakov, Marty Kurtz, Mary Spencer
//
// MyEntityManager.cpp
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
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

int MyEntityManager::AddEntity(String name, PROJECTILE_TYPE type)
{
	MyEntityClass* ent = new Projectile(type, name);
	//MyEntityClass* ent = new MyEntityClass(name);
	if (ent != nullptr)
	{
		m_lEntity.push_back(ent);
		entMap[name] = m_nEntityCount;
	}
	m_nEntityCount = m_lEntity.size();

	return 1;
}

int MyEntityManager::AddEntity(String name, CHARACTER_TYPE type, 
	float time, std::vector<vector3> movementPath)
{
	MyEntityClass* ent = new Character(type,name,time,movementPath);
	//MyEntityClass* ent = new MyEntityClass(name);
	if (ent != nullptr)
	{
		m_lEntity.push_back(ent);
		entMap[name] = m_nEntityCount;
	}
	m_nEntityCount = m_lEntity.size();

	return 1;
}

int MyEntityManager::AddEntity(MyEntityClass* entity, String name)
{
	m_lEntity.push_back(entity);
	entMap[name] = m_nEntityCount;
	m_nEntityCount = m_lEntity.size();
	return 1;
}

MyEntityClass* MyEntityManager::GetEntity(String name)
{
	//Find the related index
	auto var = entMap.find(name);
	//If not found return -1
	if (var == entMap.end())
		return NULL;

	return m_lEntity[static_cast<int>(var->second)];
}

void MyEntityManager::processCollisions(String name)
{
	if (name.compare("ALL") == 0)
	{
		for (int i = 0; i < m_nEntityCount; i++)
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
void MyEntityManager::processCollisions(uint idx)
{
	if (idx >(m_nEntityCount - 1) || idx < 0)
		return;
	//Else process 
	//IDxs will be the same in BOmanager!!
	std::vector<int> collisionList = m_pBOMngr->GetCollidingVector(idx);
	
	for (int i = 0; i < collisionList.size(); i++)
	{
		//wwwwaprintf("COLLISION>");
		m_lEntity[idx]->ApplyCollision(m_lEntity[i]);
	}
	//m_lEntity[idx] 
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

void MyEntityManager::UpdateCollisions()
{
	m_pBOMngr->Update();


}


MyEntityManager::MyEntityManager()
{
	m_pBOMngr = MyBOManager::GetInstance();
}
//TODOOOOOOOOO
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
