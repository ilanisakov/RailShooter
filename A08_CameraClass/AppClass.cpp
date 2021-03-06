#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("A08_CameraClass"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}
void AppClass::InitVariables(void)
{
	myCamera = MyCamera::GetInstance();
	
	//Load model objs
	m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper");
	m_pMeshMngr->LoadModel("Minecraft\\MC_Zombie.obj", "Zombie");
	m_pMeshMngr->LoadModel("Minecraft\\MC_Steve.obj", "Steve");
	//set model matrix
	m_pMeshMngr->SetModelMatrix(
		glm::translate(matrix4(IDENTITY), vector3(0.0f, 0.0f, 10.0f)),
		"Steve");
	m_pMeshMngr->SetModelMatrix(
		glm::translate(matrix4(IDENTITY), vector3(2.0f, 0.0f, 0.0f)),
		"Creeper");
	m_pMeshMngr->SetModelMatrix(
		glm::translate(matrix4(IDENTITY), vector3(-2.0f, 0.0f, 0.0f)),
		"Zombie");

}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	m_pCamera->SetProjection(myCamera->GetProjection(false));
	m_pCamera->SetView(myCamera->GetView());




	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	m_pGrid->Render(); //renders the XY grid with a 100% scale

	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	myCamera->ReleaseInst();

	super::Release(); //release the memory of the inherited fields
}
