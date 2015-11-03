/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __INSTANCECLASS_H_
#define __INSTANCECLASS_H_

#include "RE\Mesh\ModelClass.h"

namespace ReEng
{

class ReEngDLL InstanceClass
{
	bool m_bInstanciated = false;	//Done instanciated flag
	bool m_bVisible = true;		//visibility flag
	bool m_bVisibleAxis = false;	//Visible Axis flag
	bool m_bVisibleFrameBO = false;	//Visible Frame Bounding Object flag
	bool m_bVisibleGrandBO = false;	//Visible Grand Bounding Object flag
	bool m_bCollidable = false;		//Collisionable flag

	bool m_bFirstRun = true;
	
	int m_nGroupCount = 0;			//Number of groups
	int m_nStateLast = 0;		//Last state visited
	int m_nStateCurrent = 0;	//Current state
	int m_nStateNext = 0;		//Next state to visit
	int m_nHP = 1;				//Hit Points of the Instance
	uint m_nCurrentFrame = 0;	//Current frame to be rendered

	float m_fLastFrameDrawn = 0.0f; //Last frame rendered

	BoundingObjectClass* m_pGrandBO = nullptr;	//Bounding Object that contains all frame Bounding Objects
	BoundingObjectClass* m_pFrameBO = nullptr;	//Bounding Object of the current frame
	SystemSingleton* m_pSystem = nullptr;		//System pointer
	ModelClass* m_pModel = nullptr;				//Model from which this instance was instanciated
	AxisClass* m_pAxis = nullptr;				//Axis of the instance
	GroupClass* m_pGroup = nullptr;				//List of group pointers of the instance

	DWORD m_dLastRenderCall = 0;	//Last render call

	String m_sName = "NULL";		//Name of the instance

	matrix4 m_m4ToWorld;		//Model to world matrix

	std::map<String, int> m_map;	//For indexing the groups

	SequenceClass* m_pSequence; //Sequence played outside of state

public:
	/*
	Method: InstanceClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	InstanceClass(void);
	/* Copy Constructor */
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	InstanceClass(const InstanceClass& other);
	/* Copy Assignment Operator */
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	InstanceClass& operator=(const InstanceClass& other);
	/* Destructor */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	~InstanceClass(void);

	//Accessors
	/* Sets the Shader program */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName, vector3 a_v3Tint = REDEFAULT);
	/* Sets the shader program to a program already compiled */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetShaderProgram(String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);

	/* Sets the Model to World matrix of the instance*/
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetModelMatrix(const matrix4 a_m4ToWorld = matrix4(1.0f));
	/* Gets the model to World matrix from the instance*/
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	matrix4& GetModelMatrix(void);
	/* Property SetModelMatrix/GetModelMatrix*/
	//__declspec(property(put = SetModelMatrix, get = GetModelMatrix)) matrix4 ModelMatrix;

	/* Set the name of the instance */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetName(String a_sName);
	/* Gets the name of the specified group*/
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	String GetName(int nGroup = -1);

	/* Sets the Hit Points of the instance*/
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetHP(int a_nHP);
	/* Gets the Hit Points of the instance*/
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetHP(void);

	/* Sets the instance to be collidable */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetCollidable(bool a_bCollidable);
	/* Asks the instance if its collidable*/
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	bool GetCollidable(void);

	/* Sets the visibility flag */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetVisible(bool a_bVisible);
	/* Gets the visibility flag */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	bool GetVisible(void);

	/* Set the visibility frag for the Frame Bounding object of the instance and the groups per name*/
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetVisibleFrameBO(bool a_bVisibleBO, String sIncludeGroup = "ALL");
	/* Set the visibility frag for the Frame Bounding object of the instance and the groups per index*/
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetVisibleFrameBO(bool a_bVisibleBO, int a_nIncludeGroup = -1); //a_nIncludeGroup = -1 for all -2 for none

	/* Set the visibility frag for the Grand Bounding object of the instance */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetVisibleGrandBO(bool a_bVisibleBO);

	/* Set the visibility frag for the Axis of the instance and the groups*/
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetVisibleAxis(bool a_bVisibleAxis, bool a_bGroups = false);

	/*
		Gets the current state of the instance
	*/
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetCurrentState(void);

	/*
		Asks if the model is in the last frame for its current state;
	*/
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	bool IsInLastFrame(void);

	/*
		Plays the specified animation sequence
	*/
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void PlayAnimation(int a_nSequenceIndex = -1);

	/* Sets the next state of the instance */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetNextState(uint a_nNext);
	/* Sets the current state of the instance (it forces the switch) */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetCurrentSate(uint a_nState);

	/* Change the shader program of a group finding it by name */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetGroupShaderByName(String a_sProgramName = "Original", String a_sGroupName = "ALL", vector3 a_v3Tint = REDEFAULT);
	/* Change the shader program of a group finding it by index */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetGroupShaderByNumber(String a_sProgramName = "Original", int nGroup = -1, vector3 a_v3Tint = REDEFAULT);
	/* Change the material of a group finding it by name, the material needs to be already compiled */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetGroupMaterial(String a_sMaterialName, String a_sGroupName = "ALL");

	/* Asks the instance what is the last drawn frame */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetLastFrameDrawn(void);

	/* Asks the instance what is its the number of groups*/
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetGroupCount(void);

	/* Asks the instance what is its number of frames */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetFrameCount(void);

	/* Asks the instance for the vertices of the whole model */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	std::vector<vector3> GetVertexList(void);

	/* Asks the instance for the Model for which it was instanciated from */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	ModelClass* GetModelInstanced(void);

	/* Asks the instance for its Grand Bounding Object*/
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	BoundingObjectClass* GetGrandBoundingObject(void);

	/* Asks the instance for its Frame Bounding Object*/
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	BoundingObjectClass* GetFrameBoundingObject(void);

	/* Asks the instance for the collision list of the groups colliding with the incoming instance's groups */
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	std::vector<vector2> GetCollisionList(InstanceClass* a_pInstance);

	/* Sets the list of octants this instance is located on*/
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetOctantList(std::vector<int> a_lList);
	
	/* Creates an Instance of a previously loaded model */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void InstanceModel(ModelClass& a_Model);

	/* Updates all the internal structures of the instance*/
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Update(void);

	/* Adds all groups of the instance to the render list */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void AddToRenderList(void);

	/* Asks the instance if its already done instanciated */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	bool IsInstanced(void);

	/* Identifies a group by name, the return will be -1 if the name is not found */
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	int IdentifyGroup(String a_sName);

	/* Swap the materials of the instance */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SwapMaterials(String a_sOldMaterialName, String a_sNewMaterialName);

	/* Asks the instance if its colliding with another instance */
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	bool IsColliding(InstanceClass* a_pInstance);

	/* Asks the instance if its colliding with a ray */
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	int IsColliding(vector3 a_v3RayStart, vector3 a_vRayDirection);

	/* We need to disconect all the pointers that are shared amond the instances and the model */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void DisconectPointers(void);

private:
	/* Gets a group by name */
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	GroupClass* GetGroup(String a_sName);

	/* Initializes the variables */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void);

	/* Release the fields in the class */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void);

	/* Swaps Content with other Instance class */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void Swap(InstanceClass& other);

	/* Identifies a state by name */
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	int IdentifyState(StateClass* a_pState);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<InstanceClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<InstanceClass*>;

}

#endif //_INSTANCECLASS_H
