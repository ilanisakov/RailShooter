/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __FRAMECLASS_H_
#define __FRAMECLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

class ReEngDLL FrameClass
{
	bool m_bKeyframe = true;
	bool m_bVisible = true;
	vector3 m_v3Translation = vector3(0.0f);
	vector3 m_v3Rotation = vector3(0.0f);
	vector3 m_v3Scale = vector3(1.0f);
	matrix4 m_m4Transformation = matrix4(1.0f);
public:
	
	/*
	Method: FrameClass
	Usage: constructor
	Arguments: ---
	Output:
	*/
	FrameClass();
	/*
	Method: FrameClass
	Usage: Copy Constructor
	Arguments:
	Output:
	*/
	FrameClass(const FrameClass& other);
	/*
	Method: operator=
	Usage: Copy Assignment Operator
	Arguments:
	Output:
	*/
	virtual FrameClass& operator=(const FrameClass& other);
	/*
	Method: ~FrameClass
	Usage: Destructor
	Arguments:  ---
	Output: ---
	*/
	~FrameClass(void);
	/*
	Method: GetTransformation
	Usage:
	Arguments: ---
	Output:
	*/
	matrix4 GetTransformation(void);
	/*
	Method: ComputeTransformation
	Usage:
	Arguments:
	Output:
	*/
	matrix4 ComputeTransformation(	vector3 a_v3Translation,
									vector3 a_v3Pivot,
									vector3 a_v3Rotation,
									vector3 a_v3Scale,
									bool a_bVisible,
									bool a_bKeyFrame,
									matrix4 a_m4ToParent = matrix4(1.0f));
	/*
	Method: ComputeTransformation
	Usage:
	Arguments:
	Output:
	*/
	matrix4 ComputeTransformation(matrix4 a_m4ToParent);
	/*
	Method: ComputeTransformation
	Usage:
	Arguments:
	Output:
	*/
	matrix4 ComputeTransformation(vector3 a_v3Pivot);
	/*
	Method: IsKeyframe
	Usage:
	Arguments: ---
	Output:
	*/
	bool IsKeyframe(void);
	/*
	Method: SetVisible
	Usage:
	Arguments: ---
	Output:
	*/
	void SetVisible(bool a_bVisible);
	/*
	Method: IsVisible
	Usage:
	Arguments: ---
	Output:
	*/
	bool IsVisible(void);
	/*
	Method: SetKeyframe
	Usage:
	Arguments: ---
	Output:
	*/
	void SetKeyframe(bool a_bKeyframe);
	/*
	Method: SetPosX
	Usage:
	Arguments:
	Output: ---
	*/
	void SetPosX( float a_fValue );
	/*
	Method: SetPosY
	Usage:
	Arguments:
	Output: ---
	*/
	void SetPosY( float a_fValue );
	/*
	Method: SetPosZ
	Usage:
	Arguments:
	Output: ---
	*/
	void SetPosZ( float a_fValue );
	/*
	Method: SetAngX
	Usage:
	Arguments:
	Output: ---
	*/
	void SetAngX( float a_fValue );
	/*
	Method: SetAngY
	Usage:
	Arguments:
	Output: ---
	*/
	void SetAngY( float a_fValue );
	/*
	Method: SetAngZ
	Usage:
	Arguments:
	Output: ---
	*/
	void SetAngZ( float a_fValue );
	/*
	Method: SetSizeX
	Usage:
	Arguments:
	Output: ---
	*/
	void SetSizeX( float a_fValue );
	/*
	Method: SetSizeY
	Usage:
	Arguments:
	Output: ---
	*/
	void SetSizeY( float a_fValue );
	/*
	Method: SetSizeZ
	Usage:
	Arguments:
	Output: ---
	*/
	void SetSizeZ( float a_fValue );
	/*
	Method: GetPos
	Usage: Gets the Position
	Arguments:
	Output: ---
	*/
	vector3 GetPos(void);
	/*
	Method: GetAng
	Usage: Gets the Rotation
	Arguments: ---
	Output:
	*/
	vector3 GetAng(void);
	/*
	Method: GetSize
	Usage: Gets the Scale
	Arguments: ---
	Output:
	*/
	vector3 GetSize(void);
	/*
	Method: GetPosX
	Usage:
	Arguments: ---
	Output:
	*/
	float GetPosX( void );
	/*
	Method: GetPosY
	Usage:
	Arguments: ---
	Output:
	*/
	float GetPosY( void );
	/*
	Method: GetPosZ
	Usage:
	Arguments: ---
	Output:
	*/
	float GetPosZ( void );
	/*
	Method: GetAngX
	Usage:
	Arguments: ---
	Output:
	*/
	float GetAngX( void );
	/*
	Method: GetAngY
	Usage:
	Arguments: ---
	Output:
	*/
	float GetAngY( void );
	/*
	Method: GetAngZ
	Usage:
	Arguments: ---
	Output:
	*/
	float GetAngZ( void );
	/*
	Method: GetSizeX
	Usage:
	Arguments: ---
	Output:
	*/
	float GetSizeX( void );
	/*
	Method: GetSizeY
	Usage:
	Arguments: ---
	Output:
	*/
	float GetSizeY( void );
	/*
	Method: GetSizeZ
	Usage:
	Arguments: ---
	Output:
	*/
	float GetSizeZ( void );
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<FrameClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<FrameClass*>;

}
#endif //__ANIMATIONFRAMECLASS_H_