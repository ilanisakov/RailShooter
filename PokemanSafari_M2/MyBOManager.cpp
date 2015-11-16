#include "MyBOManager.h"
//  MyBOManager
MyBOManager* MyBOManager::m_pInstance = nullptr;
void MyBOManager::Init(void)
{
	m_nObjectCount = 0;
	pMeshMngr = MeshManagerSingleton::GetInstance();
}
void MyBOManager::Release(void)
{
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		if (m_lObject[nObject] != nullptr)
		{
			delete m_lObject[nObject];
			m_lObject[nObject] = nullptr;
		}
		m_llCollidingIndices[nObject].clear();
	}
	m_lObject.clear();
	m_llCollidingIndices.clear();
}
MyBOManager* MyBOManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new MyBOManager();
	}
	return m_pInstance;
}
void MyBOManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
MyBOManager::MyBOManager(){Init();}
MyBOManager::MyBOManager(MyBOManager const& other){ }
MyBOManager& MyBOManager::operator=(MyBOManager const& other) { return *this; }
MyBOManager::~MyBOManager(){Release();};
//Accessors
MyBOClass* MyBOManager::GetObject(uint a_nIndex)
{
	if (a_nIndex < m_nObjectCount)
		return m_lObject[a_nIndex];

	return nullptr;
}
//--- Non Standard Singleton Methods
void MyBOManager::AddObject(std::vector<vector3> a_lVertex, String a_sName)
{
	MyBOClass* pObject = new MyBOClass(a_lVertex);
	if (pObject != nullptr)
	{
		m_lObject.push_back(pObject);//Add the Object
		m_mapIndex[a_sName] = m_nObjectCount; //Add entry to the dictionary
	}
	m_nObjectCount = m_lObject.size();
	std::vector<int> lVector;
	m_llCollidingIndices.push_back(lVector);
}
void MyBOManager::SetModelMatrix(matrix4 a_mModelMatrix, String a_sIndex)
{
	//find the object
	int nIndex = this->GetIndex(a_sIndex);
	if (nIndex < 0) //if not found return
		return;

	m_lObject[nIndex]->SetModelMatrix(a_mModelMatrix);//set the matrix for the indexed Object
}
void MyBOManager::DisplaySphere(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		bool bColliding = false;
		for (uint n = 0; n < m_nObjectCount; n++)
		{
			if (m_llCollidingIndices[n].size() > 0)
			{
				bColliding = true;
				break;
			}
		}

		if (v3Color == REDEFAULT)
		{
			if (!bColliding)
				v3Color = REWHITE;
			else
				v3Color = RERED;
		}

		pMeshMngr->AddSphereToQueue(
			m_lObject[a_nIndex]->GetModelMatrix() *
			glm::translate(IDENTITY_M4, m_lObject[a_nIndex]->GetCenterLocal()) *
			glm::scale(vector3(m_lObject[a_nIndex]->GetRadius() * 2.0f)),
			v3Color,
			WIRE);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			bool bColliding = false;
			for (uint n = 0; n < m_nObjectCount; n++)
			{
				if (m_llCollidingIndices[n].size() > 0)
				{
					bColliding = true;
					break;
				}
			}

			if (v3Color == REDEFAULT)
			{
				if (!bColliding)
					v3Color = REWHITE;
				else
					v3Color = RERED;
			}
			pMeshMngr->AddSphereToQueue(
				m_lObject[nObject]->GetModelMatrix() *
				glm::translate(IDENTITY_M4, m_lObject[nObject]->GetCenterLocal()) *
				glm::scale(vector3(m_lObject[nObject]->GetRadius() * 2.0f)),
				v3Color,
				WIRE);
		}
	}
}
void MyBOManager::DisplayOriented(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		bool bColliding = false;
		for (uint n = 0; n < m_nObjectCount; n++)
		{
			if (m_llCollidingIndices[n].size() > 0)
			{
				bColliding = true;
				break;
			}
		}

		if (v3Color == REDEFAULT)
		{
			if (!bColliding)
				v3Color = REWHITE;
			else
				v3Color = RERED;
		}

		pMeshMngr->AddCubeToQueue(
			m_lObject[a_nIndex]->GetModelMatrix() *
			glm::translate(IDENTITY_M4, m_lObject[a_nIndex]->GetCenterLocal()) *
			glm::scale(m_lObject[a_nIndex]->GetHalfWidth() * 2.0f),
			v3Color,
			WIRE);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			bool bColliding = false;
			for (uint n = 0; n < m_nObjectCount; n++)
			{
				if (m_llCollidingIndices[n].size() > 0)
				{
					bColliding = true;
					break;
				}
			}

			if (v3Color == REDEFAULT)
			{
				if (!bColliding)
					v3Color = REWHITE;
				else
					v3Color = RERED;
			}
			pMeshMngr->AddCubeToQueue(
				m_lObject[nObject]->GetModelMatrix() *
				glm::translate(IDENTITY_M4, m_lObject[nObject]->GetCenterLocal()) *
				glm::scale(m_lObject[nObject]->GetHalfWidth() * 2.0f),
				v3Color,
				WIRE);
		}
	}
}
void MyBOManager::DisplayReAlligned(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		bool bColliding = false;
		for (uint n = 0; n < m_nObjectCount; n++)
		{
			if (m_llCollidingIndices[n].size() > 0)
			{
				bColliding = true;
				break;
			}
		}

		if (v3Color == REDEFAULT)
		{
			if (!bColliding)
				v3Color = REWHITE;
			else
				v3Color = RERED;
		}
		pMeshMngr->AddCubeToQueue(
			glm::translate(m_lObject[a_nIndex]->GetCenterGlobal()) * 
			glm::scale(m_lObject[a_nIndex]->GetHalfWidthG() * 2.0f),
			v3Color,
			WIRE);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			bool bColliding = false;
			for (uint n = 0; n < m_nObjectCount; n++)
			{
				if (m_llCollidingIndices[n].size() > 0)
				{
					bColliding = true;
					break;
				}
			}

			if (v3Color == REDEFAULT)
			{
				if (!bColliding)
					v3Color = REWHITE;
				else
					v3Color = RERED;
			}
			pMeshMngr->AddCubeToQueue(
				glm::translate(m_lObject[nObject]->GetCenterGlobal()) *
				glm::scale(m_lObject[nObject]->GetHalfWidthG() * 2.0f),
				v3Color,
				WIRE);
		}
	}
}
void MyBOManager::Update(void)
{
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		m_llCollidingIndices[nObject].clear();
	}
	CheckCollisions();
}
void MyBOManager::CheckCollisions(void)
{
	for (uint nObjectA = 0; nObjectA < m_nObjectCount -1; nObjectA++)
	{
		for (uint nObjectB = nObjectA + 1; nObjectB < m_nObjectCount; nObjectB++)
		{
			if (m_lObject[nObjectA]->IsColliding(m_lObject[nObjectB]))
			{
				m_llCollidingIndices[nObjectA].push_back(nObjectB);
				m_llCollidingIndices[nObjectB].push_back(nObjectA);
			}
		}
	}
}
std::vector<int> MyBOManager::GetCollidingVector(String a_sIndex)
{
	int nIndex = GetIndex(a_sIndex);
	if (nIndex < 0)
	{
		std::vector<int> empty;
		return empty;
	}
	return GetCollidingVector(static_cast<uint>(nIndex));
}
std::vector<int> MyBOManager::GetCollidingVector(uint a_nIndex)
{
	if (a_nIndex >= m_nObjectCount)
	{
		std::vector<int> empty;
		return empty;
	}
	return m_llCollidingIndices[a_nIndex];
}
int MyBOManager::GetIndex(String a_sIndex)
{
	//Find the related index
	auto var = m_mapIndex.find(a_sIndex);
	//If not found return -1
	if (var == m_mapIndex.end())
		return -1;
	return var->second;//Get the index
}