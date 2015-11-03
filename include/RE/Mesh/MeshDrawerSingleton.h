/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MESHDRAWERSINGLETON_H_
#define __MESHDRAWERSINGLETON_H_

#include "RE\System\SystemSingleton.h"
#include "RE\Mesh\MeshClass.h"
#include "RE\Light\LightManagerSingleton.h"
#include "RE\Camera\CameraManagerSingleton.h"
#include <map>

namespace ReEng
{
struct ReEngDLL MeshHandler
{
	int m_nInstanceCount = 0;			//Number of instances to draw
	std::vector<matrix4> m_lToWorld;	//List that holds the matrix per object

	/*
	Method: MeshHandler
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	MeshHandler(void);
	/* Copy Constructor */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MeshHandler(MeshHandler& other);
	/* Copy Assignment operator */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MeshHandler& operator=(MeshHandler& other);
	/* Destructor */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	~MeshHandler(void);
	/* Converts the list of matrix into an array of floats */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	void GetMatrixArray(float* a_fArray);
};

//System Class
class ReEngDLL MeshDrawerSingleton
{
	int m_nMeshes; //number of elements in the list
	static MeshDrawerSingleton* m_pInstance; // Singleton pointer
	std::vector<MeshClass*> m_lMesh; //list of meshes
	std::vector<MeshHandler*> m_lMeshHandler; //list of mesh handlers
	float* m_fMatrix;	//List of matrices to render in float form;
	ShaderManagerSingleton* m_pShaderMngr = nullptr;//Shader Manager
	LightManagerSingleton* m_pLightMngr = nullptr;		//Light Manager
	MaterialManagerSingleton* m_pMatMngr = nullptr;		//Material Manager
	CameraManagerSingleton* m_pCameraMngr = nullptr;//Pointer to the singleton of CameraSingleton
	std::map<String,int> m_map; //Identifies the objects in the list.
public:

	/* Gets/Constructs the singleton pointer */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	static MeshDrawerSingleton* GetInstance();

	/* Destroys the singleton */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	static void ReleaseInstance(void);

	/* Adds a mesh to the mesh list*/
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	int AddMesh(MeshClass* a_pMesh);

	/* Gets the mesh pointer from the vector specified by name */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MeshClass* GetMesh(String a_sName);

	/* Gets the mesh pointer from the vector specified by index */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MeshClass* GetMesh(int a_nIndex);

	/* Gets the mesh index from the vector specified by name */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	int GetMeshIndex(String a_sName);

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
	void AddMeshToRenderList(int  a_nIndex, matrix4& a_m4ToWorld);

	/* Renders the list of meshes */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Render(void);

	/* Renders the shape asking for its position in the world */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	virtual void RenderMesh(MeshClass* a_pMesh, matrix4 a_mToWorld);
	
	/* Renders the shape */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	virtual void RenderMesh(MeshClass* a_pMesh, float* a_fMatrixArray, int a_nInstances);

	/* Renders the shape asking for its position in the world and a color */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	virtual void RenderMeshWire(MeshClass* a_pMesh, matrix4 a_mToWorld, vector3 a_v3Color);

	/* Renders the shape asking for its position in the world and a color */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	virtual void RenderMeshSolid(MeshClass* a_pMesh, matrix4 a_mToWorld, vector3 a_v3Color);

private:
	/* Constructor */
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	MeshDrawerSingleton(void);

	/* Copy Constructor */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MeshDrawerSingleton(MeshDrawerSingleton const& other);

	/* Copy Assignment Operator */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MeshDrawerSingleton& operator=(MeshDrawerSingleton const& other);

	/* Destructor */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	~MeshDrawerSingleton(void);

	/* Returns the index of the mesh in the list of meshes */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	int IdentifyMesh(MeshClass* a_pMesh);

	/* Initializates the objects fields */
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

	/* Resets the render list */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void ResetList(void);
};

}

#endif //__MESHRAWERSINGLETON_H_