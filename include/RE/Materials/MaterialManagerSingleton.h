/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MATERIALMANAGERSINGLETON_H_
#define __MATERIALMANAGERSINGLETON_H_

#include "RE\system\SystemSingleton.h"
#include "RE\materials\MaterialClass.h"
#include <map>


namespace ReEng
{

class ReEngDLL MaterialManagerSingleton
{
	/* 
		The material vector is public for accessing speed reasons its more secure to have it as private
		and provide the right accessors for it, but its call so often that it creates overhead the other way
	*/
	std::map<String,int> m_map; //Map of the materials
	SystemSingleton* m_pSystem; //System class Pointer
	static MaterialManagerSingleton* m_pInstance; // Singleton Pointer

public:
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	std::vector<MaterialClass*> m_lMaterial; //Materials Vector
	

	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	static MaterialManagerSingleton* GetInstance(); // Singleton Accessor
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	static void ReleaseInstance(void);	//Singleton Destructor

	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	int IdentifyMaterial(String a_sName); //Identifies the material, if found return its index -1 otherwise

	//returns the index number of the material if it created a new one, otherwise it returns the index
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	int AddMaterial(String a_sName);
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	int AddMaterial(MaterialClass a_InputMaterial);

	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	int GetMaterialCount(void); //Return the number of materials in the vector

	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void ReloadMaps(void); //Tries to load all the textures for all of the materials

	/* Gets a copy of the material specified by name */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MaterialClass GetMaterialCopy(String a_sName);

	/* Returns the memory location containing the material specified by the name */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MaterialClass* GetMaterial(String a_sName);

	/* Returns the memory location containing the material specified by the index */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MaterialClass* GetMaterial(uint a_nIndex);

private:
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	MaterialManagerSingleton(void); // Constructor
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MaterialManagerSingleton(MaterialManagerSingleton const& other); //Copy Constructor
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	MaterialManagerSingleton& operator=(MaterialManagerSingleton const& other); // Copy Assignment Operator
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	~MaterialManagerSingleton(void); // Destructor

	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void); // Release Memory
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void); // Initialize variables
};

}
#endif //_MATERIALMANAGERSINGLETON_H