/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __SystemSingleton_H_
#define __SystemSingleton_H_

#include "RE\System\FolderSingleton.h"

namespace ReEng
{

//System Class
class ReEngDLL SystemSingleton
{
	bool m_bWindowFullscreen = false; // Window Fullscreen
	bool m_bWindowBorderless = false; // Window Borderless
	bool m_bMultithreaded = false; // Experimental: mutithreaded system
	bool m_bConsoleWindow = false; // Experimental: Console window init

	int m_nWindowWidth = 1280; // Window width
	int m_nWindowHeight = 720; // Window height
	int m_nWindowX = 0; // Window Position X
	int m_nWindowY = 0; // Window Position Y

	int m_nFPS = 60; //Frames per Second
	int m_nFrameCount = 0; //Frames Passed

	static SystemSingleton* m_pInstance; // Singleton

	String m_sWindowName = "ReEng"; // Window Name
	String m_sAppName = "Application";//Name of the Application

	DWORD m_dTimerStart = 0; //Start time of the program
	DWORD m_dStartingTime = 0; //Start time of the program
	DWORD m_dLastFPS = 0; //Last time the time was called

	std::vector<DWORD> m_lClock;//clocks list
	
public:
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	static SystemSingleton* GetInstance(); // Singleton accessor
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	static void ReleaseInstance(void); //Singleton Release

	// Application Name Property
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetAppName(void);
	//__declspec(property(get = GetAppName)) String ApplicationName;

	// Window Borderless Property
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetWindowBorderless(bool a_bBorderless = true);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	bool IsWindowBorderless(void);
	//__declspec(property(get = IsWindowBorderless, put = SetWindowBorderless)) bool WindowBorderless;

	// Window Fullscreen Property
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetWindowFullscreen(bool a_bFullscreen = true);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	bool IsWindowFullscreen(void);
	//__declspec(property(get = IsWindowFullscreen, put = SetWindowFullscreen)) bool WindowFullscreen;
	
	// Window Width Property
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetWindowWidth(int a_nWidth);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	int GetWindowWidth(void);
	//__declspec(property(get = GetWindowWidth, put = SetWindowWidth)) int WindowWidth;

	// Window Height Property
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetWindowHeight(int a_nHeight);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	int GetWindowHeight(void);
	//__declspec(property(get = GetWindowHeight, put = SetWindowHeight)) int WindowHeight;

	// WindowX Property
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetWindowX(int a_nX);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	int GetWindowX(void);
	//__declspec(property(get = GetWindowX, put = SetWindowX)) int WindowX;

	// WindowY Property
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetWindowY(int a_nY);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	int GetWindowY(void);
	//__declspec(property(get = GetWindowY, put = SetWindowY)) int WindowY;
	
	// Window Name Property
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	void SetWindowName(String a_sWindowName);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String GetWindowName(void);
	//__declspec(property(get = GetWindowName, put = SetWindowName)) String WindowName;

	// Window Name Property
	/* Sets the system to be multi-threaded <<<EXPERIMENTAL>>>*/
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetThreaded(bool a_bMultithreaded);
	/* Asks the system if its multi-threaded*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	bool GetThreaded(void);
	//__declspec(property(get = GetThreaded, put = SetThreaded)) bool Multithreaded;


	// Asks for the value of m_bConsole
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	bool GetUsingConsole(void);

	// Asks for the value of m_bConsole
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetUsingConsole(bool a_bUsing);

	/*
	float GetWindowRatio(void);
		This will return the proportions of the window size in the system, from bottom to top of the window the value is 1,
		from left to right the value is the output of this function.
	*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	float GetWindowRatio(void);

	// WindowX Property
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	int GetFPS(void);
	//__declspec(property(get = GetFPS)) int FPS;

	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void UpdateTime(void);//Updates the current time
	//float LapClock(void);//Checks the time difference between startclock and current call
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void StartClock(unsigned int a_nClock = 0);//Starts a time count for the specified clock
	/*
	Method: LapClock
	Usage: Gets the time difference between the last time this method was called for this particular clock
	Arguments:
	Output:
	*/
	double LapClock(unsigned int a_nClock = 0);

	/*
	Method: AddClock
	Usage: Adds a clock to the list and return said clock's index
	Arguments: ---
	Output: uint -> index of the new clock;
	*/
	uint AddClock(void);


	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	bool CountDown(float a_fTime, bool a_bRepeat = false);//counts down on the specified clock, returns true when the count is up

	FolderSingleton* m_pFolder;
	REOptions m_RenderingContext;

private:
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	SystemSingleton(void); // Constructor
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	SystemSingleton(SystemSingleton const& other); //Copy Constructor
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	SystemSingleton& operator=(SystemSingleton const& other); // Copy Assignment Operator
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	~SystemSingleton(void); // Destructor

	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void); // Release Memory
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void); // Initialize variables
};

}
#include "RE\System\GLSystemSingleton.h"

#endif //__SystemSingleton_H__