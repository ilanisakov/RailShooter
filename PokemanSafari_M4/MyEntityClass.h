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

/////////////////////////////////////////////////////////////////////
// Entity Type Macros
/////////////////////////////////////////////////////////////////////
#define ET_CHAR_POKEMAN    (((unsigned char) 0x10) )
#define ET_CHAR_PLAYER     (((unsigned char) 0x20) )
#define ET_PROJ_POKECUBE   (((unsigned char) 0x80) )
#define ET_ENVI_GROUND     (((unsigned char) 0x01) )
#define ET_ENVI_WALL       (((unsigned char) 0x02) )

//Combine Macros for Group Identification
#define ET_CHARACTER       (ET_CHAR_POKEMAN | ET_CHAR_PLAYER)
#define ET_ENVIRONMENT     (ET_ENVI_GROUND | ET_ENVI_WALL)
#define ET_PROJECTILE      (ET_PROJ_POKECUBE)

//Pokecube Ground Freeze Duration
#define PC_STILLCOUNT      25

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
	bool m_bRenderGeo = false;   //whether to render collision box

	bool m_bHitGround = false;   //whether hit the ground
	int stillCount = 0;          //how long has it been sitting on the ground

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
	
	/////////////////////////////////////////////////////////////////
	// UpdateProjectile() - aux update method for projectile types
	/////////////////////////////////////////////////////////////////
	void UpdateProjectile();

	/////////////////////////////////////////////////////////////////
	// UpdateCharacter() - aux update method for character types
	/////////////////////////////////////////////////////////////////
	void UpdateCharacter();

	/////////////////////////////////////////////////////////////////
	// UpdateMaster() - aux update method for common phys updates
	/////////////////////////////////////////////////////////////////
	void UpdateMaster();

public:
	/////////////////////////////////////////////////////////////////
	//Method: MyEntityClass - Projectile
	//Usage: Constructor
	//Arguments: ---
	//Output: class object
	/////////////////////////////////////////////////////////////////
	MyEntityClass(String name, ET_TYPE type);

	/////////////////////////////////////////////////////////////////
	// Constructor - path following entity
	//
	// @param
	//    name - entity name
	//    type - entity type
	//    time - entity path lap time
	//    movementPath - predetermined entity path
	/////////////////////////////////////////////////////////////////
	MyEntityClass(String name, ET_TYPE type, float time, std::vector<vector3> movementPath);

	/////////////////////////////////////////////////////////////////
	// Constructor - environmental obj
	//
	// @param
	//    name - entity name
	//    type - entity type
	//    verts - list of entity verts
	/////////////////////////////////////////////////////////////////
	MyEntityClass(String name, ET_TYPE type, std::vector<vector3> verts);

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

	/////////////////////////////////////////////////////////////////
	// SetPosition() - set the psotion of the entity
	/////////////////////////////////////////////////////////////////
	void SetPosition(vector3 vPos);

	/////////////////////////////////////////////////////////////////
	// GetPosition() -  return the position of the entity
	/////////////////////////////////////////////////////////////////
	vector3 GetPosition();

	/////////////////////////////////////////////////////////////////
	// SetVelocity() - set the velocity of the entity
	/////////////////////////////////////////////////////////////////
	void SetVelocity(vector3 vVel);

	/////////////////////////////////////////////////////////////////
	// GetVelocity() - return the velocity of the entity
	/////////////////////////////////////////////////////////////////
	vector3 GetVelocity();

	/////////////////////////////////////////////////////////////////
	// SetAcceleration - set acceleration of the entity
	/////////////////////////////////////////////////////////////////
	void SetAcceleration(vector3 vAcc);

	/////////////////////////////////////////////////////////////////
	// GetAcceleration() - return the accleration of the entity
	/////////////////////////////////////////////////////////////////
	vector3 GetAcceleration();

	/////////////////////////////////////////////////////////////////
	// SetMass() - sets the mass of the entity
	/////////////////////////////////////////////////////////////////
	void SetMass(float m);

	/////////////////////////////////////////////////////////////////
	// GEtMass() - returns the mass of the entity
	/////////////////////////////////////////////////////////////////
	float GetMass();

	/////////////////////////////////////////////////////////////////
	// ApplyForce() - apply force to entity
	//
	// @param - force to apply
	/////////////////////////////////////////////////////////////////
	void ApplyForce(vector3 force);
	
	/////////////////////////////////////////////////////////////////
	// SetRenderGeomettry() - sets whether display BO box
	//
	// @param - whether to display collision box
	/////////////////////////////////////////////////////////////////
	void SetRenderGeometry(bool display);

	/////////////////////////////////////////////////////////////////
	// SetAlive() - set wether entity is alive
	/////////////////////////////////////////////////////////////////
	void SetAlive(bool b);

	/////////////////////////////////////////////////////////////////
	// IsAlive() - return wether entity is alive
	/////////////////////////////////////////////////////////////////
	bool IsAlive();

	/////////////////////////////////////////////////////////////////
	// Update() - updates entity in the scene
	/////////////////////////////////////////////////////////////////
	void Update();

	/////////////////////////////////////////////////////////////////
	// ApplyCollision() - collision reaction
	//
	// @param - entity in which colliding with
	/////////////////////////////////////////////////////////////////
	void ApplyCollision(MyEntityClass* other);

	/////////////////////////////////////////////////////////////////
	//Method: MyBOClass
	//Usage: Constructor
	//Arguments: ---
	//Output: class object
	/////////////////////////////////////////////////////////////////
	~MyEntityClass();

protected:
	/////////////////////////////////////////////////////////////////
	//Method: MyBOClass
	//Usage: Constructor
	//Arguments: ---
	//Output: class object
	/////////////////////////////////////////////////////////////////
	void Init(void);

	/////////////////////////////////////////////////////////////////
	//Method: Swap
	//Usage: Exchanges member information with object
	//Arguments:  class object
	//Output: ---
	/////////////////////////////////////////////////////////////////
	void Swap(MyEntityClass& other);
	
	/////////////////////////////////////////////////////////////////
	//Method: Release
	//Usage: Releases the allocated memory
	//Arguments: ---
	//Output: ---
	/////////////////////////////////////////////////////////////////
	void Release(void);
};
#endif //__MYENTITY_H_