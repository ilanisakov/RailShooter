/////////////////////////////////////////////////////////////////////
// E14 - Entity Manager
// Team: Ilan Isakov, Marty Kurtz, Mary Spencer
//
// MyEntityManager.h
/////////////////////////////////////////////////////////////////////

#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include "Projectile.h"
#include "Character.h"

class MyEntityManager {

private:
	static MyEntityManager* m_pInstance;

	int m_nEntityCount = 0;
	std::vector<MyEntityClass*> m_lEntity; //list of entities

	std::map<String, uint> entMap;

	//typedef std::map<String, MyEntityClass*>::iterator entMapIt;
	//typedef std::pair<String, MyEntityClass*> entMapPair;
//TODO COMMENTS..............
	MyBOManager* m_pBOMngr;


	MyEntityManager();

	MyEntityManager(MyEntityManager const& other);

	MyEntityManager& operator=(MyEntityManager const& other);

	~MyEntityManager(void);


	void Init(void);


public:

	static MyEntityManager* GetInstance();

	static void ReleaseInstance(void);

	int AddEntity(String entity, PROJECTILE_TYPE type);
	int AddEntity(String name, CHARACTER_TYPE type,
		float time, std::vector<vector3> movementPath);


	int AddEntity(MyEntityClass* entity, String name);
	MyEntityClass* GetEntity(String entity);

	void processCollisions(String name);
	void processCollisions(uint idx);

	int GetIndex(String name);

    void UpdateCollisions();

};































#endif /*_ENTITYMANAGER_H_*/


