/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __TEXTUREMANAGERSINGLETON_H_
#define __TEXTUREMANAGERSINGLETON_H_

#include "RE\materials\TextureClass.h"
#include <vector>
#include <map>

namespace ReEng
{

class ReEngDLL TextureManagerSingleton
{
	std::map<String,int> m_map;//indexer

public:
	std::vector<TextureClass*> m_lTextures; //Vector of Textures

	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	static TextureManagerSingleton* GetInstance(); //Singleton Accessor
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	static void ReleaseInstance();	//Singleton Destructor
	
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	int IdentifyTexure(String sName); //Returns the ID number of the texture, -1 if it does not exist.
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	int LoadTexture(String sName);	//Loads a texture and returns the ID of where its stored in the vector

	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	int GetTextureCount(void); //Returns the number of texures in the vector
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	GLuint ReturnGLIndex(uint a_nIndex); //Returns the OpenGL Buffer ID in the vector location of the provided Index
private:
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	static TextureManagerSingleton* m_pInstance; //Singleton
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	TextureManagerSingleton(void); //Constructor	
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	TextureManagerSingleton(const TextureManagerSingleton& other); //Copy Constructor
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	TextureManagerSingleton& operator=(const TextureManagerSingleton& other);//Copy Assignment Operator
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	~TextureManagerSingleton(void); //Destructor

	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void); //Release the fields in the class
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void); //Initialize variables
};

}
#endif __TEXTUREMANAGERSINGLETON_H_