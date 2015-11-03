/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __SEQUENCECLASS_H_
#define __SEQUENCECLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

class ReEngDLL SequenceClass
{
	bool m_bDirectAnimation = true;//Secuence going from a low to a high frame number?
	int m_nID = 0;					//Secuence Identifier
	int m_nFirstFrame = 0;			//First frame of the secuence;
	int m_nLastFrame = 0;			//Last frame of the secuence;
	int m_nFrameRate = 0;			//How many frames a secuence is playing
	int m_nFrameCount = 0;				//Number of frames in this sequence;
	String m_sName = "NULL";		//Secuence Name
	
public:
	/*
	Method: Sequenceclass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	SequenceClass();	//Constructor
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	SequenceClass(String a_sName, int a_nID, int a_nFirstFrame, int a_nLastFrame, int a_nFrameRate);
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	SequenceClass(const SequenceClass& other);
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	SequenceClass& operator=(const SequenceClass& other);;
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	~SequenceClass();	//Destructor

	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	void Init();		//Initialices variable values
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	void Release();		//Releases the memory and deallocate space.
	
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	void SetID(int a_nID);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int getID(void);
	//__declspec(property(put = SetID, get = GetID)) int ID;

	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	void SetName(String a_sName);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	String GetName(void);
	//__declspec(property(put = SetName, get = GetName)) String Name;

	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	void SetFirstFrame(int a_nFirstFrame);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetFirstFrame(void);
	//__declspec(property(put = SetFirstFrame, get = GetFirstFrame)) int FirstFrame;

	/*
	Method: 
	Usage:
	Arguments:
	Output: ---
	*/
	void SetLastFrame(int a_nLastFrame);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetLastFrame(void);
	//__declspec(property(put = SetLastFrame, get = GetLastFrame)) int LastFrame;

	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	void SetDirectAnimation(bool a_bDirectAnimation);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	bool IsDirectAnimation(void);
	//__declspec(property(put = SetDirectAnimation, get = IsDirectAnimation)) bool DirectAnimation;

	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	void setFrameRate(int a_nFrameRate);
	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetFrameRate(void);
	//__declspec(property(put = SetFrameRate, get = GetFrameRate)) int FrameRate;

	/*
	Method: 
	Usage:
	Arguments: ---
	Output:
	*/
	int GetFrameCount(void);

private:
	/*
	Method: 
	Usage:
	Arguments:
	Output:
	*/
	void Swap(SequenceClass& other);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<SequenceClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<SequenceClass*>;

}
#endif //__SEQUENCECLASS_H__