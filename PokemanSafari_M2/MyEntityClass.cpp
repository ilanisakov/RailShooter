#include "MyEntityClass.h"
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
}
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
void MyEntityClass::Release(void)
{
}

MyEntityClass::MyEntityClass(String n)
{
	Init();
	m_sName = n;

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

void MyEntityClass::Update(void)
{

	m_v3Velocity += m_v3Acceleration;
	m_v3Position = m_v3Position + (m_v3Velocity * m_fMass);

	matrix4 m4Mod;

	m4Mod = glm::translate(m_v3Position);

	m_pMeshManager->SetModelMatrix(m4Mod, m_sName);
	m_pMeshManager->AddInstanceToRenderList(m_sName);

	int nIndex = m_pColliderManager->GetIndex(m_sName);
	m_pColliderManager->SetModelMatrix(m4Mod, m_sName);
	m_pColliderManager->DisplayReAlligned(nIndex);

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
void MyEntityClass::SetAcceleration(vector3 vAcc)
{
	m_v3Acceleration = vAcc;
}

void MyEntityClass::ApplyForce(vector3 force)
{
	m_v3Acceleration[0] += force[0] / m_fMass;
	m_v3Acceleration[1] += force[1] / m_fMass;
	m_v3Acceleration[2] += force[2] / m_fMass;

	
}



void MyEntityClass::SetMass(float m)
{
	m_fMass = m;
}
float MyEntityClass::GetMass()
{
	return m_fMass;
}

MyEntityClass::~MyEntityClass()
{
}