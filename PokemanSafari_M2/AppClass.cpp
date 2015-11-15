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

	m_pCameraMngr->SetFPS(true);

	//Get BO Manager Singleton
	m_pBndObjMngr = BoundingObjectManager::GetInstance();
	m_pLightMngr->AddLight(vector3(5.5f,10.0f,10.0f));
	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(0.0f, -20.0f, 0.0f);

	//Load Models
	//m_pMeshMngr->LoadModel("Minecraft\\MC_Steve.obj", "Steve");
	//m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper");
	m_pMeshMngr->LoadModel("PokemanSafari\\environment.obj", "Environment");
	m_pMeshMngr->LoadModel("PokemanSafari\\pokecube.obj", "Pokecube");

	//m_pBndObjMngr->AddBox("Steve", m_pMeshMngr->GetVertexList("Steve"));
	//m_pBndObjMngr->AddBox("Creeper", m_pMeshMngr->GetVertexList("Creeper"));

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
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Environment");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1), "Pokecube");



	//m_pBndObjMngr->SetModelMatrix("Steve", m_pMeshMngr->GetModelMatrix("Steve"));
	//m_pBndObjMngr->SetModelMatrix("Creeper", m_pMeshMngr->GetModelMatrix("Creeper"));
	m_pBndObjMngr->SetModelMatrix("Environment", m_pMeshMngr->GetModelMatrix("Environment"));
	m_pBndObjMngr->SetModelMatrix("Pokecube", m_pMeshMngr->GetModelMatrix("Pokecube"));


	m_pBndObjMngr->CheckCollision();
	m_pBndObjMngr->UpdateRenderList("ALL");

	//m_pCameraMngr->SetPositionTargetAndView(m_pCamera->m_v3Position,m_pCamera->m_v3Target,m_pCamera->)

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
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
	BoundingObjectManager::ReleaseInst();

}