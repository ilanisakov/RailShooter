/////////////////////////////////////////////////////////////////////
// File: AppClassControls.h
// DSA2 A08_CameraClass
// Authors:
//		Mary Spencer
//		Martin Kurtz
// 
/////////////////////////////////////////////////////////////////////
//==================================================================================================
//	CONTROLS:
//  Left  Click & Drag: Roll
//  Right Click & Drag: Pitch/Yaw
//  W: Forward
//  S: Backwards
//  A: Left
//  D: Right
//  Q: Up
//  E: Down
//==================================================================================================

#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;

#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
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

	if (bModifier)
		fSpeed *= 10.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))  //+Forward
	{
		myCamera->MoveForward(fSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))  //-Forward
	{
		myCamera->MoveForward(fSpeed * -1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))  //+Sideways
	{
		myCamera->MoveSideways(fSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))  //-Sideways
	{
		myCamera->MoveSideways(fSpeed * -1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))  //+Vertical
	{
		myCamera->MoveVertical(fSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))  //-Vertical
	{
		myCamera->MoveVertical(fSpeed * -1.0f);
	}
	//Alternative rot controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) //pitch up
	{
		myCamera->ChangePitch(fSpeed *100.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) //pitch down
	{
		myCamera->ChangePitch(fSpeed * -100.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) //yaw left
	{
		myCamera->ChangeYaw(fSpeed * 100.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) //yaw right
	{
		myCamera->ChangeYaw(fSpeed * -100.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) //roll left
	{
		myCamera->ChangeRoll(fSpeed * 100.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) //roll right
	{
		myCamera->ChangeRoll(fSpeed * -100.0f);
	}

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
#pragma endregion
}
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;

	UINT MouseX, newMouseX;
	UINT MouseY, newMouseY;
	UINT CenterX, CenterY;
	POINT pt, pt2;
	float deltaMouse;

	//get center of window
	CenterX = m_pSystem->WindowX + m_pSystem->WindowWidth / 2;
	CenterY = m_pSystem->WindowY + m_pSystem->WindowHeight / 2;

	GetCursorPos(&pt); 

	MouseX = pt.x;
	MouseY = pt.y;

	//SetCursorPos(CenterX, CenterY);
	

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
	{
	
		m_bArcBall = false;

	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		//ROLL CW (right)
		if (MouseX > CenterX ){
			deltaMouse = static_cast<float>(CenterX - MouseX);
			myCamera->ChangeRoll(-1.0f);
		}
		//ROLL CCW (left)
		else if (MouseX < CenterX){
			deltaMouse = static_cast<float>(CenterX - MouseX);
			myCamera->ChangeRoll(1.0f);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		m_bFPC = false;
	

		// YAW LEFT
		 if (MouseX < CenterX){
			deltaMouse = static_cast<float>(CenterX - MouseX);
			myCamera->ChangeYaw(.5f);
		}
		// YAW RIGHT
		else if (MouseX > CenterX)
		{
			deltaMouse = static_cast<float>(MouseX - CenterX);
			myCamera->ChangeYaw(-.5f);
		}

		// PITCH DOWN
	     if (MouseY < CenterY){
			deltaMouse = static_cast<float>(CenterY - MouseY);
			myCamera->ChangePitch(.5f);
		}

		//PITCH UP
		else if (MouseY > CenterY)
		{
			deltaMouse = static_cast<float>(MouseY - CenterY);
			myCamera->ChangePitch(-.5f);
		}

	}

}
