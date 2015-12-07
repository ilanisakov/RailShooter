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

/////////////////////////////////////////////////////////////////
//Method: MyEntityClass
//Usage: Constructor
//Arguments: ---
//Output: class object
/////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////
// Constructor - for path following entity
//
// @param
//    name - entity name
//    type - entity type
//    time - entity path lap time
//    movementPath - predetermined entity path
/////////////////////////////////////////////////////////////////
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

MyEntityClass::MyEntityClass(String name, ET_TYPE type, std::vector<vector3> verts)
{
	Init();
	m_sName = name;
	this->type = type;
	
	m_pColliderManager->AddObject(verts, m_sName);
	m_bCreated = true;
}

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

//TODO FIXME
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
}

//TODO FIXME
MyEntityClass::MyEntityClass(MyEntityClass const& other)
{
	m_v3Position = other.m_v3Position;
	m_qOrientation = other.m_qOrientation;
	m_v3Scale = other.m_v3Scale;

	m_v3Velocity = other.m_v3Velocity;
	m_v3Acceleration = other.m_v3Acceleration;

	m_sName = other.m_sName;
	m_fMaxAcc = other.m_fMaxAcc;


	m_pColliderManager = other.m_pColliderManager;
	m_pMeshManager = other.m_pMeshManager;
}

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

void MyEntityClass::SetPosition(vector3 vPos)
{
	m_v3Position = vPos;
}
vector3 MyEntityClass::GetPosition()
{
	return m_v3Position;
}

void MyEntityClass::SetVelocity(vector3 vVel)
{
	m_v3Velocity = vVel;
}
vector3 MyEntityClass::GetVelocity()
{
	return m_v3Velocity;
}

void MyEntityClass::SetAcceleration(vector3 vAcc)
{
	m_v3Acceleration = vAcc;
}
vector3 MyEntityClass::GetAcceleration()
{
	return m_v3Acceleration;
}
void MyEntityClass::SetMass(float m)
{
	m_fMass = m;
}
float MyEntityClass::GetMass()
{
	return m_fMass;
}

void MyEntityClass::ApplyForce(vector3 force)
{
	m_v3Acceleration[0] += force[0] / m_fMass;
	m_v3Acceleration[1] += force[1] / m_fMass;
	m_v3Acceleration[2] += force[2] / m_fMass;
}

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

void MyEntityClass::Update()
{
	if (type & ET_ENVIRONMENT)
		UpdateMaster();
	else if (type & ET_CHARACTER)
		UpdateCharacter();
	else if (type & ET_PROJECTILE)
	{
		if (m_bHitGround)
		{
			if (stillCount == 0)
			{
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
		m_pColliderManager->UpdateTree(m_sName);
	}
}

void MyEntityClass::UpdateCharacter()
{
	m_v3Velocity = vector3(dirIt->x * speed, dirIt->y * speed, dirIt->z * speed);

	//MyEntityClass's Update
	UpdateMaster();
	m_pColliderManager->UpdateTree(m_sName);

	//checking if it's time to move onto the next path segment
	if (m_v3Position.x >= nextIt->x - offset && m_v3Position.x <= nextIt->x + offset){
		if (m_v3Position.y >= nextIt->y - offset && m_v3Position.y <= nextIt->y + offset){
			if (m_v3Position.z >= nextIt->z - offset && m_v3Position.z <= nextIt->z + offset){
//				std::cout << "SWITCH" << std::endl;
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



void MyEntityClass::ApplyCollision(MyEntityClass* other)
{
	//std::cout << m_sName << " do something about it\n";
	std::cout << other->m_sName << " hit! ";

	if (!m_bHitReg)
	{
		if (other->type & ET_CHAR_POKEMAN)
		{
			int score = 100;
			float otherVel = glm::length(other->m_v3Velocity) *10.0f;
//			printf("Velocity [%f]\n", otherVel);
			if (otherVel < 1.0f && otherVel >= 0.5f)
				score += 30;
			else if (otherVel < 0.5f && otherVel >= 0.25f)
				score += 15;
			else if (otherVel < 0.25f && otherVel > 0.0f)
				score += 5;

			//printf("Name[%s] Other[%s]", m_sName.c_str(),
			//	other->m_sName.c_str());

			m_pScoreMngr->AddScore(score, other->m_sName);

			m_bHitReg = true;

			//Move to kill zone
			m_v3Velocity[1] = -35.0f;

		}
		else if (other->type & ET_ENVI_WALL)
		{
			//float x = glm::abs(m_v3Velocity[0]);
			//float z = glm::abs(m_v3Velocity[2]);
			//if (x > z)
			//{
			//	m_v3Velocity[2] *= -1.0f;
			//}
			//else
			//{
			//	m_v3Velocity[0] *= -1.0f;
			//}
			//m_v3Velocity[1] *= 2.0f;

			//vector3 dir = this->m_v3Position - other->m_v3Position;
			//dir = glm::normalize(dir);

			//float theta = glm::acos(glm::dot(dir, vector3(0.0f, 0.0f, 1.0f)));
			//printf("THeta %f\n", theta);
			//if (theta )
			
			m_v3Velocity[0] *= -1.0f;
			m_v3Velocity[2] *= -1.0f;

			if (m_v3Velocity[1] > 0.0f)
				m_v3Velocity[1] *= -2.0f;
		}
		else if (other->type & ET_ENVI_GROUND)
		{
			m_bHitReg = true;
			m_bHitGround = true;
			stillCount = PC_STILLCOUNT;
		}
	}

}

void MyEntityClass::Release(void)
{
	//Nothing todo
}

MyEntityClass::~MyEntityClass()
{
	Release();
}