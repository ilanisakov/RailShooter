/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __OCTREESINGLETON_H_
#define __OCTREESINGLETON_H_

#include "RE\system\SystemSingleton.h"
#include "RE\Physics\OctantClass.h"

namespace ReEng
{

//System Class
class ReEngDLL OctreeSingleton
{
	int m_nOctantCount = 0;			//Number of octants in the Tree
	int m_nMaxSubtrees = 0;		//Maximum sublevel of the tree
	int m_nMaxObjects = 0;		//Maximum number of objects per octant
	OctantClass* m_pRoot = nullptr;	//Root of the Tree
	static OctreeSingleton* m_pInstance; // Singleton pointer

public:
	/* Gets/Constructs the singleton pointer */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	static OctreeSingleton* GetInstance();
	/* Destroys the singleton */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	static void ReleaseInstance(void);

	/* Gets an octant from the tree by ID*/
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	OctantClass* GetOctant(int a_nOctantID);

	/* Generates the Tree using the provided Bounding Object List and maximum levels and objects per octant */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void GenerateOctree(std::vector<BoundingObjectClass*> a_lBoundingObject, int a_nMaxSubtrees = 4, int a_nMaxObjects = 2);
	
	/* Calculates the Octant(s) the provided Bounding object is currently located without reconstructing the tree*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void UpdatePositionInTree(BoundingObjectClass* a_pBO);

	/* Renders the Non-empty leaf octant nodes of the Octree*/
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Render(void);

private:
	/* Constructor */
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	OctreeSingleton(void);
	/* Copy Constructor */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	OctreeSingleton(OctreeSingleton const& other);
	/* Copy Assignment Operator */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	OctreeSingleton& operator=(OctreeSingleton const& other);
	/* Destructor */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	~OctreeSingleton(void);

	/* Releases the objects memory */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/* Initializates the objects fields */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void);

	/* Taverses the tree finding the octant nodes the provided Bounding Object collides with*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void TraverseUpdatePosition(OctantClass* a_pNode, BoundingObjectClass* a_pBO);

	/* Traverse the tree for rendering */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void TraverseRender(OctantClass* a_pNode);

	/* Traverses the tree filling internal information */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void TraverseInfo(OctantClass* a_pNode);

	/* Traverses finding the node that contains the specidied ID, it will store it in a_pOutput */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void TraverseGet(OctantClass* a_pNode, OctantClass*& a_pOutput, int a_nID);

	/* Generates the 8 octant nodes for the specified a_pNode with a maximum level of subdivisions and max objects per node */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void GenerateSubTree(OctantClass* a_pNode, bool a_bResetCount = false);

	/* Deletes the specidied node and subtrees */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void DeleteNode(OctantClass*& a_pNode);
};

}

#endif //__OCTREESINGLETON_H_