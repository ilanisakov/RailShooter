/////////////////////////////////////////////////////////////////////
// File: AppClassStartUp.cpp
// DSA2 PokemanSafari_M4
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description: Houses App Init & Loading Functions
//
/////////////////////////////////////////////////////////////////////

#include "AppClass.h"

/////////////////////////////////////////////////////////////////////
//InitWindow()
// - Initialize ReEng variables necessary to create the window
/////////////////////////////////////////////////////////////////////
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("PokemanSafari"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

/////////////////////////////////////////////////////////////////////
//InitVariables()
// -Initializes user specific variables, this is executed right after InitApplicationVariables,
//  the purpose of this member function is to initialize member variables specific for this lesson
/////////////////////////////////////////////////////////////////////
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

	//Retrieve Singletons
	m_pScoreMngr = ScoreManager::GetInstance();
	m_pBOMngr = MyBOManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	m_pCameraMngr->SetFPS(true);
	//Create the rail camera
	railCamIndex = m_pCameraMngr->AddCamera(vector3(0.0f, 0.0f, 5.0f),
		vector3(0.0f, 0.0f, 0.0f),
		vector3(0.0f, 1.0f, 0.0f));


	m_pLightMngr->AddLight(vector3(5.5f, 10.0f, 10.0f));

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
	m_pMeshMngr->LoadModel("PokemanSafari\\pikachu2.obj", "Pikachu2");
	//m_pMeshMngr->LoadModel("PokemanSafari\\pikachu3.obj", "Pikachu3");
	m_pMeshMngr->LoadModel("PokemanSafari\\pikachu4.obj", "Pikachu4");
	m_pMeshMngr->LoadModel("PokemanSafari\\pikachu5.obj", "Pikachu5");
	m_pMeshMngr->LoadModel("PokemanSafari\\diglett.obj", "Diglett");
	m_pMeshMngr->LoadModel("PokemanSafari\\diglett2.obj", "Diglett2");
	m_pMeshMngr->LoadModel("PokemanSafari\\diglett3.obj", "Diglett3");
	m_pMeshMngr->LoadModel("PokemanSafari\\diglett4.obj", "Diglett4");
	m_pMeshMngr->LoadModel("PokemanSafari\\diglett5.obj", "Diglett5");
	m_pMeshMngr->LoadModel("PokemanSafari\\diglett6.obj", "Diglett6");
	m_pMeshMngr->LoadModel("PokemanSafari\\piplup.obj", "Piplup");
	m_pMeshMngr->LoadModel("PokemanSafari\\piplup2.obj", "Piplup2");



	//Setup PokeCube
	m_pEntityMngr->AddEntity("Pokecube", ET_PROJ_POKECUBE);
	p_pokecube_01 = m_pEntityMngr->GetEntity("Pokecube");
	p_pokecube_01->SetPosition(m_v3PosPokeCube);
	p_pokecube_01->SetVelocity(vector3(0.002f, 0.0f, 0.0f));
	p_pokecube_01->SetAcceleration(vector3(0.0f, -0.002f, 0.0f));
	p_pokecube_01->SetMass(1.2f);

	//Create Player
	c_player = new MyEntityClass("player", ET_CHAR_PLAYER, 80, playerPath);
	
	//Create Pokemans
	m_pEntityMngr->AddEntity("Pikachu", ET_CHAR_POKEMAN, 5, pikachuPath);
	m_pEntityMngr->AddEntity("Pikachu2", ET_CHAR_POKEMAN, 5, pikachuPath2);
	//m_pEntityMngr->AddEntity("Pikachu3", ET_CHAR_POKEMAN, 5, pikachuPath3);
	m_pEntityMngr->AddEntity("Pikachu4", ET_CHAR_POKEMAN, 5, pikachuPath4);
	m_pEntityMngr->AddEntity("Pikachu5", ET_CHAR_POKEMAN, 5, pikachuPath5);

	m_pEntityMngr->AddEntity("Diglett", ET_CHAR_POKEMAN, 2, diglettPath);
	m_pEntityMngr->AddEntity("Diglett2", ET_CHAR_POKEMAN, 1, diglettPath2);
	m_pEntityMngr->AddEntity("Diglett3", ET_CHAR_POKEMAN, 2, diglettPath3);
	m_pEntityMngr->AddEntity("Diglett4", ET_CHAR_POKEMAN, 2, diglettPath4);
	m_pEntityMngr->AddEntity("Diglett5", ET_CHAR_POKEMAN, 2, diglettPath5);
	m_pEntityMngr->AddEntity("Diglett6", ET_CHAR_POKEMAN, 2, diglettPath6);


	m_pEntityMngr->AddEntity("Piplup", ET_CHAR_POKEMAN, 5, piplupPath);
	m_pEntityMngr->AddEntity("Piplup2", ET_CHAR_POKEMAN, 5, piplupPath2);



	c_pika_01 = m_pEntityMngr->GetEntity("Pikachu");
	c_pika_02 = m_pEntityMngr->GetEntity("Pikachu2");
	//c_pika_03 = m_pEntityMngr->GetEntity("Pikachu3");
	c_pika_04 = m_pEntityMngr->GetEntity("Pikachu4");
	c_pika_05 = m_pEntityMngr->GetEntity("Pikachu5");

	c_diglett_01 = m_pEntityMngr->GetEntity("Diglett");
	c_diglett_02 = m_pEntityMngr->GetEntity("Diglett2");
	c_diglett_03 = m_pEntityMngr->GetEntity("Diglett3");
	c_diglett_04 = m_pEntityMngr->GetEntity("Diglett4");
	c_diglett_05 = m_pEntityMngr->GetEntity("Diglett5");
	c_diglett_06 = m_pEntityMngr->GetEntity("Diglett6");

	c_piplup_01 = m_pEntityMngr->GetEntity("Piplup");
	c_piplup_02 = m_pEntityMngr->GetEntity("Piplup2");



	//Setting mouse to center of the screen
	sf::Mouse::setPosition(sf::Vector2i(widthW / 2, heightW / 2));
	XRotation = 0;
	YRotation = 0;

	//Set to Rail Cam
	ToggleCamera();

	//Build Env Position Target Object
	std::vector<vector3> envTargetVert;
	envTargetVert.push_back(vector3(0.125f, 0.125f, 0.125f));
	envTargetVert.push_back(vector3(0.125f, 0.125f, -0.125f));
	envTargetVert.push_back(vector3(0.125f, -0.125f, 0.125f));
	envTargetVert.push_back(vector3(0.125f, -0.125f, -0.125f));
	envTargetVert.push_back(vector3(-0.125f, 0.125f, 0.125f));
	envTargetVert.push_back(vector3(-0.125f, 0.125f, -0.125f));
	envTargetVert.push_back(vector3(-0.125f, -0.125f, 0.125f));
	envTargetVert.push_back(vector3(-0.125f, -0.125f, -0.125f));
	m_pEntityMngr->AddEntity("envTarget", ET_ENVIRONMENT, envTargetVert);
	envPosEntity = m_pEntityMngr->GetEntity("envTarget");
	displayTracking = false;

	//Build Environment Collisions
	BuildEnv();

	//Initialize OctTree (Puts all entities in the tree)
	m_pBOMngr->InitOctTree(2);
}

/////////////////////////////////////////////////////////////////////
//FillPaths() - Fills entity paths
/////////////////////////////////////////////////////////////////////
void AppClass::FillPath(void)
{
	/////////////////////////////////////////////////////////////////
	//Player's Path
	/////////////////////////////////////////////////////////////////
	//going forward
	playerPath.push_back(vector3(-54, -12, 90));
	playerPath.push_back(vector3(-54, -12, -49));
	playerPath.push_back(vector3(-10, -12, -49));
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
	pikachuPath.push_back(vector3(-25.0f, -14.0f, -7.0f));
	pikachuPath.push_back(vector3(-25.0f, -14.0f, 10.0f));
	pikachuPath.push_back(vector3(-35.0f, -14.0f, 10.0f));
	pikachuPath.push_back(vector3(-35.0f, -14.0f, -7.0f));


	pikachuPath2.push_back(vector3(37.0f, -16.0f, -51.0f));
	pikachuPath2.push_back(vector3(37.0f, -16.0f, -1.0f));

	pikachuPath3.push_back(vector3(-47.0f, -10.0f, 33.0f));
	pikachuPath3.push_back(vector3(-47.0f, -10.0f, 33.0f));

	pikachuPath4.push_back(vector3(-59.0f, -15.0f, -23.5f));
	pikachuPath4.push_back(vector3(-59.0f, -15.0f, -10.5f));

	pikachuPath5.push_back(vector3(-2.0f, -13.0f, -14.0f));
	pikachuPath5.push_back(vector3(4.0f, -13.0f, -14.0f));


	/////////////////////////////////////////////////////////////////
	// Basic Diglett Paths
	/////////////////////////////////////////////////////////////////
	diglettPath.push_back(vector3(-52.0f, -16.0f, -40.0f));
	diglettPath.push_back(vector3(-52.0f, -20.0f, -40.0f));

	diglettPath2.push_back(vector3(13.0f, -15.0f, 32));
	diglettPath2.push_back(vector3(13.0f, -19.0f, 32));

	diglettPath3.push_back(vector3(17.0f, -10.0f, 32));
	diglettPath3.push_back(vector3(17.0f, -14.0f, 32));

	diglettPath4.push_back(vector3(32.0f, -11.0f, 36));
	diglettPath4.push_back(vector3(32.0f, -15.0f, 36));

	diglettPath5.push_back(vector3(-31.0f, -14.5f, 50));
	diglettPath5.push_back(vector3(-31.0f, -19.5f, 50));

	diglettPath6.push_back(vector3(56.0f, -14.0f, 50));
	diglettPath6.push_back(vector3(56.0f, -18.0f, 50));

	/////////////////////////////////////////////////////////////////
	// Piplup path
	////////////////////////////////////////////////////////////////
	piplupPath.push_back(vector3(2.0f, -18.0f, -46.0f));
	piplupPath.push_back(vector3(2.0f, -19.0f, -30.0f));
	piplupPath.push_back(vector3(2.0f, -18.0f, -23.0f));
	piplupPath.push_back(vector3(10.0f, -19.0f, -23.0f));
	piplupPath.push_back(vector3(25.0f, -18.0f, -23.0f));
	piplupPath.push_back(vector3(25.0f, -19.0f, -33.0f));
	piplupPath.push_back(vector3(25.0f, -18.0f, -46.0f));
	piplupPath.push_back(vector3(15.0f, -19.0f, -46.0f));

	piplupPath2.push_back(vector3(14.0f, -17.5f, -37.0f));
	piplupPath2.push_back(vector3(14.0f, -19.0f, -37.0f));





}

/////////////////////////////////////////////////////////////////////
// BuildEnv() - Creates all collision bodies for the environment
/////////////////////////////////////////////////////////////////////
void AppClass::BuildEnv()
{
	/////////////////////////////////////////////////////////////////
	// TREES (Trunk, Canopy) [0 - 18]
	/////////////////////////////////////////////////////////////////
	std::vector<vector3> eBOX;
	eBOX.push_back(vector3(-62.1f, -15.9f, 64.4f));
	eBOX.push_back(vector3(-66.3f, -7.3f, 60.5f));
	m_pEntityMngr->AddEntity("TREE_000T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-56.6f, -5.7f, 67.9f));
	eBOX.push_back(vector3(-72.3f, 2.1f, 55.9f));
	m_pEntityMngr->AddEntity("TREE_000C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-41.6f, -15.9f, 67.2f));
	eBOX.push_back(vector3(-38.2f, -6.7f, 63.4f));
	m_pEntityMngr->AddEntity("TREE_001T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-34.2f, -6.3f, 71.6f));
	eBOX.push_back(vector3(-43.9f, 0.7f, 59.2f));
	m_pEntityMngr->AddEntity("TREE_001C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-38.9f, -15.6f, 41.2f));
	eBOX.push_back(vector3(-32.9f, -6.6f, 45.7f));
	m_pEntityMngr->AddEntity("TREE_002T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-43.1f, -6.4f, 48.4f));
	eBOX.push_back(vector3(-28.8f, 1.1f, 37.1f));
	m_pEntityMngr->AddEntity("TREE_002C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-36.8f, -13.9f, 26.8f));
	eBOX.push_back(vector3(-33.6f, -3.5f, 23.0f));
	m_pEntityMngr->AddEntity("TREE_003T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-30.6f, -3.2f, 19.5f));
	eBOX.push_back(vector3(-39.6f, 9.4f, 28.1f));
	m_pEntityMngr->AddEntity("TREE_003C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-44.5f, -12.9f, 6.2f));
	eBOX.push_back(vector3(-39.6f, -6.4f, 3.3f));
	m_pEntityMngr->AddEntity("TREE_004T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-48.0f, -5.5f, 10.4f));
	eBOX.push_back(vector3(-35.7f, 1.8f, -0.2f));
	m_pEntityMngr->AddEntity("TREE_004C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-20.3f, -13.5f, 19.3f));
	eBOX.push_back(vector3(-21.9f, -9.1f, 21.5f));
	m_pEntityMngr->AddEntity("TREE_005T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-24.2f, -6.7f, 23.7f));
	eBOX.push_back(vector3(-17.8f, -2.1f, 16.8f));
	m_pEntityMngr->AddEntity("TREE_005C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-32.4f, -13.3f, -8.4f));
	eBOX.push_back(vector3(-27.1f, -4.7f, -11.6f));
	m_pEntityMngr->AddEntity("TREE_006T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-22.8f, -1.5f, -4.5f));
	eBOX.push_back(vector3(-38.5f, 8.1f, -15.0f));
	m_pEntityMngr->AddEntity("TREE_006C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-45.9f, -13.6f, -26.4f));
	eBOX.push_back(vector3(-42.6f, -7.0f, -31.6f));
	m_pEntityMngr->AddEntity("TREE_007T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-49.6f, -5.5f, -37.0f));
	eBOX.push_back(vector3(-41.2f, 0.3f, -20.8f));
	m_pEntityMngr->AddEntity("TREE_007C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-23.7f, -14.9f, -25.5f));
	eBOX.push_back(vector3(-25.9f, -5.8f, -28.4f));
	m_pEntityMngr->AddEntity("TREE_008T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-28.3f, 4.3f, -33.3f));
	eBOX.push_back(vector3(-21.9f, -3.0f, -21.2f));
	m_pEntityMngr->AddEntity("TREE_008C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-65.9f, -16.5f, 13.4f));
	eBOX.push_back(vector3(-61.1f, -7.3f, 15.7f));
	m_pEntityMngr->AddEntity("TREE_009T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-69.7f, -6.1f, 19.4f));
	eBOX.push_back(vector3(-58.3f, 2.2f, 10.8f));
	m_pEntityMngr->AddEntity("TREE_009C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-67.6f, -16.6f, -4.0f));
	eBOX.push_back(vector3(-64.9f, -6.7f, -6.4f));
	m_pEntityMngr->AddEntity("TREE_010T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-62.7f, -5.5f, -9.7f));
	eBOX.push_back(vector3(-70.2f, 0.0f, -0.9f));
	m_pEntityMngr->AddEntity("TREE_010C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-70.0f, -16.5f, -40.1f));
	eBOX.push_back(vector3(-66.5f, -6.6f, -43.9f));
	m_pEntityMngr->AddEntity("TREE_011T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-73.3f, -5.4f, -35.6f));
	eBOX.push_back(vector3(-63.1f, 0.4f, -48.6f));
	m_pEntityMngr->AddEntity("TREE_011C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-56.2f, -15.9f, -56.8f));
	eBOX.push_back(vector3(-61.2f, -4.7f, -61.7f));
	m_pEntityMngr->AddEntity("TREE_012T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-54.2f, -2.7f, -67.8f));
	eBOX.push_back(vector3(-67.1f, 8.5f, -54.1f));
	m_pEntityMngr->AddEntity("TREE_012C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-35.2f, -15.1f, -59.9f));
	eBOX.push_back(vector3(-38.8f, -7.0f, -56.5f));
	m_pEntityMngr->AddEntity("TREE_013T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-43.7f, -5.3f, -53.5f));
	eBOX.push_back(vector3(-33.2f, 0.8f, -63.7f));
	m_pEntityMngr->AddEntity("TREE_013C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-11.4f, -15.5f, -60.4f));
	eBOX.push_back(vector3(-16.5f, -6.0f, -57.2f));
	m_pEntityMngr->AddEntity("TREE_014T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(-21.8f, -4.9f, -54.2f));
	eBOX.push_back(vector3(-6.1f, 1.5f, -63.5f));
	m_pEntityMngr->AddEntity("TREE_014C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(55.2f, -14.5f, -55.6f));
	eBOX.push_back(vector3(58.8f, -7.2f, -50.5f));
	m_pEntityMngr->AddEntity("TREE_015T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(53.0f, -4.6f, -45.4f));
	eBOX.push_back(vector3(62.1f, 0.9f, -61.9f));
	m_pEntityMngr->AddEntity("TREE_015C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(53.0f, -13.9f, -28.8f));
	eBOX.push_back(vector3(56.4f, -4.2f, -23.7f));
	m_pEntityMngr->AddEntity("TREE_016T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(58.2f, -3.1f, -18.2f));
	eBOX.push_back(vector3(51.7f, 8.7f, -34.4f));
	m_pEntityMngr->AddEntity("TREE_016C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(53.5f, -12.8f, -2.6f));
	eBOX.push_back(vector3(57.6f, -7.2f, 0.5f));
	m_pEntityMngr->AddEntity("TREE_017T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(63.0f, -3.5f, 3.1f));
	eBOX.push_back(vector3(48.0f, 2.1f, -6.5f));
	m_pEntityMngr->AddEntity("TREE_017C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(53.8f, -13.5f, 18.6f));
	eBOX.push_back(vector3(58.2f, -7.1f, 22.8f));
	m_pEntityMngr->AddEntity("TREE_018T", ET_ENVI_WALL, eBOX);
	eBOX.clear();
	eBOX.push_back(vector3(49.1f, -5.6f, 11.3f));
	eBOX.push_back(vector3(64.9f, -0.3f, 24.1f));
	m_pEntityMngr->AddEntity("TREE_018C", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	/////////////////////////////////////////////////////////////////
	// BUSHES [1-4]
	/////////////////////////////////////////////////////////////////
	eBOX.push_back(vector3(21.6f, -10.8f, -58.4f));
	eBOX.push_back(vector3(10.7f, -15.3f, -63.4f));
	m_pEntityMngr->AddEntity("BUSH_001", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(29.9f, -13.1f, -54.2f));
	eBOX.push_back(vector3(23.9f, -14.9f, -60.5f));
	m_pEntityMngr->AddEntity("BUSH_002", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(19.95f, -11.5f, -6.4f));
	eBOX.push_back(vector3(25.8f, -14.5f, 2.8f));
	m_pEntityMngr->AddEntity("BUSH_003", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(14.4f, -14.7f, 1.8f));
	eBOX.push_back(vector3(19.4f, -13.7f, 6.0f));
	m_pEntityMngr->AddEntity("BUSH_004", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	/////////////////////////////////////////////////////////////////
	// WATER
	/////////////////////////////////////////////////////////////////
	//eBOX.push_back(vector3(2.4f, -15.5f, -51.7f));
	//eBOX.push_back(vector3(29.7f, -17.3f, -20.9f));
	//m_pEntityMngr->AddEntity("WATR_000", ET_ENVI_WALL, eBOX);
	//eBOX.clear();

	/////////////////////////////////////////////////////////////////
	// CAVE
	/////////////////////////////////////////////////////////////////
	eBOX.push_back(vector3(33.4f, -13.0f, 12.5f));
	eBOX.push_back(vector3(-1.8f, 0.2f, 17.3f));
	m_pEntityMngr->AddEntity("CAVE_001", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(51.2f, -14.6f, 43.2f));
	eBOX.push_back(vector3(69.9f, 1.9f, 40.0f));
	m_pEntityMngr->AddEntity("CAVE_002", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(38.1f, -4.0f, 38.5f));
	eBOX.push_back(vector3(37.0f, -13.8f, 50.6f));
	m_pEntityMngr->AddEntity("CAVE_003", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(38.1f, -0.1f, 36.7f));
	eBOX.push_back(vector3(36.5f, -14.4f, 14.7f));
	m_pEntityMngr->AddEntity("CAVE_004", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(69.0f, -14.9f, 43.5f));
	eBOX.push_back(vector3(70.2f, 0.8f, 68.5f));
	m_pEntityMngr->AddEntity("CAVE_005", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(38.4f, -15.4f, 68.3f));
	eBOX.push_back(vector3(68.2f, 1.0f, 68.8f));
	m_pEntityMngr->AddEntity("CAVE_006", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-1.9f, -15.4f, 68.4f));
	eBOX.push_back(vector3(35.2f, 1.0f, 68.8f));
	m_pEntityMngr->AddEntity("CAVE_007", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-3.6f, 0.1f, 40.0f));
	eBOX.push_back(vector3(-6.0f, -13.9f, 53.1f));
	m_pEntityMngr->AddEntity("CAVE_008", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-16.7f, -14.6f, 40.0f));
	eBOX.push_back(vector3(-18.1f, 0.1f, 70.5f));
	m_pEntityMngr->AddEntity("CAVE_009", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-2.8f, 0.2f, 69.6f));
	eBOX.push_back(vector3(-16.3f, -16.5f, 68.3f));
	m_pEntityMngr->AddEntity("CAVE_010", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-5.5f, -14.6f, 13.6f));
	eBOX.push_back(vector3(-2.8f, 0.1f, 37.0f));
	m_pEntityMngr->AddEntity("CAVE_011", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-6.3f, 0.1f, 38.2f));
	eBOX.push_back(vector3(-13.7f, -3.6f, 67.7f));
	m_pEntityMngr->AddEntity("CAVE_012", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(39.2f, -1.3f, 43.5f));
	eBOX.push_back(vector3(49.4f, 1.0f, 68.0f));
	m_pEntityMngr->AddEntity("CAVE_013", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(68.1f, 2.2f, 43.9f));
	eBOX.push_back(vector3(52.3f,-1.0f, 67.7f));
	m_pEntityMngr->AddEntity("CAVE_014", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(50.0f, -3.9f, 42.3f));
	eBOX.push_back(vector3(38.9f, -0.9f, 38.9f));
	m_pEntityMngr->AddEntity("CAVE_015", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(35.4f, -1.1f, 68.2f));
	eBOX.push_back(vector3(-1.0f, 1.0f, 38.0f));
	m_pEntityMngr->AddEntity("CAVE_016", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-1.3f, 1.0f, 17.7f));
	eBOX.push_back(vector3(33.6f, -1.1f, 36.9f));
	m_pEntityMngr->AddEntity("CAVE_017", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-1.2f, -8.0f, 36.7f));
	eBOX.push_back(vector3(2.4f, -3.1f, 25.4f));
	m_pEntityMngr->AddEntity("CAVE_018", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(3.8f, -3.0f, 24.4f));
	eBOX.push_back(vector3(12.0f, -8.0f, 17.6f));
	m_pEntityMngr->AddEntity("CAVE_019", ET_ENVI_WALL, eBOX);
	eBOX.clear();

	/////////////////////////////////////////////////////////////////
	// GROUND
	/////////////////////////////////////////////////////////////////
	eBOX.push_back(vector3(70.3f, -18.5f, -70.8f));
	eBOX.push_back(vector3(35.86f, -18.0f, -37.99f));
	m_pEntityMngr->AddEntity("GRND_001", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(35.9f, -14.5f, -0.2f));
	eBOX.push_back(vector3(70.8f, -17.5f, -37.0f));
	m_pEntityMngr->AddEntity("GRND_002", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(35.6f, -14.5f, 1.9f));
	eBOX.push_back(vector3(70.3f, -16.0f, 36.9f));
	m_pEntityMngr->AddEntity("GRND_003", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(70.2f, -17.0f, 69.6f));
	eBOX.push_back(vector3(34.9f, -14.5f, 38.8f));
	m_pEntityMngr->AddEntity("GRND_004", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(35.2f, -15.5f, -37.8f));
	eBOX.push_back(vector3(-1.1f, -19.0f,-71.2f));
	m_pEntityMngr->AddEntity("GRND_005", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(35.2f, -16.0f, -37.1f));
	eBOX.push_back(vector3(-0.5f, -15.5f, -1.1f));
	m_pEntityMngr->AddEntity("GRND_006", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(16.7f, -15.0f, -16.0f));
	eBOX.push_back(vector3(-1.4f, -13.5f, -0.6f));
	m_pEntityMngr->AddEntity("GRND_006.1", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-1.6f, -15.0f, 0.3f));
	eBOX.push_back(vector3(34.8f, -15.5f, 12.6f));
	m_pEntityMngr->AddEntity("GRND_007.1", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-1.7f, -11.0f, 37.0f));
	eBOX.push_back(vector3(34.0f, -11.0f, 19.9f));
	m_pEntityMngr->AddEntity("GRND_007.2", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-0.96f, -15.0f, 67.6f));
	eBOX.push_back(vector3(33.5f, -15.0f, 43.5f));
	m_pEntityMngr->AddEntity("GRND_008.1", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-3.0f, -16.0f, -72.2f));
	eBOX.push_back(vector3(-38.7f, -19.5f, -38.6f));
	m_pEntityMngr->AddEntity("GRND_009", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-2.6f, -15.0f, -37.1f));
	eBOX.push_back(vector3(-36.6f, -17.0f, -1.5f));
	m_pEntityMngr->AddEntity("GRND_010", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-2.8f, -15.0f, 0.5f));
	eBOX.push_back(vector3(-39.0f, -15.5f, 37.1f));
	m_pEntityMngr->AddEntity("GRND_011", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-39.2f, -15.0f, 37.9f));
	eBOX.push_back(vector3(-2.9f, -18.0f, 70.0f));
	m_pEntityMngr->AddEntity("GRND_012", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(10.7f, -11.5f, 55.7f));
	eBOX.push_back(vector3(-1.1f, -13.5f, 40.3f));
	m_pEntityMngr->AddEntity("GRND_012.1", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-39.9f, -16.0f, -73.7f));
	eBOX.push_back(vector3(-70.4f, -19.0f, -38.7f));
	m_pEntityMngr->AddEntity("GRND_013", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-70.4f, -18.5f, -36.5f));
	eBOX.push_back(vector3(-40.4f, -15.0f, -1.2f));
	m_pEntityMngr->AddEntity("GRND_014", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-39.8f, -16.0f, 37.0f));
	eBOX.push_back(vector3(-70.7f, -19.0f, 0.8f));
	m_pEntityMngr->AddEntity("GRND_015", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-39.7f, -16.0f, 37.6f));
	eBOX.push_back(vector3(-70.3f, -17.0f, 69.6f));
	m_pEntityMngr->AddEntity("GRND_016", ET_ENVI_GROUND, eBOX);
	eBOX.clear();

	eBOX.push_back(vector3(-25.7f, -13.6f, 61.0f));
	eBOX.push_back(vector3(-47.0f, -14.3f, -38.6f));
	m_pEntityMngr->AddEntity("GRND_017", ET_ENVI_GROUND, eBOX);
	eBOX.clear();


	eBOX.push_back(vector3(-6.0f, -12.5f,0.0f));
	eBOX.push_back(vector3(16.0f, -14.0f, -15.5f));
	m_pEntityMngr->AddEntity("GRND_018", ET_ENVI_GROUND, eBOX);
	eBOX.clear();
}