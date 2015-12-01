/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09
----------------------------------------------*/
/////////////////////////////////////////////////////////////////////
// File: AppClass.h
// DSA2 PokemanSafari_M2
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

#include "MyEntityManager.h"
#include "Projectile.h"
#include "Character.h"
#include "ScoreManager.h"

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class AppClass : public ReEngAppClass
{

	//window
	RECT desktop;
	int width, widthW;
	int height, heightW;
	int halfWidth;
	int halfHeight;
	int windowOffsetX, windowOffsetY;

	//camera Rotation stuff
	float XRotation, YRotation;
	float rotationSpeed = 10.0f;

	ScoreManager* m_pScoreMngr;
	MyBOManager* m_pBOMngr;
	MyEntityManager* m_pEntityMngr;
	
	Projectile* p_pokecube_01;
	Character* c_pika_01;

	vector3 m_v3PosEnv = vector3(2.5f, 0.0f, 0.0f);
	vector3 lookDir = vector3(0.0f, 0.0f, 0.0f);
	vector3 m_v3PosPokeCube = vector3( 0.0f, 0.0f, 0.0f);
	vector3 m_v3PosPika;

	//RailCamera
	Character* c_player;
	bool camSelect = false;
	int railCamIndex = 0;

	//paths
	std::vector<vector3> playerPath;
	std::vector<vector3> pikachuPath;

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

	/*
	FillPaths
	Fills the array's with their respective paths
	*/
	virtual void FillPath(void) final;

	void ThrowPokecube();

	void ToggleCamera();

	void UpdatePlayerCamera();
};

#endif //__APPLICATION_H_
