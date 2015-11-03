/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
	Provides a fullscreen mode and icon to 
	http://www.winprog.org/tutorial/simple_window.html 
	Adapted into a class.
Date: 2014/05
----------------------------------------------*/
#ifndef __WINDOWCLASS_H_
#define __WINDOWCLASS_H_

#include <windows.h>
#include "Resource.h"
#include "RE\system\REDefinitions.h" //ReEng basic Definitions
#include "RE\System\SystemSingleton.h"

namespace ReEng
{

class ReEngDLL WindowClass
{
	bool m_bFullscreen = false; //Run in fullscreen mode?
	bool m_bBorderless = false; //Run with borders?
	bool m_bWindowCrated = false; //Window has been created

	int m_nCommandShow = 0; //Number of arguments

	LPCWSTR m_sWindowName; //Name of the window
	HWND m_hWindowHandler; //Window handler

	HINSTANCE m_hInstance; //Window Instance
	WNDPROC m_Callback; //Associated Callback for this window

	SystemSingleton* m_pSystem; //System singleton for ReEngine
	
public:
	/*
	Constructor
	*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	WindowClass(void);
	/*
	Constructor
	*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	WindowClass(HINSTANCE a_hInstance, int a_nCmdShow, WNDPROC a_WndProc);

	/*
	void CalculateWindowSize(void);
	Gets the window size.
	*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void CalculateWindowSize(void);

	/*
	void SetWindowInstance(HINSTANCE hInstance);
		Sets the window Instance
	*/
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetWindowInstance(HINSTANCE a_hInstance);

	/*
	void SetWindowCallback(WNDPROC WndProc);
		Sets the window callback
	*/
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetWindowCallback(WNDPROC a_WndProc);

	/*
	void SetIncomingArguments(int nCmdShow);
		Sets the number of incoming arguments
	*/
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetIncomingArguments(int a_nCmdShow);

	/*
	CreateMEWindow
		Creates window with the provided arguments
	Arguments:
		LPCWSTR windowName = L"Window" -> Name of the window
		int width = 1280 -> width of the window
		int height = 720 -> height of the window
	*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	int CreateMEWindow(LPCWSTR a_windowName = L"Window", int a_nWidth = 1280, int a_nHeight = 720);

	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	int GetWidth(void);
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	int GetHeight(void);

	/*
	GetHandler
		Returns the window handler
	*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	HWND GetHandler(void);

	/*
	SetFullscreen(bool input = true)
		Sets whether or not the program will run in fullscreen
	*/
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetFullscreen(bool a_bInput = true);

	/*
	SetBorderless(bool input = true)
		Sets whether or not the window will be borderless
	*/
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetBorderless(bool a_bInput = true);

	/*
	void CreateConsoleWindow(void)
		Allocates a console window for output
	*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void CreateConsoleWindow(void);

private:
	/*
	Copy Constructor
	*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	WindowClass(const WindowClass& other);

	/*
	Copy Assignment Operator
	*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	WindowClass& operator=(const WindowClass& other);

	/*
	void Init(void);
		Initializes the member variables
	*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};

}

#endif /*__WINDOWCLASS_H__*/