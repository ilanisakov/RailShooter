/////////////////////////////////////////////////////////////////////
// File: AppClassControls.cpp
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
//ProcessKeyboard() - Manage the response of key presses
/////////////////////////////////////////////////////////////////////
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.2f;

#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false, bLastF = false, 
				bLastSpace = false, bLastC = false, bLastG = false, bLastT = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion

#pragma region Camera Positioning
	if(bModifier)
		fSpeed *= 10.0f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCameraMngr->MoveForward(fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCameraMngr->MoveForward(-fSpeed);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCameraMngr->MoveSideways(-fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCameraMngr->MoveSideways(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_pCameraMngr->MoveVertical(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_pCameraMngr->MoveVertical(fSpeed);


	//Alternative rot controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) //pitch up
	{
		m_pCameraMngr->ChangePitch(fSpeed *50.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) //pitch down
	{
		m_pCameraMngr->ChangePitch(fSpeed * -50.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) //yaw left
	{
		m_pCameraMngr->ChangeYaw(fSpeed * 50.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) //yaw right
	{
		m_pCameraMngr->ChangeYaw(fSpeed * -50.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) //roll left
	{
		m_pCameraMngr->ChangeRoll(fSpeed * 50.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) //roll right
	{
		m_pCameraMngr->ChangeRoll(fSpeed * -50.0f);
	}
#pragma endregion


#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL));
	ON_KEY_PRESS_RELEASE(F1, NULL, m_pCameraMngr->SetCameraMode(CAMPERSP));
	ON_KEY_PRESS_RELEASE(F2, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOZ));
	ON_KEY_PRESS_RELEASE(F3, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOY));
	ON_KEY_PRESS_RELEASE(F4, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOX));
	static bool bFPSControll = false;
	ON_KEY_PRESS_RELEASE(F, bFPSControll = !bFPSControll, m_pCameraMngr->SetFPS(bFPSControll));

	ON_KEY_PRESS_RELEASE(Space, ThrowPokecube(), NULL);
	ON_KEY_PRESS_RELEASE(C, ToggleCamera(), NULL);
	ON_KEY_PRESS_RELEASE(G, ToggleGeometry(), NULL);
	ON_KEY_PRESS_RELEASE(T, ToggleEnvTrack(), NULL);
#pragma endregion
}

/////////////////////////////////////////////////////////////////////
//ProcessMouse() - Manage the response of key presses and mouse 
//                 position
/////////////////////////////////////////////////////////////////////
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
	sf::Vector2i pos = sf::Mouse::getPosition();
	vector3 playerLoc = c_player->GetPosition();
	vector3 lookHelp;
	float x = pos.x;
	float y = pos.y;
	
	//putting X and Y into the window coordinate space
	x = x - windowOffsetX;
	y = y - windowOffsetY;

	if (x < 0)	
		x = 0;
	else if (x > width)
		x = width;
	if (y < 0)
		y = 0;
	else if (y > height)
		y = height;

	//bring windowed coord system to -1 to 1 coord system
	float Xpercent = MapValue(x, 0.0f, (float)width, -1.0f, 1.0f);
	float Ypercent = MapValue(y, 0.0f, (float)height, 1.0f, -1.0f);
	
	//get how many degrees were gonna be rotating with
	XRotation = XRotation + (Xpercent * 1.1);
	YRotation = YRotation + (Ypercent * 1.1);

	if (YRotation > 90)
		YRotation = 90;
	else if (YRotation < -90)
		YRotation = -90;

	lookHelp.x = cos(XRotation * (PI / 180.0f));
	lookHelp.y = sin(YRotation * (PI / 180.0f));
	lookHelp.z = sin(XRotation * (PI / 180.0f));

	lookDir.y = playerLoc.y + lookHelp.y;
	lookDir.z = playerLoc.z + lookHelp.z;
	lookDir.x = playerLoc.x + lookHelp.x;

	//std::cout << "PlayerLoc: " << playerLoc.x << "," << playerLoc.y << "," << playerLoc.z << std::endl;
	//std::cout << "LookDir: " << lookDir.x << "," << lookDir.y << "," << lookDir.z << std::endl;
	//std::cout << "LookHelp: " << lookHelp.x << "," << lookHelp.y << "," << lookHelp.z << std::endl;

	m_pCameraMngr->SetPositionTargetAndView(playerLoc, lookDir, REAXISY, railCamIndex);
	
	

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;
}
