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

/////////////////////////////////////////////////////////////////////
// Constructor
// @param
//    center - center of the oct tree
//    depth  - depth of tree from this oct
//    width - width of the oct
/////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////
// Copy Constructor
/////////////////////////////////////////////////////////////////////
MyOctTree::MyOctTree(MyOctTree const& other)
{
	m_pMeshMngr = other.m_pMeshMngr;
	m_parent = other.m_parent;
	for (int i = 0; i < OCT_SIZE; i++)
	{
		m_child[i] = other.m_child[i];
	}
	m_subdivisions = other.m_subdivisions;
	m_radius = other.m_radius;
	m_center = other.m_center;
	m_octMap = other.m_octMap;
	for (int i = 0; i < (OCT_MAX_DEPTH + 1); i++)
	{
		m_ancestorList[i] = other.m_ancestorList[i];
	}
	m_ancesterDepth = other.m_ancesterDepth;
	m_IdxList = other.m_IdxList;
}

/////////////////////////////////////////////////////////////////////
// Swap() - swaps class data members
/////////////////////////////////////////////////////////////////////
void MyOctTree::Swap(MyOctTree& other)
{
	std::swap(m_pMeshMngr, other.m_pMeshMngr);
	std::swap(m_parent, other.m_parent);
	for (int i = 0; i < OCT_SIZE; i++)
	{
		std::swap(m_child[i], other.m_child[i]);
	}
	std::swap(m_subdivisions, other.m_subdivisions);
	std::swap(m_radius, other.m_radius);
	std::swap(m_center, other.m_center);
	std::swap(m_octMap, other.m_octMap);
	for (int i = 0; i < (OCT_MAX_DEPTH + 1); i++)
	{
		std::swap(m_ancestorList[i], other.m_ancestorList[i]);
	}
	std::swap(m_ancesterDepth, other.m_ancesterDepth);
	std::swap(m_IdxList, other.m_IdxList);
}

/////////////////////////////////////////////////////////////////////
// Copy Assignment Operator
/////////////////////////////////////////////////////////////////////
MyOctTree& MyOctTree::operator=(MyOctTree const& other)
{
	if (this != &other)
	{
		Release(this);
		Init();
		MyOctTree temp(other);
		Swap(temp);
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////
// Init() - initialize class data members
/////////////////////////////////////////////////////////////////////
void MyOctTree::Init()
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	for (int i = 0; i < OCT_SIZE; i++)
	{
		m_child[i] = nullptr;
	}
}

/////////////////////////////////////////////////////////////////////
// Subdivide() - subdivide the octtree until at tree base
/////////////////////////////////////////////////////////////////////
void MyOctTree::Subdivide()
{
	//Check for base oct cell
	if (m_subdivisions == 0)
		return;

	//Else divide further
	for (int i = 0; i < OCT_SIZE; i++)
	{
		m_child[i] = new MyOctTree(CalcChildCenter(i),
			                     m_subdivisions - 1,
			                     m_radius);
		m_child[i]->m_parent = this;
	}
}

/////////////////////////////////////////////////////////////////////
// CalcChildCenter() - calculate the center of a child oct
//
// @param - which child it is (0 - 7)
/////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////
// DisplayBox() - display box of octant and suboctants
/////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////
// AddObject() - adds an object into the octtree
//
// @param
//    obj - object reference to add
//    tree - current tree in traversal
/////////////////////////////////////////////////////////////////////
void MyOctTree::AddObject(MyOctTree* tree, MyBOClass* obj)
{
	//If no more childern enter it here
	if (tree->m_subdivisions == 0)
	{
		tree->m_octMap[obj->GetName()] = obj;
		return;
	}

	//Get oct locations of BO box points
	int maxQ = tree->DetermineOctant(obj->GetMaxG());
	int minQ = tree->DetermineOctant(obj->GetMinG()); 

	if ( maxQ != minQ )
	{
		//Object is in more than one Oct enter into this node 
		tree->m_octMap[obj->GetName()] = obj;
		return;
	}
	else
	{
		//Contained in 1 child node, pass to child
		AddObject(tree->m_child[maxQ], obj);
		return;
	}
}

/////////////////////////////////////////////////////////////////////
// RemoveObject() - removes a BO from the tree
//
// @param
//    node - current oct to search in
//    obj - object reference to remove
// @return - whether successful
/////////////////////////////////////////////////////////////////////
bool MyOctTree::RemoveObject(MyOctTree* node, MyBOClass* obj)
{
	//BAD... brute force...
	//Check Current Oct
	t_octMapIt it = node->m_octMap.find(obj->GetName());
	if (it != node->m_octMap.end())
	{
		//printf(" %s\n", obj->GetName().c_str());
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

/////////////////////////////////////////////////////////////////////
// UpdateObject() - removes and readds an obj from the octtree
//
// @param
//    root - base of tree to update in
//    obj - object reference to update
/////////////////////////////////////////////////////////////////////
void MyOctTree::UpdateObject(MyOctTree* root, MyBOClass* obj)
{
	//Find where the obj is and destroy it.
	RemoveObject(root, obj);

	//re-add it
	//printf("ReAdding %s ", obj->GetName().c_str());
	AddObject(root, obj);
}

/////////////////////////////////////////////////////////////////////
// TraverseAux() - recursive travsal collision method
//
// @param - current oct node
/////////////////////////////////////////////////////////////////////
void MyOctTree::TraverseAux(MyOctTree* node)
{
	//Put current level into the list of ancestor objs
	m_ancesterDepth++;
	m_ancestorList[m_ancesterDepth] = node;

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
				//printf("Traversed: %s vs %s\n", itA->first.c_str(), it->first.c_str());
				//Check the collision
				if (itA->second->IsColliding(it->second))
				{
					//Record in Index Listing
					(*m_IdxList)[itA->second->GetStoredIndex()].push_back(it->second->GetStoredIndex());
					(*m_IdxList)[it->second->GetStoredIndex()].push_back(itA->second->GetStoredIndex());
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

/////////////////////////////////////////////////////////////////////
// CollisionTraverse() - check collisions of all BOs in octtree
//
// @param - ref to coliding report lost
/////////////////////////////////////////////////////////////////////
void MyOctTree::CollisionTraverse(std::vector<std::vector<int>>* idxList)
{
	m_ancesterDepth = -1;
	m_IdxList = idxList;
	TraverseAux(this);
}

/////////////////////////////////////////////////////////////////////
// DetermineOctant() - dtermines what octant a point is in
/////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////
// GetCenter() - returns the center of the octant cell
/////////////////////////////////////////////////////////////////////
vector3 MyOctTree::GetCenter()
{
	return m_center;
}

/////////////////////////////////////////////////////////////////////
// GetSize() - returns the size of the octant cell
/////////////////////////////////////////////////////////////////////
float MyOctTree::GetSize()
{
	return m_radius;
}

/////////////////////////////////////////////////////////////////////
// Release() - deallocate any memory recursively
/////////////////////////////////////////////////////////////////////
void Release(MyOctTree* node);
void MyOctTree::Release(MyOctTree* node)
{
	if (node == nullptr)
		return;
	if (node->m_subdivisions == 0)
		return;

	for (int i = 0; i < OCT_SIZE; i++)
	{
		Release(node->m_child[i]);
		delete m_child[i];
	}
}

/////////////////////////////////////////////////////////////////////
// Destructor()
/////////////////////////////////////////////////////////////////////
MyOctTree::~MyOctTree()
{
	Release(this);
}