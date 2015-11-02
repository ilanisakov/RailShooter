/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingBoxClass.h"

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class AppClass : public ReEngAppClass
{
	MyBoundingBoxClass* m_pBB1 = nullptr;
	MyBoundingBoxClass* m_pBB2 = nullptr;

	vector3 m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	vector3 m_v3O2 = vector3( 2.5f, 0.0f, 0.0f);
public:
	typedef ReEngAppClass super;

	/* Constructor */
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bUsingConsole = false) : super(hInstance, lpCmdLine, nCmdShow, a_bUsingConsole) {}

	/*
	ReadConfig
	Reads the configuration of the application to a file
	*/
	virtual void ReadConfig(void) final {}

	/*
	WriteConfig
	Writes the configuration of the application to a file
	*/
	virtual void WriteConfig(void) final {}

	/*
	InitWindow
	Initialize ReEng variables necessary to create the window
	*/
	virtual void InitWindow(String a_sWindowName) final;

	/*
	InitVariables
	Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	*/
	virtual void InitVariables(void) final;

	/*
	Update
	Updates the scene
	*/
	virtual void Update(void) final;

	/*
	Display
	Displays the scene
	*/
	virtual void Display(void) final;

	/*
	ProcessKeyboard
	Manage the response of key presses
	*/
	virtual void ProcessKeyboard(void) final;

	/*
	ProcessMouse
	Manage the response of key presses and mouse position
	*/
	virtual void ProcessMouse(void) final;

	/*
	Release
	Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	*/
	virtual void Release(void) final;
};

#endif //__APPLICATION_H_
