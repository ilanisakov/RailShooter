/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __CAMERACLASS_H_
#define __CAMERACLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{
	//Camera Class
	class ReEngDLL CameraClass
	{
		bool m_bFPS = true; //If set to false will behave like a flight simulator camera

		CAMERAMODE m_nMode = CAMERAMODE::CAMPERSP; //Sets the mode the camera will display

		float m_fFOV = 45.0f;

		vector2 m_v2NearFar = vector2(0.001f, 1000.0f);

		vector3 m_v3Position = vector3(0.0f, 0.0f, 5.0f);
		vector3 m_v3Target = vector3(0.0f, 0.0f, 5.0f);
		vector3 m_v3Top = vector3(0.0f, 1.0f, 0.0f);

		vector3 m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
		vector3 m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
		vector3 m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);

		vector3 m_v3PitchYawRoll = vector3(0.0f);

		matrix4 m_m4Projection = matrix4(1.0f);
		matrix4 m_m4View = matrix4(1.0f);

	public:
		/*
		Method: CameraClass
		Usage: Constructor
		Arguments: ---
		Output: class object
		*/
		CameraClass(void);
		/* Constructor with parameters */
		/*
		Method: 
		Usage:
		Arguments:
		Output:
		*/
		CameraClass(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);
		/* Copy Constructor */
		/*
		Method: 
		Usage:
		Arguments:
		Output:
		*/
		CameraClass(CameraClass const& other);
		/* Copy Assignment Operator*/
		/*
		Method: 
		Usage:
		Arguments:
		Output:
		*/
		CameraClass& operator=(CameraClass const& other);
		/* Destructor */
		/*
		Method: 
		Usage:
		Arguments: ---
		Output: ---
		*/
		~CameraClass(void);

		/* Gets the View matrix from the camera */
		/*
		Method: 
		Usage:
		Arguments: ---
		Output:
		*/
		matrix4 GetViewMatrix(void);
		/* Gets the Projection matrix from the camera */
		/*
		Method: 
		Usage:
		Arguments: ---
		Output:
		*/
		matrix4 GetProjectionMatrix(void);
		/* Gets the ModelViewProjection matrix from the camera */
		/*
		Method: 
		Usage:
		Arguments:
		Output:
		*/
		matrix4 GetMVP(matrix4 a_m4ModelToWorld);
		/* Gets the ViewProjection matrix from the camera */
		/*
		Method: 
		Usage:
		Arguments: ---
		Output:
		*/
		matrix4 GetVP(void);

		/* Gets the position of the camera */
		/*
		Method: 
		Usage:
		Arguments: ---
		Output:
		*/
		vector3 GetPosition(void);

		/* Changes the near and far planes */
		/*
		Method: 
		Usage:
		Arguments:
		Output:
		*/
		void SetNearFarPlanes(float a_fNear, float a_fFar);
		/* Calculates the projection based on the camera values */
		/*
		Method: 
		Usage:
		Arguments: ---
		Output: ---
		*/
		void CalculateProjection(void);
		/* Calculates the view based on the camera values */
		/*
		Method: 
		Usage:
		Arguments: ---
		Output: ---
		*/
		void CalculateView(void);
		/* Set Field of View */
		/*
		Method: 
		Usage:
		Arguments:
		Output:
		*/
		void SetFOV(float a_fFOV);

		/*
		Method: 
		Usage: Sets the camera at the specified position
		Arguments:
		Output:
		*/
		void SetPosition(vector3 a_v3Position);
		/*
		Method:
		Usage: Sets the target of the camera to the specified position
		Arguments:
			vector3 a_vTarget -> point to look at
		Output:
		*/
		void SetTarget(vector3 a_v3Target);
		/*
		Method: 
		Usage: Sets the camera at the specified position and target
		Arguments:
		Output:
		*/
		void SetPositionAndTarget(vector3 a_v3Position, vector3 a_v3Target);

		/*
		Method: 
		Usage: Gets the camera space just in front of the camera
		Arguments: ---
		Output:
		*/
		matrix4 GetCameraSpaceAdjusted(void);
		
		/*
		Method: 
		Usage: Gets the camera plane of the camera
		Arguments: ---
		Output:
		*/
		matrix4 GetCameraPlane(void);

		/*
		Method: 
		Usage: Translates the camera forward or backward
		Arguments: 
		Output: ---
		*/
		void MoveForward(float a_fDistance = 0.1f);
		/*
		Method: 
		Usage: Translates the camera Upward or downward
		Arguments: 
		Output: ---
		*/
		void MoveVertical(float a_fDistance = 0.1f);
		/*
		Method: 
		Usage: Translates the camera right or left
		Arguments:
		Output: ---
		*/
		void MoveSideways(float a_fDistance = 0.1f);

		/*
		Method: 
		Usage: Rotates the camera Pitch
		Arguments: 
		Output: ---
		*/
		void ChangePitch(float a_fDegree = 0.01f);
		
		/*
		Method: 
		Usage: Rotates the camera Yaw
		Arguments:
		Output: ---
		*/
		void ChangeYaw(float a_fDegree = 0.01f);
		/*
		Method: 
		Usage: Rotates the camera Roll
		Arguments:
		Output: ---
		*/
		void ChangeRoll(float a_fDegree = 0.01f);

		
		/*
		Method: 
		Usage: Sets the camera in First Person Shooter mode, if false it will work like an aircraft
		Arguments:
		Output: ---
		*/
		void SetFPS(bool a_bFPS = true);
		
		/*
		Method: 
		Usage: Sets the camera in Perspective mode, if false it will work as an orthographic camera
		Arguments:
		Output:
		*/
		void SetCameraMode(CAMERAMODE a_nMode = CAMERAMODE::CAMPERSP);
		
		/*
		Method: 
		Usage: Returns the current value for the camera mode
		Arguments: ---
		Output:
		*/
		CAMERAMODE GetCameraMode(void);

		/*
		Method: 
		Usage: Resets the value of the camera
		Arguments: ---
		Output: ---
		*/
		void ResetCamera(void);

	private:
		/*
		Method: 
		Usage: Releases the object from memory
		Arguments: ---
		Output: ---
		*/
		void Release(void);
		/*
		Method: 
		Usage: Initialize the object's fields
		Arguments: ---
		Output: ---
		*/
		void Init(void);
		
		/*
		Method: 
		Usage: Swaps the contents of the object with another object's content
		Arguments:
		Output: ---
		*/
		void Swap(CameraClass& other);
	};

	EXPIMP_TEMPLATE template class ReEngDLL std::vector<CameraClass>;
	EXPIMP_TEMPLATE template class ReEngDLL std::vector<CameraClass*>;
}
#endif //__CAMERACLASS_H_