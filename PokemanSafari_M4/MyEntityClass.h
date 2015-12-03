/////////////////////////////////////////////////////////////////////
// File: MyEntityClass.h
// DSA2 PokemanSafari_M4
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////
#ifndef __MYENTITY_H_
#define __MYENTITY_H_

#include "MyBOManager.h"
#include "ScoreManager.h"

//TODO update this!!!....
/////////////////////////////////////////////////////////////////////
// Entity Type:
// XXXXXXXX
// ^        - (1 = character, 0 = projectile)
// 1XXXXXXX
//  ^^^     - character types (pokeman, player, reserved)?
// 11XXXXXX
//     ^^^^ - pokeman type? 
/////////////////////////////////////////////////////////////////////
#define ET_CHARACTER       ((unsigned char) 0x80)

#define ET_CHAR_POKEMAN    (((unsigned char) 0x01) | ET_CHARACTER)
#define ET_CHAR_PLAYER     (((unsigned char) 0x02) | ET_CHARACTER)
#define ET_PROJ_POKECUBE   (((unsigned char) 0x01) )

typedef unsigned char ET_TYPE;

class MyEntityClass
{
private:
	//Singletons
	MyBOManager* m_pColliderManager = nullptr;
	MeshManagerSingleton* m_pMeshManager = nullptr;
	ScoreManager* m_pScoreMngr = nullptr;

	String m_sName;              //name of entity
	ET_TYPE type;                //type code of entity

	bool m_bAlive = false;       //whether alive/active in the scene
	bool m_bCreated = false;     //whether created
	bool m_bHitReg = true;       //whether collision has begun response

	quaternion m_qOrientation = quaternion();
	vector3 m_v3Scale = vector3();
	vector3 m_v3Position = vector3();
	vector3 m_v3Velocity = vector3();
	vector3 m_v3Acceleration = vector3();

	float m_fMaxAcc = 10.0f;
	float m_fMass = 0.0f;

	//Path following data members
	std::vector<vector3>::iterator nextIt;
	std::vector<vector3> path;
	std::vector<vector3> pathDirection;
	std::vector<vector3>::iterator it;
	std::vector<vector3>::iterator dirIt;

	int currentSeg;
	float lapTime;
	float totalDistance;
	float speed;
	const float offset = 1.0f;
	

	void UpdateProjectile();
	void UpdateCharacter();
	void UpdateMaster();

public:
	/////////////////////////////////////////////////////////////////
	//Method: MyEntityClass
	//Usage: Constructor
	//Arguments: ---
	//Output: class object
	/////////////////////////////////////////////////////////////////
	MyEntityClass(String name, ET_TYPE type);

	/////////////////////////////////////////////////////////////////
	// Constructor
	//
	// @param
	//    name - entity name
	//    type - entity type
	//    time - entity path lap time
	//    movementPath - predetermined entity path
	/////////////////////////////////////////////////////////////////
	MyEntityClass(String name, ET_TYPE type, float time, std::vector<vector3> movementPath);

	/////////////////////////////////////////////////////////////////
	//Method: MyEntityClass
	//Usage: Constructor
	//Arguments: class object
	//Output: class object
	/////////////////////////////////////////////////////////////////
	MyEntityClass(MyEntityClass const& other);

	/////////////////////////////////////////////////////////////////
	//Method: operator=
	//Usage: Copy Assigment operator
	//Arguments: ---
	//Output: class object
	/////////////////////////////////////////////////////////////////
	MyEntityClass& operator=(MyEntityClass const& other);

	void SetPosition(vector3 vPos);
	vector3 GetPosition();
	void SetVelocity(vector3 vVel);
	vector3 GetVelocity();
	void SetAcceleration(vector3 vAcc);
	vector3 GetAcceleration();

	void SetMass(float m);
	float GetMass();

	void ApplyForce(vector3 force);
	
	/////////////////////////////////////////////////////////////////
	// SetAlive() - set wether entity is alive
	/////////////////////////////////////////////////////////////////
	void SetAlive(bool b);
	/////////////////////////////////////////////////////////////////
	// IsAlive() - return wether entity is alive
	/////////////////////////////////////////////////////////////////
	bool IsAlive();

	void Update();


	void ApplyCollision(MyEntityClass* other);

	/*
	Method: MyBOClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	~MyEntityClass();

protected:
	/*
	Method: MyBOClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	void Init(void);
	/*
	Method: Swap
	Usage: Exchanges member information with object
	Arguments:  class object
	Output: ---
	*/
	void Swap(MyEntityClass& other);
	/*
	Method: Release
	Usage: Releases the allocated memory
	Arguments: ---
	Output: ---
	*/
	void Release(void);
};
#endif //__MYENTITY_H_