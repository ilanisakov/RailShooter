/////////////////////////////////////////////////////////////////////
// File: MyEntityClass.cpp
// DSA2 PokemanSafari_M4
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////

#include "MyEntityClass.h"

/////////////////////////////////////////////////////////////////////
//Method: MyEntityClass - Projectile
//Usage: Constructor
//Arguments: ---
//Output: class object
/////////////////////////////////////////////////////////////////////
MyEntityClass::MyEntityClass(String name, ET_TYPE type)
{
	Init();
	m_sName = name;
	this->type = type;
	//printf("%s  type[%#X]\n", name.c_str(), type);
	InstanceClass* pInst = m_pMeshManager->GetInstanceByName(m_sName);
	if (pInst != nullptr)
	{
		std::vector<vector3> vertexList = pInst->GetVertexList();
		m_pColliderManager->AddObject(/*list of verts*/vertexList, m_sName);
		m_bCreated = true;
	}
	else
	{
		m_bCreated = false;
	}
}

/////////////////////////////////////////////////////////////////////
// Constructor - for path following entity
//
// @param
//    name - entity name
//    type - entity type
//    time - entity path lap time
//    movementPath - predetermined entity path
/////////////////////////////////////////////////////////////////////
MyEntityClass::MyEntityClass(String name, ET_TYPE type, float time, std::vector<vector3> movementPath)
{
	Init();
	m_sName = name;
	this->type = type;
	//printf("%s  type[%#X]\n", name.c_str(), type);
	InstanceClass* pInst = m_pMeshManager->GetInstanceByName(m_sName);
	if (pInst != nullptr)
	{
		std::vector<vector3> vertexList = pInst->GetVertexList();
		m_pColliderManager->AddObject(/*list of verts*/vertexList, m_sName);
		m_bCreated = true;
	}
	else
	{
		m_bCreated = false;
	}

	//Setup path following..
	this->path = movementPath; // path for the character
	this->lapTime = time;
	this->currentSeg = 0; //current line segment of the track 
	this->m_v3Position = path[0];
	this->totalDistance = 0;

	//getting the magnitudes of the paths
	float x, y, z, mag;
	nextIt = path.begin() + 1;
	for (it = path.begin(); it != path.end(); ++it){
		x = nextIt->x - it->x;
		y = nextIt->y - it->y;
		z = nextIt->z - it->z;
		mag = sqrt(x * x + y * y + z * z);
		pathDirection.push_back(vector3(x / mag, y / mag, z / mag));
		totalDistance = totalDistance + mag;
		++nextIt;
		if (nextIt == path.end())
			nextIt = path.begin();
	}

	//getting constant track speed
	this->speed = totalDistance / (lapTime * 60 + 1000);

	it = path.begin();
	dirIt = pathDirection.begin();
	nextIt = path.begin() + 1;
	if (nextIt == path.end())
		nextIt = path.begin();
}

/////////////////////////////////////////////////////////////////////
// Constructor - environmental obj
//
// @param
//    name - entity name
//    type - entity type
//    verts - list of entity verts
/////////////////////////////////////////////////////////////////////
MyEntityClass::MyEntityClass(String name, ET_TYPE type, std::vector<vector3> verts)
{
	Init();
	m_sName = name;
	this->type = type;
	
	m_pColliderManager->AddObject(verts, m_sName);
	m_bCreated = true;
}

/////////////////////////////////////////////////////////////////////
//Method: MyBOClass
//Usage: Constructor
//Arguments: ---
//Output: class object
/////////////////////////////////////////////////////////////////////
void MyEntityClass::Init(void)
{
	m_v3Position = vector3();
	m_qOrientation = quaternion();
	m_v3Scale = vector3();

	m_v3Velocity = vector3();
	m_v3Acceleration = vector3();

	m_sName = "";
	m_fMaxAcc = 10.0f;
	m_fMass = 1.0f;

	m_pColliderManager = MyBOManager::GetInstance();
	m_pMeshManager = MeshManagerSingleton::GetInstance();
	m_pScoreMngr = ScoreManager::GetInstance();
}

/////////////////////////////////////////////////////////////////////
//Method: Swap
//Usage: Exchanges member information with object
//Arguments:  class object
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyEntityClass::Swap(MyEntityClass& other)
{
	std::swap(m_v3Position, other.m_v3Position);
	std::swap(m_qOrientation, other.m_qOrientation);
	std::swap(m_v3Scale, other.m_v3Scale);

	std::swap(m_v3Velocity, other.m_v3Velocity);
	std::swap(m_v3Acceleration, other.m_v3Acceleration);

	std::swap(m_fMaxAcc, other.m_fMaxAcc);
	std::swap(m_sName, other.m_sName);
	std::swap(m_pColliderManager, other.m_pColliderManager);
	std::swap(m_pMeshManager, other.m_pMeshManager);
	std::swap(m_pScoreMngr, other.m_pScoreMngr);

	std::swap(type, other.type);
	std::swap(m_bAlive, other.m_bAlive);
	std::swap(m_bCreated, other.m_bCreated);
	std::swap(m_bHitReg, other.m_bHitReg);
	std::swap(m_bRenderGeo, other.m_bRenderGeo);
	std::swap(m_bHitGround, other.m_bHitGround);
	std::swap(stillCount, other.stillCount);

	std::swap(m_fMass, other.m_fMass);

	std::swap(nextIt, other.nextIt);
	std::swap(path, other.path);
	std::swap(pathDirection, other.pathDirection);
	std::swap(it, other.it);
	std::swap(dirIt, other.dirIt);

	std::swap(currentSeg, other.currentSeg);
	std::swap(lapTime, other.lapTime);
	std::swap(totalDistance, other.totalDistance);
	std::swap(speed, other.speed);
}

/////////////////////////////////////////////////////////////////////
//Method: MyEntityClass
//Usage: Constructor
//Arguments: class object
//Output: class object
/////////////////////////////////////////////////////////////////////
MyEntityClass::MyEntityClass(MyEntityClass const& other)
{
	m_v3Position = other.m_v3Position;
	m_qOrientation = other.m_qOrientation;
	m_v3Scale = other.m_v3Scale;

	m_v3Velocity = other.m_v3Velocity;
	m_v3Acceleration = other.m_v3Acceleration;

	m_sName = other.m_sName;
	type = other.type;
	m_fMaxAcc = other.m_fMaxAcc;
	m_fMass = other.m_fMass;

	m_pColliderManager = other.m_pColliderManager;
	m_pMeshManager = other.m_pMeshManager;
	m_pScoreMngr = other.m_pScoreMngr;

	m_bAlive = other.m_bAlive;
	m_bCreated = other.m_bCreated;
	m_bHitReg = other.m_bHitReg;
	m_bRenderGeo = other.m_bRenderGeo;
	m_bHitGround = other.m_bHitGround;
	stillCount = other.stillCount;

	nextIt = other.nextIt;
	path = other.path;
	pathDirection = other.pathDirection;
	it = other.it;
	dirIt = other.dirIt;
	currentSeg = other.currentSeg;
	lapTime = other.lapTime;
	totalDistance = other.totalDistance;
	speed = other.speed;
}

/////////////////////////////////////////////////////////////////////
//Method: operator=
//Usage: Copy Assigment operator
//Arguments: ---
//Output: class object
/////////////////////////////////////////////////////////////////////
MyEntityClass& MyEntityClass::operator=(MyEntityClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyEntityClass temp(other);
		Swap(temp);
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////
// SetPosition() - set the psotion of the entity
/////////////////////////////////////////////////////////////////////
void MyEntityClass::SetPosition(vector3 vPos)
{
	m_v3Position = vPos;
}

/////////////////////////////////////////////////////////////////////
// GetPosition() -  return the position of the entity
/////////////////////////////////////////////////////////////////////
vector3 MyEntityClass::GetPosition()
{
	return m_v3Position;
}

/////////////////////////////////////////////////////////////////////
// SetVelocity() - set the velocity of the entity
/////////////////////////////////////////////////////////////////////
void MyEntityClass::SetVelocity(vector3 vVel)
{
	m_v3Velocity = vVel;
}

/////////////////////////////////////////////////////////////////////
// GetVelocity() - return the velocity of the entity
/////////////////////////////////////////////////////////////////////
vector3 MyEntityClass::GetVelocity()
{
	return m_v3Velocity;
}

/////////////////////////////////////////////////////////////////////
// SetAcceleration - set acceleration of the entity
/////////////////////////////////////////////////////////////////////
void MyEntityClass::SetAcceleration(vector3 vAcc)
{
	m_v3Acceleration = vAcc;
}

/////////////////////////////////////////////////////////////////////
// GetAcceleration() - return the accleration of the entity
/////////////////////////////////////////////////////////////////////
vector3 MyEntityClass::GetAcceleration()
{
	return m_v3Acceleration;
}

/////////////////////////////////////////////////////////////////////
// SetMass() - sets the mass of the entity
/////////////////////////////////////////////////////////////////////
void MyEntityClass::SetMass(float m)
{
	m_fMass = m;
}

/////////////////////////////////////////////////////////////////////
// GEtMass() - returns the mass of the entity
/////////////////////////////////////////////////////////////////////
float MyEntityClass::GetMass()
{
	return m_fMass;
}

/////////////////////////////////////////////////////////////////////
// ApplyForce() - apply force to entity
//
// @param - force to apply
/////////////////////////////////////////////////////////////////////
void MyEntityClass::ApplyForce(vector3 force)
{
	m_v3Acceleration[0] += force[0] / m_fMass;
	m_v3Acceleration[1] += force[1] / m_fMass;
	m_v3Acceleration[2] += force[2] / m_fMass;
}

/////////////////////////////////////////////////////////////////////
// SetRenderGeomettry() - sets whether display BO box
//
// @param - whether to display collision box
/////////////////////////////////////////////////////////////////////
void MyEntityClass::SetRenderGeometry(bool display)
{
	m_bRenderGeo = display;
}

/////////////////////////////////////////////////////////////////////
// SetAlive() - set wether projectile is alive
/////////////////////////////////////////////////////////////////////
void MyEntityClass::SetAlive(bool b)
{
	m_bAlive = b;
	m_bHitReg = false;
}
/////////////////////////////////////////////////////////////////////
// IsAlive() - return wether projectile is alive
/////////////////////////////////////////////////////////////////////
bool MyEntityClass::IsAlive()
{
	return m_bAlive;
}

/////////////////////////////////////////////////////////////////////
// Update() - updates entity in the scene
/////////////////////////////////////////////////////////////////////
void MyEntityClass::Update()
{
	if (type & ET_ENVIRONMENT)
		UpdateMaster();
	else if (type & ET_CHARACTER)
		UpdateCharacter();
	else if (type & ET_PROJECTILE)
	{
		//Special behavior (sitting on ground)
		if (m_bHitGround)
		{
			if (stillCount == 0)
			{
				this->SetPosition(vector3(-100, -100, -100));

				m_v3Velocity[0] = 0.0f;
				m_v3Velocity[2] = 0.0f;
				if (m_v3Velocity[1] > 0.0f)
					m_v3Velocity[1] *= -2.0f;
				else
					m_v3Velocity[1] *= 2.0f;

				m_bHitGround = false;
				UpdateProjectile();
				return;
			}
			stillCount--;
			matrix4 m4Mod;
			m4Mod = glm::translate(m_v3Position);
			m_pMeshManager->SetModelMatrix(m4Mod, m_sName);
			m_pMeshManager->AddInstanceToRenderList(m_sName);

			int nIndex = m_pColliderManager->GetIndex(m_sName);
			m_pColliderManager->SetModelMatrix(m4Mod, m_sName);

			if (m_bRenderGeo)
			{
				m_pColliderManager->DisplayReAlligned(nIndex);
			}
			return;
		}

		UpdateProjectile();
	}
	    
}

/////////////////////////////////////////////////////////////////////
// UpdateProjectile() - aux update method for projectile types
/////////////////////////////////////////////////////////////////////
void MyEntityClass::UpdateProjectile()
{
	if (!m_bAlive)
		return;
	//Else alive

	//basic pokecube
	//check killzone?
	vector3 pos = GetPosition();
	//printf("PC:ps x[%f] y[%f] z[%f]\n", pos[0], pos[1], pos[2]);
	if (pos[1] < -30.0f)
	{
		m_bAlive = false;
	}
	else
	{
		//move
		MyEntityClass::UpdateMaster();
		//Update region in octtree
		m_pColliderManager->UpdateTree(m_sName);
	}
}

/////////////////////////////////////////////////////////////////////
// UpdateCharacter() - aux update method for character types
/////////////////////////////////////////////////////////////////////
void MyEntityClass::UpdateCharacter()
{
	m_v3Velocity = vector3(dirIt->x * speed, dirIt->y * speed, dirIt->z * speed);

	//MyEntityClass's Update
	UpdateMaster();
	//UPdate region in octtree
	m_pColliderManager->UpdateTree(m_sName);

	//checking if it's time to move onto the next path segment
	if (m_v3Position.x >= nextIt->x - offset && m_v3Position.x <= nextIt->x + offset){
		if (m_v3Position.y >= nextIt->y - offset && m_v3Position.y <= nextIt->y + offset){
			if (m_v3Position.z >= nextIt->z - offset && m_v3Position.z <= nextIt->z + offset){
				//std::cout << "SWITCH" << std::endl;
				it++;
				if (it == path.end())
					it = path.begin();
				dirIt++;
				if (dirIt == pathDirection.end())
					dirIt = pathDirection.begin();
				nextIt++;
				if (nextIt == path.end())
					nextIt = path.begin();
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////
// UpdateMaster() - aux update method for common phys updates
/////////////////////////////////////////////////////////////////////
void MyEntityClass::UpdateMaster()
{
	m_v3Velocity += m_v3Acceleration;
	m_v3Position = m_v3Position + (m_v3Velocity * m_fMass);

	matrix4 m4Mod;

	m4Mod = glm::translate(m_v3Position);

	m_pMeshManager->SetModelMatrix(m4Mod, m_sName);
	m_pMeshManager->AddInstanceToRenderList(m_sName);

	int nIndex = m_pColliderManager->GetIndex(m_sName);
	m_pColliderManager->SetModelMatrix(m4Mod, m_sName);

	if (m_bRenderGeo)
	{
		m_pColliderManager->DisplayReAlligned(nIndex);
	}
}

/////////////////////////////////////////////////////////////////////
// ApplyCollision() - collision reaction
//
// @param - entity in which colliding with
/////////////////////////////////////////////////////////////////////
void MyEntityClass::ApplyCollision(MyEntityClass* other)
{
	//std::cout << m_sName << " do something about it\n";
	//std::cout << other->m_sName << " hit! ";

	if (!m_bHitReg)
	{
		//Hit Pokeman, register score
		if (other->type & ET_CHAR_POKEMAN)
		{
			int score = 100;
			float otherVel = glm::length(other->m_v3Velocity) *10.0f;
			if (otherVel < 1.0f && otherVel >= 0.5f)
				score += 30;
			else if (otherVel < 0.5f && otherVel >= 0.25f)
				score += 15;
			else if (otherVel < 0.25f && otherVel > 0.0f)
				score += 5;

			m_pScoreMngr->AddScore(score, other->m_sName);
			other->SetPosition(vector3(-1000, -1000, -1000));
			m_bHitReg = true;

			//Move to kill zone
			m_v3Velocity[1] = -35.0f;

		}
		//Hit wall, bounce
		else if (other->type & ET_ENVI_WALL)
		{
			
			m_v3Velocity[0] *= -1.0f;
			m_v3Velocity[2] *= -1.0f;

			if (m_v3Velocity[1] > 0.0f)
				m_v3Velocity[1] *= -2.0f;
		}
		//Hit ground, stick then disappear
		else if (other->type & ET_ENVI_GROUND)
		{

			m_bHitReg = true;
			m_bHitGround = true;
			stillCount = PC_STILLCOUNT;
		}
	}

}

/////////////////////////////////////////////////////////////////////
//Method: Release
//Usage: Releases the allocated memory
//Arguments: ---
//Output: ---
/////////////////////////////////////////////////////////////////////
void MyEntityClass::Release(void)
{
	//Nothing todo
}

/////////////////////////////////////////////////////////////////////
//Method: MyBOClass
//Usage: Constructor
//Arguments: ---
//Output: class object
/////////////////////////////////////////////////////////////////////
MyEntityClass::~MyEntityClass()
{
	Release();
}