/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __TEXTURECLASS_H_
#define __TEXTURECLASS_H_

#include "RE\system\SystemSingleton.h"
#include "RE\system\filereaderclass.h"
#include "FreeImage\FreeImage.h"

namespace ReEng
{

class ReEngDLL TextureClass
{
	GLuint m_nTextureID = 0;
	SystemSingleton* m_pSystem = nullptr;
	String m_sName = "NULL";
	String m_sFileName = "NULL";

public:
	/*
	Method: TextureClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	TextureClass(void); //Constructor
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	TextureClass(const TextureClass& other); //Copy Constructor
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	TextureClass& operator=(const TextureClass& other); //Copy Assignment Operator
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
	~TextureClass(void); //Destructor

	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void LoadTexture(String a_sFileName);
//Accessors
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	GLuint GetGLTextureID(void); //Returns the OpenGL Identifier
	//__declspec(property(get = GetGLTextureID)) GLuint GLTextureID;
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	String GetTextureName(void); //Returns the name of the texture
	//__declspec(property(get = GetTextureName)) String TextureName;
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	String GetTextureFileName(void); //Returns the filename of the texture
	//__declspec(property(get = GetTextureFileName)) String TextureFileName;

private:
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void); //Initializes the variables
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<TextureClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<TextureClass*>;

}
#endif //_TEXTURECLASS_H