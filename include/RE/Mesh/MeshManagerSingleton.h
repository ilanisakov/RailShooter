/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MESHMANAGERSINGLETON_H_
#define __MESHMANAGERSINGLETON_H_

#include "RE\Mesh\MeshDrawerSingleton.h"
#include "RE\Mesh\PrimitiveManagerSingleton.h"
#include "RE\Mesh\ModelManagerSingleton.h"
#include "RE\Mesh\TextSingleton.h"

namespace ReEng
{
//MeshManagerSingleton
class ReEngDLL MeshManagerSingleton
{
	static MeshManagerSingleton* m_pInstance; // Singleton pointer

	TextSingleton* m_pText; //Text Singleton

public:
	MeshDrawerSingleton* m_pMeshDrawer = nullptr;//pointer to the Mesh Drawer singleton
	PrimitiveManagerSingleton* m_pPrimitiveMngr = nullptr; //pointer to the Primitive Manager singleton
	ModelManagerSingleton* m_pModelMngr = nullptr; //pointer to the Model Manager singleton

	/* Gets/Constructs the singleton pointer */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	static MeshManagerSingleton* GetInstance();

	/* Destroys the singleton */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	static void ReleaseInstance(void);

	/* Saves the specified model file, needs to specify the file extension (ATO or BTO) */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	REERRORS SaveModel(String a_sFileName,
						String a_sInstanceName,
						bool a_bAbsoluteRoute = false);

	/* Loads the specified model file */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	REERRORS LoadModel(String a_sFileName,
							String a_sInstanceName,
							bool a_bAbsoluteRoute = false,
							matrix4 a_m4ToWorld = matrix4(1.0),
							int a_nVisibility = 1,
							int a_nCollidable = 1,
							int a_nState = 0);

	/* Loads the specified level file */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void LoadLevel(String a_sFileName);

	/* Loads an add-on file for the specified instance*/
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	REERRORS LoadAddOn(String a_sInstanceName, String a_sFileName);

	/* Sets the model matrix of an specific instance finding it by name */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld, String a_sInstance = "ALL", bool a_bUpdateOctree = false);

	/* Sets the model matrix of an specific instance finding it by index */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld, int a_nIndex, bool a_bUpdateOctree = false);

	/* Asks the manager for an specific instance's model to world matrix */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	matrix4 GetModelMatrix(String a_sInstance);

	/* Updates the model manager */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void Update(bool a_bCheckCollisions = true);

	/* Renders a line on with the specified vectors and color */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddLineToRenderList(vector3 a_v3Origin, vector3 a_v3Ending, vector3 a_v3StartColor = REDEFAULT, vector3 a_v3EndColor = REDEFAULT);

	/* Renders a mesh on the specified space */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddMeshToRenderList(MeshClass* a_pMesh, matrix4& a_m4ToWorld);

	/* Renders a mesh on the specified space */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddMeshToRenderList(int a_nIndex, matrix4& a_m4ToWorld);

	/* Render the axis on the specified position */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddAxisToQueue(matrix4 a_m4ToWorld);

	/* Renders the cube on the specified position*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddPlaneToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT);

	/* Renders the cube on the specified position*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddCubeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the cone on the specified position*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddConeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the cylinder on the specified position*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddCylinderToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the tube on the specified position*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddTubeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the torus on the specified position*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddTorusToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the sphere on the specified position*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddSphereToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the sphere on the specified position*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddGridToQueue(float a_fSize = 1.0f, int a_Axis = REAXIS::XY, vector3 a_v3Color = REDEFAULT);

	/* Renders a String in the specified color */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void Print(String a_sInput, vector3 a_v3Color = REWHITE);
	/* Renders a String Line in the specified color */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void PrintLine(String a_sInput, vector3 a_v3Color = REWHITE);

	/* Renders a char array in the specified color */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddTextToQueue(vector3 a_v3Color, const char * _Format, ...);
	/* Renders a char array in the specified color */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddTextLineToQueue(vector3 a_v3Color, const char * _Format, ...);

	/* Renders the a Camera Mesh on the specified camera's position, -1 for active camera*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddCameraToQueue(int a_nID = -1, vector3 a_v3Color = REWHITE);

	/* Renders the specified instance */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddInstanceToRenderList(String a_sInstance = "ALL");

	/* Renders the list of meshes */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Render(void);

	/* Asks the Manager for the number of models */
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	int GetModelCount(void);

	/* Asks the Manager for the number of instances */
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	int GetInstanceCount(void);

	/* Asks the name of the specified instance by its index returns empty if not found */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	String GetNameOfInstanceByIndex(int a_nIndex);

	/* Gets the Instance by an index number */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	InstanceClass* GetInstanceByIndex(int a_nIndex);

	/* Gets the Instance by a name */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	InstanceClass* GetInstanceByName(String a_sInstanceName);

	/* Asks for the Bounding Object of the specified instance by index*/
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	BoundingObjectClass* GetBoundingObject(int a_nIndex);

	/* Asks for the Bounding Object of the specified instance by name*/
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	BoundingObjectClass* GetBoundingObject(String a_sInstanceName);

	/* Asks the manager for the list of vertices of an specified instance */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	std::vector<vector3> GetVertexList(String a_sInstanceName);

	/* Asks the manager if an instance with this name has been created */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	bool IsInstanceCreated(String a_sInstanceName);

	/* Sets the visibility flag of the Bounding Object */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetVisibleBoundingObject(bool a_bVisible, String a_sInstanceName = "ALL");

	/* Sets the visibility flag of the Bounding Object */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetVisibleBoundingObject(bool a_bVisible, int a_nInstanceIndex);

	/* Returns a vector4 with the indices of the Instances and groups colliding */
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	std::vector<vector4> GetCollisionList(void);

	/* Returns the index of the specified instance name, -1 if not found */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	int IdentifyInstance(String a_sInstanceName);

	/* Sets the shader program of an specific instance by name */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetShaderProgramByName(String a_sInstanceName = "ALL", String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);

	/* Sets the shader program of an specific instance by index */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetShaderProgramByNumber(int a_nInstance = -1, int a_nGroup = -1, String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);

	/* Sets the visibility of the axis of the instance */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetVisibleAxis(bool a_bVisible, String a_sInstanceName = "ALL", bool a_bAllGroups = false);

	/* Sets the visibility of the hierarchical Bounding Object */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetVisibleBoundingObjectHierarchy(bool a_bVisible, String a_sInstanceName = "ALL");

	/* Sets the texture for the font */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetFont(String a_sTextureName);

private:
	/* Constructor */
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	MeshManagerSingleton(void);

	/* Copy Constructor */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MeshManagerSingleton(MeshManagerSingleton const& other);

	/* Copy Assignment Operator */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MeshManagerSingleton& operator=(MeshManagerSingleton const& other);

	/* Destructor */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	~MeshManagerSingleton(void);

	/* Initializes the objects fields */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void);

	/* Releases the objects memory */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void);
};

}

#endif //__MESHMANAGERSINGLETON_H_