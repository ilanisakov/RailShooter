#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("PokemanSafari"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	m_pScoreMngr = ScoreManager::GetInstance();
	m_pBOMngr = MyBOManager::GetInstance();

	m_pCameraMngr->SetFPS(true);

	m_pLightMngr->AddLight(vector3(5.5f,10.0f,10.0f));

	//Fill Paths
	FillPath();

	//Initialize positions
	m_v3PosPokeCube = vector3(-2.5f, 0.0f, 0.0f);
	m_v3PosEnv = vector3(0.0f, -20.0f, 0.0f);

	//Load Models
	//m_pMeshMngr->LoadModel("Minecraft\\MC_Steve.obj", "Steve");
	//m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper");
	m_pMeshMngr->LoadModel("PokemanSafari\\environment.obj", "Environment");
	m_pMeshMngr->LoadModel("PokemanSafari\\pokecube.obj", "Pokecube");

	p_pokecube_01 = new Projectile(PJ_POKECUBE, "Pokecube");
	p_pokecube_01->SetPosition(m_v3PosPokeCube);
	p_pokecube_01->SetVelocity(vector3(0.001f, 0.0f, 0.0f));
    p_pokecube_01->SetAcceleration(vector3(0.0f, -0.002f, 0.0f));
	p_pokecube_01->SetMass(1.2f);

	c_player = new Character(CT_PLAYER, "player", playerPath);

	//c_pokeman_01 = new Character(CT_POKEMAN, )
}

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

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();
	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);
	m_pLightMngr->SetPosition(vector3(0.0f, 150.0f, 0.0f));
	m_pLightMngr->SetIntensity(8000.0f);

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();

	//Set the model matrices for both objects and Bounding Spheres
	//m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Steve");
	//m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");


	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3PosEnv), "Environment");
	//m_pMeshMngr->SetModelMatrix(glm::translate(m_v3PosPokeCube), "Pokecube");

	m_pBOMngr->Update();

	p_pokecube_01->Update();

	//setting the camera's position to the players location
	m_pCameraMngr->SetPosition(c_player->GetLocation());

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("Environment");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pScoreMngr->Update();
	//m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
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

void AppClass::FillPath(void)
{
	//Player's Path
	playerPath.push_back(vector3(20, 0, 0));
	playerPath.push_back(vector3(5, 0, 0));
	playerPath.push_back(vector3(5, 5, 0));
	playerPath.push_back(vector3(0, 5, 0));
}