/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __SHADERMANAGERSINGLETON_H_
#define __SHADERMANAGERSINGLETON_H_

#include "RE\system\ShaderClass.h"
#include <vector>
#include <assert.h>
#include <map>
namespace ReEng
{

//System Class
class ReEngDLL ShaderManagerSingleton
{
	int m_nShaderCount = 0; //Number of shaders

	static ShaderManagerSingleton* m_pInstance; // Singleton
	
	std::vector<ShaderClass> m_vShader; //vector of shaders
	std::map<String, int> m_map;//Indexer of Shaders

public:
	/* Singleton accessor */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	static ShaderManagerSingleton* GetInstance();

	/* Singleton Release */
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	static void ReleaseInstance(void);
	
	/* Compiles a shader program and returns the OpenGL identifier */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	GLuint CompileShader(String a_sVertexShader, String a_sFragmentShader, String a_sName = "");

	/* Asks the manager for the OpenGL identifier for the specified name*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	GLuint GetShaderID(String a_sName);

	/* Asks the manager for the OpenGL identifier for the specified index*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	GLuint GetShaderID(int a_nIndex);

	/* Ask for the Index in the vector of the specified shader name*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	int IdentifyShader(String a_sName);

private:
	/* Constructor */
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	ShaderManagerSingleton(void);

	/* Copy Constructor */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	ShaderManagerSingleton(ShaderManagerSingleton const& other);

	/* Copy Assignment Operator */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	ShaderManagerSingleton& operator=(ShaderManagerSingleton const& other);

	/* Destructor */
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	~ShaderManagerSingleton(void);

	/* Release Memory */
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void);

	/* Initialize variables */
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};

}
#endif //__SHADERMANAGERSINGLETON_H_