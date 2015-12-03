/////////////////////////////////////////////////////////////////////
// File: MyEntityManager.h
// DSA2 PokemanSafari_M4
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description: Modified Entity Manager Singleton Class
//
/////////////////////////////////////////////////////////////////////

#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

//Includes
#include "MyEntityClass.h"

class MyEntityManager {

private:
	static MyEntityManager* m_pInstance;

	uint m_nEntityCount = 0;
	std::vector<MyEntityClass*> m_lEntity; //list of entities

	std::map<String, uint> entMap;

	//typedef std::map<String, MyEntityClass*>::iterator entMapIt;
	//typedef std::pair<String, MyEntityClass*> entMapPair;
//TODO COMMENTS..............
	MyBOManager* m_pBOMngr;


	MyEntityManager();

	MyEntityManager(MyEntityManager const& other);

	MyEntityManager& operator=(MyEntityManager const& other);

	~MyEntityManager();

	void Init();

	void Release();


public:

	static MyEntityManager* GetInstance();

	static void ReleaseInstance();

	int AddEntity(String name, ET_TYPE type);
	int AddEntity(String name, ET_TYPE type,
		float time, std::vector<vector3> movementPath);
	int AddEntity(MyEntityClass* entity, String name);

	MyEntityClass* GetEntity(String name);

	int GetIndex(String name);

	int GetEntityCount();

	void processCollisions(String name);
	void processCollisions(int idx);

	void Update();

    void UpdateCollisions();

};































#endif /*_ENTITYMANAGER_H_*/


