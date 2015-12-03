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
	//initializing window variables
	height = ReEngAppClass::m_pWindow->GetHeight();//Window Height
	width = ReEngAppClass::m_pWindow->GetWidth();//Window Width
	halfHeight = height / 2;
	halfWidth = width / 2;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	widthW = desktop.right; //Screen Width
	heightW = desktop.bottom; //Screen Height
	windowOffsetX = (widthW - width) / 2;
	windowOffsetY = (heightW - height) / 2;
	
	m_pScoreMngr = ScoreManager::GetInstance();
	m_pBOMngr = MyBOManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	m_pCameraMngr->SetFPS(true);
	//Create the rail camera
	railCamIndex = m_pCameraMngr->AddCamera(vector3(0.0f, 0.0f, 5.0f),
		                     vector3(0.0f, 0.0f, 0.0f),
		                     vector3(0.0f, 1.0f, 0.0f));


	m_pLightMngr->AddLight(vector3(5.5f,10.0f,10.0f));

	//Fill Paths
	FillPath();

	//Initialize positions
	m_v3PosPokeCube = vector3(0.0f, 0.0f, 0.0f);
	m_v3PosEnv = vector3(0.0f, -20.0f, 0.0f);
	m_v3PosPika = vector3(-20.0f, -14.0f, -7.0f);
	m_v3PosDiglett = vector3(-10, -20, -30);

	//Load Models
	m_pMeshMngr->LoadModel("PokemanSafari\\environment.obj", "Environment");
	m_pMeshMngr->LoadModel("PokemanSafari\\pokecube.obj", "Pokecube");
	m_pMeshMngr->LoadModel("PokemanSafari\\pikachu.obj", "Pikachu");
	m_pMeshMngr->LoadModel("PokemanSafari\\diglett.obj", "Diglett");
	m_pMeshMngr->LoadModel("PokemanSafari\\diglett2.obj", "Diglett2");


	m_pEntityMngr->AddEntity("Pokecube", ET_PROJ_POKECUBE);
	p_pokecube_01 = m_pEntityMngr->GetEntity("Pokecube");
	p_pokecube_01->SetPosition(m_v3PosPokeCube);
	p_pokecube_01->SetVelocity(vector3(0.002f, 0.0f, 0.0f));
    p_pokecube_01->SetAcceleration(vector3(0.0f, -0.002f, 0.0f));
	p_pokecube_01->SetMass(1.2f);
	
	//m_pEntityMngr->AddEntity("player", ET_CHAR_PLAYER, 80, playerPath);
	c_player = new MyEntityClass("player",ET_CHAR_PLAYER, 80, playerPath);
	//c_player = m_pEntityMngr->GetEntity("player");

	m_pEntityMngr->AddEntity("Pikachu", ET_CHAR_POKEMAN, 5, pikachuPath);
	m_pEntityMngr->AddEntity("Diglett", ET_CHAR_POKEMAN, 2, diglettPath);
	m_pEntityMngr->AddEntity("Diglett2", ET_CHAR_POKEMAN, 1, diglettPath2);

	c_pika_01 = m_pEntityMngr->GetEntity("Pikachu");
	c_diglett_01 = m_pEntityMngr->GetEntity("Diglett");
	c_diglett_02 = m_pEntityMngr->GetEntity("Diglett2");

	//Setting mouse to center of the screen
	sf::Mouse::setPosition(sf::Vector2i(widthW / 2, heightW / 2));
	XRotation = 0;
	YRotation = 0;

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

void AppClass::UpdatePlayerCamera()
{
	//setting the camera's position to the players location
	c_player->Update();

	if (camSelect)
	{
		//Using Rail Camera


		//lookDir = vector3(m_pCameraMngr->GetViewMatrix(-1)[0][0], m_pCameraMngr->GetViewMatrix(-1)[1][1], m_pCameraMngr->GetViewMatrix(-1)[2][2]);
		//m_pCameraMngr->SetPosition(c_player->GetLocation());


		matrix4 camView = glm::transpose(m_pCameraMngr->GetViewMatrix(-1));
		vector3 playerLoc = c_player->GetPosition();
		//vector3 camZ = vector3(camView[2][0], camView[2][1], camView[2][2]);

		//vector3 camLoc = m_pCameraMngr->GetPosition();
		//vector3 dif = playerLoc - camLoc;
		//printf("PlayerPos x[%f] y[%f] z[%f]\n",playerLoc[0],playerLoc[1],playerLoc[2]);
		//printf("CameraPos x[%f] y[%f] z[%f]\n", camLoc[0], camLoc[1], camLoc[2]);
		//printf("Diff x[%f] y[%f] z[%f]\n", dif[0], dif[1], dif[2]);

		vector3 playerTarget = m_v3PosPika;
		//vector3 playerTarget =dif + vector3(0.0f, 0.0f, -1.0f);
		//if (flip)
		//{
		//	playerTarget *= -1.0f;
		///}
		//flip = !flip;
		//m_pCameraMngr->SetPosition(playerLoc);
		//m_pCameraMngr->SetTarget(playerTarget);

		////Ilans stuff///////////////////////////////////////////////
		//int windowWidth = this->
		//////////////////////////////////////////////////////////////

		vector3 playerUp = vector3(camView[1][0], camView[1][1], camView[1][2]);
		//m_pCameraMngr->SetPositionTargetAndView(playerLoc, playerTarget, REAXISY, -1);

		//playerTarget = dif + (camZ);
		//playerTarget[1] = [1];
		//printf("PlayerTarget x[%f] y[%f] z[%f]\n", playerTarget[0], playerTarget[1], playerTarget[2]);

		//m_pCameraMngr->MoveForward(-dif[2]);
		//m_pCameraMngr->MoveSideways(dif[0]);
		//m_pCameraMngr->MoveVertical(dif[1]);
		//m_pCameraMngr->SetPosition(playerLoc,railCamIndex);
		//m_pCameraMngr->SetTarget(playerTarget, railCamIndex);
		//m_pCameraMngr->SetPositionTargetAndView(playerLoc, playerTarget, playerUp, -1);
		//m_pCameraMngr->CalculateView(railCamIndex);
		//m_pCameraMngr->CalculateProjection();
		//matrix4 temp;
		//temp = m_pCameraMngr->GetViewMatrix(-1);
		//
		//First person camera movement
		//if (m_bFPC == true)
		//	CameraRotation();
		//
		//ArcBall();

		return;
	}
	//Else free camera



	
}

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

/*	p_pokecube_01->Update();
	c_pika_01->Update();
	c_diglett_01->Update();
	c_diglett_02->Update();
*/
	c_player->Update();
	m_pEntityMngr->Update();
	m_pEntityMngr->processCollisions("Pokecube");

	
	
	//UpdatePlayerCamera();
	


	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("Environment");
	//m_pMeshMngr->AddInstanceToRenderList("Pikachu");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("x: %f            ", temp[0][0]);//print the Frames per Second
	//printf("y: %f            ", temp[1][1]);//print the Frames per Second
	//printf("z: %f            \r", temp[2][2]);//print the Frames per Second
	//Print info on the screen
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

void AppClass::FillPath(void)
{
	/////////////////////////////////////////////////////////////////
	//Player's Path
	/////////////////////////////////////////////////////////////////
	//going forward
	playerPath.push_back(vector3(-54, -12, 90));
	playerPath.push_back(vector3(-54, -12, -49));
	playerPath.push_back(vector3(-10, -12,-49));
	playerPath.push_back(vector3(-10, -12, 60));
	playerPath.push_back(vector3(45, -12, 60));
	playerPath.push_back(vector3(45, -12, -60));
	//going backwards
	playerPath.push_back(vector3(45, -12, 60));
	playerPath.push_back(vector3(-10, -12, 60));
	playerPath.push_back(vector3(-10, -12, -49));
	playerPath.push_back(vector3(-54, -12, -49));
	playerPath.push_back(vector3(-54, -12, 89));

	/////////////////////////////////////////////////////////////////
	// Basic Pikachu Path
	/////////////////////////////////////////////////////////////////
	pikachuPath.push_back(vector3(-20.0f, -14.0f, -7.0f));
	pikachuPath.push_back(vector3(-20.0f, -14.0f, 10.0f));
	pikachuPath.push_back(vector3(-35.0f, -14.0f, 10.0f));
	pikachuPath.push_back(vector3(-35.0f, -14.0f, -7.0f));

	/////////////////////////////////////////////////////////////////
	// Basic Diglett Paths
	/////////////////////////////////////////////////////////////////
	diglettPath.push_back(vector3(-52.0f, -16.0f, -40.0f));
	diglettPath.push_back(vector3(-52.0f, -20.0f, -40.0f));

	diglettPath2.push_back(vector3(-52.0f, -20.0f, 5));
	diglettPath2.push_back(vector3(-52.0f, -16.0f, 5));
}