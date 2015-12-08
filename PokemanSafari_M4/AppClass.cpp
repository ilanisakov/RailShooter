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

/////////////////////////////////////////////////////////////////////
// ThrowPokecube() - performs the operation to throw a pokecube
//                   in game
/////////////////////////////////////////////////////////////////////
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
	float velocityFactor = 0.5f;
	p_pokecube_01->SetVelocity(vector3(dir[0] * velocityFactor,
		                               dir[1] * velocityFactor, 
									   dir[2] * velocityFactor));
}

/////////////////////////////////////////////////////////////////////
// ToggleCamera() - toggles betwen rail and free camera
/////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////
// ToggleGeometry() - toggles whether to display collision geometry
/////////////////////////////////////////////////////////////////////
void AppClass::ToggleGeometry()
{
	displayGeometry = !displayGeometry;
	m_pEntityMngr->SetRenderGeometry(displayGeometry);
}

/////////////////////////////////////////////////////////////////////
// ToggleEnvTrack() - toggles whether using position target
//                    (DEBUG USE ONLY)
/////////////////////////////////////////////////////////////////////
void AppClass::ToggleEnvTrack()
{
	displayTracking = !displayTracking;
}

/////////////////////////////////////////////////////////////////////
//Update() - Updates the scene
/////////////////////////////////////////////////////////////////////
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

	//Set Environment
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3PosEnv), "Environment");

	//Update Player Camera Entity
	c_player->Update();

	//Update All Entities
	m_pEntityMngr->Update();

	//Processess Pokecube collisions only
	m_pEntityMngr->processCollisions("Pokecube");

	//If enabled display position tracking shape/coordinates
	if (displayTracking)
	{
		//Displays cube in front of the camera
		matrix4 camView = glm::transpose(m_pCameraMngr->GetViewMatrix(-1));
		vector3 pos = m_pCameraMngr->GetPosition(-1);
		vector3 dir = -1.0f * vector3(camView[2][0], camView[2][1], camView[2][2]);
		vector3 tar = pos + dir*2.0f;
		envPosEntity->SetPosition(tar);
		//Outputs Target cube position
		printf("ETarget [%f,%f,%f]\n", tar[0], tar[1], tar[2]);
	}
	else //Hide
	{
		envPosEntity->SetPosition(vector3(0.0f, -40.0f, 0.0f));
	}

	//Whether to display OctTree Grid
	if (displayGeometry)
	    m_pBOMngr->DisplayOctTree();

	//Adds environment to render list
	m_pMeshMngr->AddInstanceToRenderList("Environment");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Display Scoring
	m_pScoreMngr->Update();

	//m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
	//m_pMeshMngr->Print("YRotation:");
	//m_pMeshMngr->Print(std::to_string(YRotation), RERED);
}

/////////////////////////////////////////////////////////////////////
//Display() - Displays the scene
/////////////////////////////////////////////////////////////////////
void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
		//Dont Render a Grid...
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

/////////////////////////////////////////////////////////////////////
//Release() - Releases the application
/////////////////////////////////////////////////////////////////////
void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
	m_pCameraMngr->ReleaseInstance();
	m_pScoreMngr->ReleaseInst();
	m_pBOMngr->ReleaseInstance();
	m_pEntityMngr->ReleaseInstance();

	if (c_player != nullptr)
	    delete c_player;

}

