/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __GROUP_H_
#define __GROUP_H_

#include "RE\Materials\MaterialManagerSingleton.h"
#include "RE\Animation\FrameClass.h"
#include "RE\Animation\AnimationClass.h"
#include "RE\Physics\BoundingObjectClass.h"
#include "RE\Mesh\MeshDrawerSingleton.h"
#include "RE\mesh\AxisClass.h"

namespace ReEng
{

class ReEngDLL GroupClass
{	
	bool m_bVisible = true;	//Visibility flag
	bool m_bVisibleBO = false;	//Debug flag
	bool m_bCollidable = false;	//Collision flag
	bool m_bGlobalized = false;	//Global coordinates flag
	bool m_bModified = false;	//Modified flag

	int m_nHP = 0;			//Hit Points of this group
	uint m_nShapeCount = 0;		//number of shapes in this group
	uint m_nFrameCount = 0;		//Frames in this group
	
	SystemSingleton* m_pSystem = nullptr;	//System pointer
	MaterialManagerSingleton* m_pMatMngr = nullptr;//Material Manager Pointer
	MeshDrawerSingleton* m_pMeshDrawer = nullptr;//Mesh Manager Pointer
	GroupClass* m_pParent = nullptr;	//Parent group pointer
	FrameClass* m_pFrame = nullptr;	//List of frames of animation in the group
	BoundingObjectClass* m_pBO = nullptr;	//Bounding Object of the group
	AxisClass* m_pAxis = nullptr;		//Axis of the group
	
	String m_sName = "NULL";			//Name of the group
	String m_sParent = "NULL";		//Name of the parent of the group

	vector3 m_v3Pivot;		//Point in which the point is going to rotate around
	matrix4 m_m4ToWorld;	//Model to world matrix

	std::vector<MeshClass*> m_lMeshList;//List of shapes that compose the group
	std::vector<int> m_lMesh; //List of Meshes that compose a group
	std::vector<int> m_lMeshM; //List of Meshes that compose a group when modified
	matrix4 m_m4Mesh; //List of matrices for all Meshes that compose a group

public:
	/*
	Method: GroupClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	GroupClass(void);
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	GroupClass(const GroupClass& other);
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	GroupClass& operator=(const GroupClass& other);
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	~GroupClass(void);
	
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void Swap(GroupClass& other);

	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetShapeCount(void); //Returns the number of shapes in the vector of shapes
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	String GetName(void); //Return the name of the group
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	void SetName(String a_sName);
	//__declspec(property(get = GetName, put = SetName)) String Name; //Name Property

	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	MeshClass* GetMesh(uint a_nIndex);//Returns the shape in the given index

	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void RemoveEmptyMeshes(void);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void AddShape(String a_sName);

	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void CompileOpenGL3X(void);

	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	int IdentifyShapeByMaterial(String a_sName);

	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	bool CloneFromGroup(const GroupClass& other);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void ReleaseOpenGL(); //DeleteOpenGL

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void CompleteMissingShapeInfo(bool a_bAverageNormals = false);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SwapMaterial(String a_sOldMaterialName, String a_sNewMaterialName);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName, vector3 a_v3Tint = REDEFAULT);
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetShaderProgram(String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetMaterial(String a_sMaterialName);

	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	vector3 GetPivot(void);
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetPivot(vector3 a_v3Pivot);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetParent(GroupClass* a_pParent);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetHP(int a_nHP);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetHP(void);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetCollidable(bool a_bCollidable);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	bool GetCollidable(void);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetVisible(bool a_bVisible);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	bool GetVisible(void);

	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	String GetParentName(void);
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetParentName(String a_sParent);

	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	FrameClass GetFrame(uint nFrame);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetGlobalized(bool a_bGlobalized);

	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetFrameCount(void);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void GenerateFrames(int a_nFrames);

	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void ReleaseFrames(void);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetFrame(int a_nFrame, vector3 a_v3Translation, vector3 a_v3Rotation, vector3 a_v3Scale, bool a_bVisible, bool a_bKeyframe);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetPosX(float a_fValue, int a_nFrame);
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetPosY(float a_fValue, int a_nFrame);
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetPosZ(float a_fValue, int a_nFrame);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetAngX(float a_fValue, int a_nFrame);
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetAngY(float a_fValue, int a_nFrame);
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetAngZ(float a_fValue, int a_nFrame);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetSizeX(float a_fValue, int a_nFrame);
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetSizeY(float a_fValue, int a_nFrame);
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetSizeZ(float a_fValue, int a_nFrame);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetVisible(bool a_bValue, int a_nFrame);
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetKeyframe(bool a_bValue, int a_nFrame);
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetVisibleBO(bool a_bVisibleBO);
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetVisibleAxis(bool a_bVisible);

	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void ComputeMatrix(void);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void Interpolate(int a_nFrames);

	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	matrix4& GetModelMatrix(void);

	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	matrix4 TraverseHierarchy(GroupClass* a_Group, int a_nFrame = 0);

	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	std::vector<vector3> GetVertexList(int a_nShape = -1);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void Update(uint a_nFrame, matrix4 a_mToWorld);

	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	BoundingObjectClass* GetBoundingObject(void);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void CompileBoundingObject(void);
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetBoundingObject(BoundingObjectClass* a_pBO);

	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	bool IsColliding(vector3 a_v3RayOrigin, vector3 a_v3RayDirection, float& a_fDistance);

	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void DisconectAnimationFrames(void);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetModelMatrix(matrix4 a_nMatrix);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void AddToRenderList(uint a_nFrame = 0);//Add all shapes to the render list
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void AddBOToRenderList(bool a_bForce = false);//Render all debug
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void AddAxisToRenderList(bool a_bForce = false);//Render all debug

private:
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<GroupClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<GroupClass*>;

}
#endif //__GROUP_H__