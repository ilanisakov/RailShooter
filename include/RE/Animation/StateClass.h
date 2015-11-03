/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __STATECLASS_H_
#define __STATECLASS_H_

#include "RE\system\SystemSingleton.h"
#include <vector>

namespace ReEng
{

class ReEngDLL StateClass
{
	
	bool m_bTransitionState = false;//Is this a transition state
	bool m_bRepeatSequence	= true;	//Does the sequence repeats
	bool m_bBreakableState = true;	//Can I break out of this state without finishing the animation?
	int m_nSequence = 0;			//Sequence being played
	int m_nExitCount = 0;				//Number of exits of this state
	
	std::vector<StateClass*> m_lExit;//Exits of the state

	String m_sName;
public:
	/*
	Method: Stateclass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	StateClass();	//Constructor
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	StateClass(String a_sName, int a_nSequence = 0, bool a_bBreakableState = false, bool a_bTransitionState = false, bool a_bRepeatSequence = false);
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	StateClass(const StateClass& other);
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	StateClass& operator=(const StateClass& other);
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	~StateClass();	//Destructor

	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	void Init();		//Initialices variable values
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	void Release();		//Releases the memory and deallocate space.

	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	void SetName(String a_sName);
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	String GetName(void);
	//__declspec(property(put = SetName, get = GetName)) String Name;

	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	void SetSequence(int a_nSequence);
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	int GetSequence(void);
	//__declspec(property(put = SetSequence, get = GetSequence)) int Sequence;

	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetBreakable(bool a_bRepeatSequence);
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	bool GetBreakable(void);

	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	void SetRepeatSequence(bool a_bRepeatSequence);
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	bool GetRepeatSequence(void);
	//__declspec(property(put = SetRepeatSequence, get = GetRepeatSequence)) bool RepeatSequence;

	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	int GetNumberOfExits(void);
	//__declspec(property(get = GetNumberOfExists)) int Exits;

	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	int AddExit(StateClass* a_pState);

	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	int GetExitIndex(StateClass* a_pState);

	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	bool IsTransitionState(void);

	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	StateClass* GetAutoExit(void);

	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	StateClass* GetExit(int a_nIndex);

private:
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	void Swap(StateClass& other);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<StateClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<StateClass*>;

}

#endif //__STATECLASS_H__