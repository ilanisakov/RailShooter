/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __SHADERCLASS_H_
#define __SHADERCLASS_H_

#include "RE\system\SystemSingleton.h"
#include "RE\system\ShaderCompiler.h"

namespace ReEng
{

class ReEngDLL ShaderClass
{
	String m_sProgramName = "NULL";
	String m_sVertexShaderName = "NULL";
	String m_sFragmentShaderName = "NULL";
	GLuint m_nProgram = 0;
public:
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	ShaderClass(void);
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	ShaderClass(const ShaderClass& other);
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	ShaderClass& operator=(const ShaderClass& other);
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	~ShaderClass(void);
	
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void Swap(ShaderClass& other);

	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	GLuint CompileShader(String a_sVertexShader, String a_sFragmentShader, String a_sName = "");

	//Attributes
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetProgramName(void);
	//__declspec(property(get = GetProgramName)) String Name;

	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetVertexShaderName(void);
	//__declspec(property(get = GetVertexShaderName)) String VertexShader;

	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetFragmentShaderName(void);
	//__declspec(property(get = GetFragmentShaderName)) String FragmentShader;

	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	int GetProgramID(void);
	//__declspec(property(get = GetProgramID)) int ProgramID;

	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void);

protected:
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void);
	
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<ShaderClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<ShaderClass*>;

}

#endif //__SHADERCLASS_H__