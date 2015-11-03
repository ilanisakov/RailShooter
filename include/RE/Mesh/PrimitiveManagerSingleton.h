/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __PRIMITIVEMANAGERSINGLETON_H_
#define __PRIMITIVEMANAGERSINGLETON_H_

#include "RE\Mesh\PrimitiveClass.h"
#include "RE\Mesh\PrimitiveWireClass.h"
#include "RE\Mesh\MeshDrawerSingleton.h"


namespace ReEng
{

//System Class
class ReEngDLL PrimitiveManagerSingleton
{
	static PrimitiveManagerSingleton* m_pInstance; // Singleton of the class

	MeshClass* m_pAxis = nullptr; //Axis primitive
	MeshClass* m_pGrid = nullptr; //Grid primitive
	MeshClass* m_pLine = nullptr; //Line primitive
	MeshClass* m_pPlane = nullptr; //Plane primitive
	MeshClass* m_pCube = nullptr; //Cube primitive
	MeshClass* m_pCubeWire = nullptr; //Cube Wire primitive
	MeshClass* m_pCone = nullptr; //Cone primitive
	MeshClass* m_pConeWire = nullptr; //Cone Wire primitive
	MeshClass* m_pCylinder = nullptr; //Cylinder primitive
	MeshClass* m_pCylinderWire = nullptr; //Cylinder Wire primitive
	MeshClass* m_pTube = nullptr; //Tube primitive
	MeshClass* m_pTubeWire = nullptr; //Tube Wire primitive
	MeshClass* m_pTorus = nullptr; //Torus primitive
	MeshClass* m_pTorusWire = nullptr; //Torus Wire primitive
	MeshClass* m_pSphere = nullptr;//Sphere primitive
	MeshClass* m_pSphereWire = nullptr;//Sphere Wire primitive

	MeshDrawerSingleton* m_pMeshDrawer = nullptr;

public:
	/* Gets/Constructs the singleton pointer */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	static PrimitiveManagerSingleton* GetInstance();
	/* Destroys the singleton */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	static void ReleaseInstance(void); //Singleton Release

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
	
	/* Renders the sphere on the specified position*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddLineToQueue(vector3 a_v3Start, vector3 a_v3End, vector3 a_v3StartColor = REDEFAULT, vector3 a_v3EndColor = REDEFAULT);

	/* Renders a camera shape on the specified position */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddCameraToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT);
	
private:
	/* Constructor */
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	PrimitiveManagerSingleton(void);
	/* Copy constructor */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	PrimitiveManagerSingleton(PrimitiveManagerSingleton const& other);
	/* Copy Assignment operator */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	PrimitiveManagerSingleton& operator=(PrimitiveManagerSingleton const& other);
	/* Destructor */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	~PrimitiveManagerSingleton(void);

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
};

}

#endif //__PRIMITIVEMANAGERSINGLETON_H_