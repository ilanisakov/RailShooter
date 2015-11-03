/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __FOLDERSINGLETON_H_
#define __FOLDERSINGLETON_H_

#include <string>
#include <Windows.h>

#include "RE\system\REDefinitions.h" //ReEng basic Definitions

namespace ReEng
{

typedef std::string String;
class ReEngDLL FolderSingleton
{
	String m_sRoot = "";
	String m_sData = "";
	String m_s3DS = "";
	String m_sBTO = "";
	String m_sPOM = "";
	String m_sFBX = "";
	String m_sOBJ = "";
	String m_sLVL = "";
	String m_sTextures = "";
	String m_sShaders = "";
	String m_sAddOn = "";

	static FolderSingleton* m_pInstance;
public:
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	static FolderSingleton* GetInstance(void);
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	static void ReleaseInstance();	//Singleton Destructor
	
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetFolderRoot(String a_sInput);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetFolderRoot(void);
	//__declspec(property(put = SetFolderRoot, get = GetFolderRoot)) String Root;

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetFolderData(String a_sInput);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetFolderData(void);
	//__declspec(property(put = SetFolderData, get = GetFolderData)) String Data;

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetFolderM3DS(String a_sInput);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetFolderM3DS(void);
	//__declspec(property(put = SetFolderM3DS, get = GetFolderM3DS)) String M3DS;

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetFolderMBTO(String a_sInput);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetFolderMBTO(void);
	//__declspec(property(put = SetFolderMBTO, get = GetFolderMBTO)) String MBTO;

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetFolderMPOM(String a_sInput);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetFolderMPOM(void);
	//__declspec(property(put = SetFolderMPOM, get = GetFolderMPOM)) String MPOM;

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetFolderMFBX(String a_sInput);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetFolderMFBX(void);
	//__declspec(property(put = SetFolderMFBX, get = GetFolderMFBX)) String MFBX;

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetFolderMOBJ(String a_sInput);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetFolderMOBJ(void);
	//__declspec(property(put = SetFolderMOBJ, get = GetFolderMOBJ)) String MOBJ;

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetFolderLVL(String a_sInput);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetFolderLVL(void);
	//__declspec(property(put = SetFolderLVL, get = GetFolderLVL)) String LVL;

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetFolderTextures(String a_sInput);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetFolderTextures(void);
	//__declspec(property(put = SetFolderTextures, get = GetFolderTextures)) String Textures;

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetFolderShaders(String a_sInput);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetFolderShaders(void);
	//__declspec(property(put = SetFolderShaders, get = GetFolderShaders)) String Shaders;

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetFolderAddOn(String a_sInput);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetFolderAddOn(void);
	//__declspec(property(put = SetFolderAddOn, get = GetFolderAddOn)) String AddOn;

private:
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	FolderSingleton(void);
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	FolderSingleton(const FolderSingleton& other);
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	FolderSingleton& operator=(const FolderSingleton& other);
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	~FolderSingleton(void);

	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void);
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void);

	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetRealProgramPath(void);
};

}

#endif //__FOLDERSINGLETON_H_
