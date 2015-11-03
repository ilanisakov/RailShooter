/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MATERIALCLASS_H_
#define __MATERIALCLASS_H_

#include "RE\system\SystemSingleton.h"
#include "RE\materials\TextureManagerSingleton.h"

namespace ReEng
{

class ReEngDLL MaterialClass
{
	SystemSingleton* m_pSystem = nullptr;
	TextureManagerSingleton* m_pTextureMngr = nullptr;

	GLuint m_nMapDiffuse = 0;
	GLuint m_nMapNormal = 0;
	GLuint m_nMapSpecular = 0;

	vector3 m_vKd;

	String m_sName = "NULL";
	String m_sMapDiffuse = "NULL";
	String m_sMapNormal = "NULL";
	String m_sMapSpecular = "NULL";
	
public:
	/*
	Method: MaterialClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	MaterialClass(String a_sName);
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MaterialClass(const MaterialClass& other);
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MaterialClass& operator=(const MaterialClass& other);
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	~MaterialClass(void);
	
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void);

	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetName(String a_sName);
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	String	GetName(void);
	//__declspec(property(put = SetName, get = GetName)) String Name;

	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetDiffuseMapName(String a_sFileName);
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	String	GetDiffuseMapName(void);
	//__declspec(property(put = SetDiffuseMapName, get = GetDiffuseMapName)) String DiffuseMapName;

	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetNormalMapName(String a_sFileName);
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	String	GetNormalMapName(void);
	//__declspec(property(put = SetNormalMapName, get = GetNormalMapName)) String NormalMapName;

	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetSpecularMapName(String a_sFileName);
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	String	GetSpecularMapName(void);
	//__declspec(property(put = SetSpecularMapName, get = GetSpecularMapName)) String SpecularMapName;

	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	GLuint	GetDiffuseMap(void);
	//__declspec(property(get = GetDiffuseMap)) GLuint DiffuseMap;

	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	GLuint	GetNormalMap(void);
	//__declspec(property(get = GetNormalMap)) GLuint NormalMap;

	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	GLuint	GetSpecularMap(void);
	//__declspec(property(get = GetSpecularMap)) GLuint SpecularMap;

	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetDiffuse(vector3 a_Kd);
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	vector3	GetDiffuse(void);
	//__declspec(property(put = SetDiffuse, get = GetDiffuse)) vector3 Kd;

	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	REERRORS LoadDiffuse(String a_sFileName);

	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	REERRORS LoadNormal(String a_sFileName);

	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	REERRORS LoadSpecular(String a_sFilename);

	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	REERRORS LoadMaps(void);
private:
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};

}
#endif //_EMPTY_H