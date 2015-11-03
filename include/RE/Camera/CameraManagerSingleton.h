/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __CAMERAMANAGERSINGLETON_H_
#define __CAMERAMANAGERSINGLETON_H_

#include "RE\Camera\CameraClass.h"

namespace ReEng
{
	//Camera Manager Singleton
	class ReEngDLL CameraManagerSingleton
	{
		static CameraManagerSingleton* m_pInstance; // Singleton pointer
		std::vector<CameraClass*> m_lCamera; //Camera list holder
		uint m_nActiveCamera = 0;
		uint m_nCameraCount = 0;
	public:
		/* Gets/Constructs the singleton pointer */
		/*
		Method: Usage:
		Arguments:
		Output:
		*/
		static CameraManagerSingleton* GetInstance();
		/* Destroys the singleton */
		/*
		Method: Usage:
		Arguments: ---
		Output: ---
		*/
		static void ReleaseInstance(void);

		/* AddCamera will create a new CameraClass object and add it to the list
		   returning the index in the list
		   */
		/*
		Method: Usage:
		Arguments:
		Output:
		*/
		uint AddCamera(vector3 a_v3Eye, vector3 a_v3Target, vector3 a_v3Up);

		/* Calculates the view of the camera specified by index, if -1 it will use the active camera */
		/*
		Method: Usage:
		Arguments:
		Output: ---
		*/
		void CalculateView(int a_nIndex = -1);

		/* Calculates the Projection of the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void CalculateProjection(int a_nIndex = -1);

		/* Sets the active camera flag from the list */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void SetActiveCamera(uint a_nIndex = 0);

		/* Gets the View matrix from the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output:
		*/
		matrix4 GetViewMatrix(int a_nIndex = -1);

		/* Gets the Projection matrix from the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output:
		*/
		matrix4 GetProjectionMatrix(int a_nIndex = -1);

		/* Gets the ModelViewProjection matrix from the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output:
		*/
		matrix4 GetMVP(matrix4 a_m4ModelToWorld, int a_nIndex = -1);
		/* Gets the ViewProjection matrix from the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output:
		*/
		matrix4 GetVP(int a_nIndex = -1);

		/* Gets the position of the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output:
		*/
		vector3 GetPosition(int a_nIndex = -1);
		/* Sets the camera specified by index at the specified position and target, if -1 it will use the active camera */
		/*
		Method: SetPositionAndTarget
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void SetPositionAndTarget(vector3 a_v3Position, vector3 a_v3Target, int a_nIndex = -1);

		/* Gets the camera space just in front of the camera by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output:
		*/
		matrix4 GetCameraSpaceAdjusted(int a_nIndex = -1);
		/* Gets the camera plane of the camera by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output:
		*/
		matrix4 GetCameraPlane(int a_nIndex = -1);

		/* Sets the camera in First Person Shooter mode, if false it will work like an aircraft, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void SetFPS(bool a_bFPS = true, int a_nIndex = -1);

		/* Sets the camera in Perspective mode, if false it will work as an orthographic camera, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void SetCameraMode(CAMERAMODE a_nMode = CAMERAMODE::CAMPERSP, int a_nIndex = -1);

		/* Returns the current value for the camera mode of the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output:
		*/
		CAMERAMODE GetCameraMode(int a_nIndex = -1);

		/* Returns the number of cameras in the list specified by index, if -1 it will use the active camera */
		
		/*
		Method: 
		Usage:
		Arguments: ---
		Output: uint number of cameras
		*/uint GetCameraCount(void);

		/* Changes the near and far planes of the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void SetNearFarPlanes(float a_fNear, float a_fFar, int a_nIndex = -1);
		
		/* Set Field of View */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void SetFOV(float a_fFOV, int a_nIndex = -1);

		/*	Translates the camera forward or backward of the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void MoveForward(float a_fDistance = 0.1f, int a_nIndex = -1);
		/*	Translates the camera Upward or downward of the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void MoveVertical(float a_fDistance = 0.1f, int a_nIndex = -1);
		/*	Translates the camera right or left of the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void MoveSideways(float a_fDistance = 0.1f, int a_nIndex = -1);

		/*	Rotates the camera Pitch of the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void ChangePitch(float a_fDegree = 1.0f, int a_nIndex = -1);
		/*	Rotates the camera Yaw of the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void ChangeYaw(float a_fDegree = 1.0f, int a_nIndex = -1);
		/*	Rotates the camera Roll of the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void ChangeRoll(float a_fDegree = 1.0f, int a_nIndex = -1);

		/* Sets the camera at the specified position of the camera specified by index, if -1 it will use the active camera */
		/*
		Method: 
		Usage:
		Arguments:
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void SetPosition(vector3 a_vPosition, int a_nIndex = -1);

		/*
		Method: SetTarget
		Usage: Sets the Target of the camera specified by index at the specified position
		Arguments:
			vector3 a_vTarget -> 
			int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
		Output: ---
		*/
		void SetTarget(vector3 a_vTarget, int a_nIndex = -1);

	private:
		/* Constructor */
		/*
		Method: 
		Usage:
		Arguments: ---
		Output:
		*/
		CameraManagerSingleton(void);
		/* Copy Constructor */
		/*
		Method: Usage:
		Arguments:
		Output:
		*/
		CameraManagerSingleton(CameraManagerSingleton const& other);
		/* Copy Assignment Operator */
		/*
		Method: 
		Usage:
		Arguments:
		Output:
		*/
		CameraManagerSingleton& operator=(CameraManagerSingleton const& other);
		/* Destructor */
		/*
		Method: 
		Usage:
		Arguments: ---
		Output: ---
		*/
		~CameraManagerSingleton(void);

		/* Releases the objects memory */
		/*
		Method: 
		Usage:
		Arguments: ---
		Output: ---
		*/
		void Release(void);
		/* Initializes the objects fields */
		/*
		Method: 
		Usage:
		Arguments: ---
		Output: ---
		*/
		void Init(void);
	};

}
#endif //__CAMERAMANAGERSINGLETON_H_