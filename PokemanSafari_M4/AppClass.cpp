/////////////////////////////////////////////////////////////////////
// File: AppClass.cpp
// DSA2 PokemanSafari_M4
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////
#include "AppClass.h"

void AppClass::ThrowPokecube()
{
	//Check if already in the air
	if (p_pokecube_01->IsAlive())
		return;

	p_pokecube_01->SetAlive(true);
	matrix4 camView = glm::transpose(m_pCameraMngr->GetViewMatrix(-1));
	vector3 pos = m_pCameraMngr->GetPosition(-1);
	pos[1] -= 0.5f; //don't go 'through' the camera
	p_pokecube_01->SetPosition(pos);
	//Set the velocity in cam z direction
	vector3 dir = -1.0f * vector3(camView[2][0], camView[2][1], camView[2][2]);
	//TODO put this inside Projectile?
	float velocityFactor = 0.5f;
	p_pokecube_01->SetVelocity(vector3(dir[0] * velocityFactor,
		                               dir[1] * velocityFactor, 
									   dir[2] * velocityFactor));
}

//TODO DELETE
//void AppClass::UpdatePlayerCamera()
//{
//	//setting the camera's position to the players location
//	c_player->Update();
//
//	if (camSelect)
//	{
//		//Using Rail Camera
//
//		matrix4 camView = glm::transpose(m_pCameraMngr->GetViewMatrix(-1));
//		vector3 playerLoc = c_player->GetPosition();
//
//
//		vector3 playerTarget = m_v3PosPika;
//
//
//		vector3 playerUp = vector3(camView[1][0], camView[1][1], camView[1][2]);
//
//
//		return;
//	}
//	//Else free camera
//
//}

void AppClass::ToggleCamera()
{
	if (!camSelect)
	{
		m_pCameraMngr->SetActiveCamera(railCamIndex);

		camSelect = true;
	}
	else
	{
		camSelect = false;
		m_pCameraMngr->SetActiveCamera(0);
	}
}

void AppClass::ToggleGeometry()
{
	displayGeometry = !displayGeometry;
	m_pEntityMngr->SetRenderGeometry(displayGeometry);
}

void AppClass::ToggleEnvTrack()
{
	displayTracking = !displayTracking;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();
	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	//lighting
	m_pLightMngr->SetPosition(vector3(0.0f, 150.0f, 0.0f));
	m_pLightMngr->SetIntensity(8000.0f);

	

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();


	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3PosEnv), "Environment");

	c_player->Update();

	m_pEntityMngr->Update();
	m_pEntityMngr->processCollisions("Pokecube");

	//envPosEntity->SetPosition(lookDir);
	if (displayTracking)
	{
		matrix4 camView = glm::transpose(m_pCameraMngr->GetViewMatrix(-1));
		vector3 pos = m_pCameraMngr->GetPosition(-1);
		//pos[1] -= 0.5f; //don't go 'through' the camera
		//Set the velocity in cam z direction
		vector3 dir = -1.0f * vector3(camView[2][0], camView[2][1], camView[2][2]);
		vector3 tar = pos + dir*2.0f;
		envPosEntity->SetPosition(tar);
		printf("ETarget [%f,%f,%f]\n", tar[0], tar[1], tar[2]);
	}
	else
	{
		envPosEntity->SetPosition(vector3(0.0f, -40.0f, 0.0f));
	}

	if (displayGeometry)
	    m_pBOMngr->DisplayOctTree();
	//TODO whether displaying BO

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("Environment");


	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Display Scoring
	m_pScoreMngr->Update();

	//m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
	m_pMeshMngr->Print("YRotation:");
	m_pMeshMngr->Print(std::to_string(YRotation), RERED);
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	//default: //Perspective
	//	m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
	//	break;
	//case CAMERAMODE::CAMROTHOX:
	//	m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
	//	break;
	//case CAMERAMODE::CAMROTHOY:
	//	m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
	//	break;
	//case CAMERAMODE::CAMROTHOZ:
	//	m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
	//	break;
	}
	
	m_pMeshMngr->Render(); //renders the render list
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
	m_pCameraMngr->ReleaseInstance();
}

