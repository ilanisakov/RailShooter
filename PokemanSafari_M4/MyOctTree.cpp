/////////////////////////////////////////////////////////////////////
// File: MyOctTree.cpp
// DSA2 PokemanSafari_M4
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////

#include "MyOctTree.h"

MyOctTree::MyOctTree(vector3 center, int depth, float width)
{
	m_center = center;
	m_subdivisions = depth;
	m_radius = width / 2.0f;
	
	//Initialize the children
	Init();

	//Perform subdivisions for children
	Subdivide();
}

MyOctTree::MyOctTree(MyOctTree const& other)
{
	//TODO
}

MyOctTree& MyOctTree::operator=(MyOctTree const& other)
{
	//TODO
	return *this;

}

void MyOctTree::Init()
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	for (int i = 0; i < OCT_SIZE; i++)
	{
		m_child[i] = nullptr;
	}
}

void MyOctTree::Subdivide()
{
	//Check for base oct cell
	if (m_subdivisions == 0)
		return;

	//Else divide
	for (int i = 0; i < OCT_SIZE; i++)
	{
		m_child[i] = new MyOctTree(CalcChildCenter(i),
			                     m_subdivisions - 1,
			                     m_radius);
		m_child[i]->m_parent = this;
	}
}

vector3 MyOctTree::CalcChildCenter(int idx)
{
	float radius = m_radius / 2.0f;
	switch (idx)
	{
	case 0: 
		return vector3(m_center[0] + radius,
			           m_center[1] + radius,
			           m_center[2] + radius);
	case 1:
		return vector3(m_center[0] + radius,
			           m_center[1] + radius,
					   m_center[2] - radius);
	case 2:
		return vector3(m_center[0] + radius,
			           m_center[1] - radius,
			           m_center[2] + radius);
	case 3:
		return vector3(m_center[0] + radius,
			           m_center[1] - radius,
			           m_center[2] - radius);
	case 4:
		return vector3(m_center[0] - radius,
			           m_center[1] + radius,
			           m_center[2] + radius);
	case 5: 
		return vector3(m_center[0] - radius,
			           m_center[1] + radius,
			           m_center[2] - radius);
	case 6:
		return vector3(m_center[0] - radius,
			           m_center[1] - radius,
			           m_center[2] + radius);
	case 7:
		return vector3(m_center[0] - radius,
			           m_center[1] - radius,
			           m_center[2] - radius);
	default: //UNDEFINED
		return m_center;
	}
}

void MyOctTree::DisplayBox()
{
	if (m_subdivisions != 0)
	{
		//only draw the lowest childrens boxes
		for (int i = 0; i < OCT_SIZE; i++)
		{
			m_child[i]->DisplayBox();
		}
		return;
	}

	//lowest - draw the box
	m_pMeshMngr->AddCubeToQueue(
		glm::translate(IDENTITY_M4, m_center) *
		glm::scale(vector3(m_radius)*2.0f),
		REYELLOW,
		WIRE); 
	
}

void MyOctTree::AddObject(MyOctTree* tree, MyBOClass* obj)
{
	//printf("%d", tree->m_subdivisions);
	//If no more childern enter it here
	if (tree->m_subdivisions == 0)
	{
//		printf("\n");
		tree->m_octMap[obj->GetName()] = obj;
		return;
	}

	//Get oct locations of BO box points
	int maxQ = tree->DetermineOctant(obj->GetMaxG());
	int minQ = tree->DetermineOctant(obj->GetMinG()); 

	if ( maxQ != minQ )
	{
		//Object is in more than one Oct enter into this node 
//		printf("\n");
		tree->m_octMap[obj->GetName()] = obj;
		return;
	}
	else
	{
		//Contained in 1 child node, pass to child
//		printf("%d,", maxQ);
		AddObject(tree->m_child[maxQ], obj);
		return;
	}
}

bool MyOctTree::RemoveObject(MyOctTree* node, MyBOClass* obj)
{
	//BAD... brute force...
	//Check Current Oct
	t_octMapIt it = node->m_octMap.find(obj->GetName());
	if (it != node->m_octMap.end())
	{
//		printf(" %s\n", obj->GetName().c_str());
		node->m_octMap.erase(it);
		return true;
	}
	else if(node->m_subdivisions != 0) //check children...
	{
		for (int i = 0; i < OCT_SIZE; i++)
		{
			if (node->RemoveObject(m_child[i], obj))
				return true;
		}
	}
	return false; //Never found it
}

void MyOctTree::UpdateObject(MyOctTree* root, MyBOClass* obj)
{
	//Find where the obj is and destroy it.
//	printf("Removing");
	RemoveObject(root, obj);

	//re-add it
//	printf("ReAdding %s ", obj->GetName().c_str());
	AddObject(root, obj);
}

void MyOctTree::TraverseAux(MyOctTree* node)
{
	//Put current level into the list of ancestor objs
	m_ancesterDepth++;
	m_ancestorList[m_ancesterDepth] = node;

	MyBOClass* pBOanc; //ancestor
	MyBOClass* pBOcur; //current level
	//Check CurrentLvL with all Ancestors (itself is now included)
	for (int d = 0; d <= m_ancesterDepth; d++)
	{
		//For All Ancestor's Objs
		for (t_octMapIt itA = m_ancestorList[d]->m_octMap.begin();
			itA != m_ancestorList[d]->m_octMap.end(); itA++)
		{ 
			//FOr My Objs
			for (t_octMapIt it = node->m_octMap.begin();
				it != node->m_octMap.end(); it++)
			{
				if (itA->second == it->second)
				{
					break; //dont do double checks!
				}
//				printf("Traversed: %s vs %s\n", itA->first.c_str(), it->first.c_str());
				//Check the collision
				if (itA->second->IsColliding(it->second))
				{
					//Record in Index Listing
					(*m_IdxList)[itA->second->GetStoredIndex()].push_back(it->second->GetStoredIndex());
					(*m_IdxList)[it->second->GetStoredIndex()].push_back(itA->second->GetStoredIndex());

					//m_llCollidingIndices[nObjectA].push_back(nObjectB);
					//m_llCollidingIndices[nObjectB].push_back(nObjectA);
				}
			}
			
		}
	}

	//Do this for every child
	if (node->m_subdivisions != 0)
	{
		for (int i = 0; i < OCT_SIZE; i++)
		{
			TraverseAux(node->m_child[i]);
		}
	}
	//Decrement depth. (moving back up now)
	m_ancesterDepth--;
}

void MyOctTree::CollisionTraverse(std::vector<std::vector<int>>* idxList)
{
	m_ancesterDepth = -1;
	m_IdxList = idxList;
//	printf("Begin Traversal...\n");
	TraverseAux(this);
}

int MyOctTree::DetermineOctant(vector3 point)
{
	vector3 diff = point - m_center;
	std::vector<int> octList;
	if (diff[0] > 0.0f)         //+X
	{
		if (diff[1] > 0.0f)     //+X+Y
		{
			if (diff[2] > 0.0f) //+X+Y+Z
				return 0;         
			return 1;           //+X+Y-Z
		}
		else                    //+X-Y
		{
			if (diff[2] > 0.0f) //+X-Y+Z
				return 2;
			return 3;           //+X-Y-Z
		}
	}
	else                        //-X
	{
		if (diff[1] > 0.0f)     //-X+Y
		{
			if (diff[2] > 0.0f) //-X+Y+Z
				return 4;
			return 5;           //-X+Y-Z
		}
		else                    //-X-Y
		{
			if (diff[2] > 0.0f) //-X-Y+Z
				return 6;
			return 7;           //-X-Y-Z
		}
	}
}

vector3 MyOctTree::GetCenter()
{
	return m_center;
}

float MyOctTree::GetSize()
{
	return m_radius;
}

void MyOctTree::Release()
{
	//TODO
}

MyOctTree::~MyOctTree()
{
	Release();
}