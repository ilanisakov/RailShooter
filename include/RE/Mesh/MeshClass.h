/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MESHCLASS_H_
#define __MESHCLASS_H_

#include "RE\System\SystemSingleton.h"
#include "RE\System\ShaderManagerSingleton.h"
#include "RE\Materials\MaterialManagerSingleton.h"

namespace ReEng
{

//System Class
class ReEngDLL MeshClass
{
protected:

	bool m_bCopy = false;	//Checks to see if this Mesh is a copy or the original
	bool m_bWire = false;	//Checks to see if the Mesh is going to be drawn in wires
	bool m_bBinded = false; //Binded flag

	int m_nMaterial = 0; //Material index of this mesh
	int m_nVertexCount = 0; //Number of vertices in this Mesh

	GLuint m_vao = 0;			//OpenGL Vertex Array Object
	GLuint m_VertexBuffer = 0;	//OpenGL Buffer (Will hold the vertex buffer pointer)
	GLuint m_ColorBuffer = 0;	//OpenGL Buffer (Will hold the color buffer pointer)
	GLuint m_UVBuffer = 0;		//OpenGL Buffer (Will hold the UV buffer pointer)
	GLuint m_NormalBuffer = 0;	//OpenGL Buffer (will hold the Normal Buffer)
	GLuint m_TangentBuffer = 0;	//OpenGL Buffer (will hold the Tangent Buffer)
	GLuint m_BinormalBuffer = 0;//OpenGL Buffer (will hold the Binormal Buffer)

	GLuint m_nShader = 0;	//Index of the shader
	GLuint m_nShaderO = 0;	//Index of the original shader

	ShaderManagerSingleton* m_pShaderMngr = nullptr;	//Shader Manager
	MaterialManagerSingleton* m_pMatMngr = nullptr;		//Material Manager

	String m_sName = "NULL";	//Identifier of the Mesh
	vector3 m_v3Tint; //Color modifier

	std::vector<vector3> m_lVertexPos;	//List of Vertices
	std::vector<vector3> m_lVertexCol;	//List of Colors
	std::vector<vector3> m_lVertexNor;	//List of Normals
	std::vector<vector3> m_lVertexTan;	//List of Tangents
	std::vector<vector3> m_lVertexBin;	//List of Binormals
	std::vector<vector3> m_lVertexUV;		//List of UVS
	
public:
	/*
	Method: MeshClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	MeshClass(void);
	/* Copy Constructor */
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	MeshClass(MeshClass const& other);
	/* Copy Assignment Operator*/
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	MeshClass& operator=(MeshClass const& other);
	/* Destructor */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	~MeshClass(void);

	/* Swaps the contents of the object with another object's content */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void Swap(MeshClass& other);

	/* Compiles the Mesh for OpenGL 3.X use*/
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void CompileOpenGL3X(void);

	/* Asks the Mesh if it has been binded */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	bool GetBinded(void);

	/* Set the shader to the newly loaded shader */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName, vector3 a_v3Tint = REDEFAULT);

	/* Sets the shader of the Shape to a loaded shader */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetShaderProgram(String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);
	
	/* Sets the material of the shape by name */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetMaterial(String a_sMaterialName);

	/* Returns the total number of vertices in this Mesh */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetVertexCount(void);

	/* Sets the material index by index in the material manager */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetMaterialIndex(int a_nIndex);
	/* Gets the material used in the shape by index of the material manager */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetMaterialIndex(void);
	
	/* Asks the mesh for the Shader program used */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	GLuint GetShaderIndex(void);

	/* Adds a new point to the vector of vertices */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void AddVertexPosition(vector3 a_v3Input);

	/* Adds a new color to the vector of vertices */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void AddVertexColor(vector3 a_v3Input);

	/* Adds a new normal to the vector of vertices */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void AddVertexNormal(vector3 a_v3Input);

	/* Adds a new binormal to the vector of vertices */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void AddVertexBinormal(vector3 a_v3Input);

	/* Adds a new tangent to the vector of vertices */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void AddVertexTangent(vector3 a_v3Input);

	/* Adds a new uv to the vector of vertices */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void AddVertexUV(vector3 a_v3Input);

	/* Asks the shape for the list of vertices */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	std::vector<vector3> GetVertexList(void);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	void SetVertexList(std::vector<vector3> a_lVertex);

	/* Asks the shape for the list of Color vertices */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	std::vector<vector3> GetColor(void);

	/* Asks the shape for the list of UV vertices */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	std::vector<vector3> GetUVs(void);

	/* Asks the shape for the list of Normal vertices */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	std::vector<vector3> GetNormals(void);

	/* Asks the shape for the list of tangents */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	std::vector<vector3> GetTangents(void);

	/* Asks the shape for the list of bitangents */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	std::vector<vector3> GetBitangets(void);

	/* Return the tint applied to the mesh */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	vector3 GetTint(void);

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetVertexBuffer(GLuint a_nIndex);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	GLuint GetVertexBuffer(void);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	GLuint GetUVBuffer(void);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	GLuint GetColorBuffer(void);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	GLuint GetNormalBuffer(void);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	GLuint GetTangentBuffer(void);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	GLuint GetBinormalBuffer(void);

	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	bool IsWire(void);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	uint GetColorSize(void);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	vector3 GetFirstColor(void);

	/* Asks the Mesh for its name */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	String GetName(void);
	/* Sets the Mesh's name */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	virtual void SetName(String a_sName);

	/*
	Method: RenderMeshWire
	Usage:
	Arguments:
		MeshClass* a_pMesh
		matrix4 a_mViewProjection
		matrix4 a_mToWorld
		vector3 a_v3Color
	Output: ---
	*/
	virtual void RenderWire(matrix4 a_mViewProjection, matrix4 a_mToWorld, vector3 a_v3Color);
	/*
	Method: RenderMeshSolid
	Usage:
	Arguments:
		MeshClass* a_pMesh
		matrix4 a_mViewProjection
		matrix4 a_mToWorld
		vector3 a_v3Color
	Output: ---
	*/
	virtual void RenderSolid(matrix4 a_mViewProjection, matrix4 a_mToWorld, vector3 a_v3Color);

protected:
	/* Initialize the object's fields */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void);
	/* Releases the object from memory */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/* Completes the information missing to create the mesh */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void CompleteMesh(void);
	/* Disconnects OpenGL3.x from the Mesh without releasing the buffers*/
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void DisconnectOpenGL3X(void);

public:
	/* Completes the triangle information */
	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void CompleteTriangleInfo(bool a_bAverageNormals = false);

	/* Calculates the missing tangets */
	/*
	Method: 
	Usage:
	Arguments: ---
	Output: ---
	*/
	void CalculateTangents(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<MeshClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<MeshClass*>;

}

#endif //__MESHCLASS_H_