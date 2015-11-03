/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __ANIMATIONCLASS_H_
#define __ANIMATIONCLASS_H_

#include "RE\System\SystemSingleton.h"
#include "RE\Animation\FrameClass.h"

namespace ReEng
{

class ReEngDLL AnimationClass
{
public:
	/*
	Method: AnimationClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	AnimationClass(void);
	/*
	Method: AnimationClass
	Usage: Copy Constructor
	Arguments: other instance
	Output: class object
	*/
	AnimationClass(const AnimationClass& other);
	/*
	Method: operator=
	Usage: copy assignment operator
	Arguments: other instance
	Output: ---
	*/
	AnimationClass& operator=(const AnimationClass& other);
	/*
	Method: ~AnimationClass
	Usage: destructor
	Arguments: ---
	Output: ---
	*/
	~AnimationClass(void);
	/*
	Method: Init
	Usage: Initializes the variable members
	Arguments: ---
	Output: ---
	*/
	void Init(void);
	/*
	Method: Release
	Usage: Deinitializes the variable members
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Method: Swap
	Usage: swaps the values of the member fields of incoming object for self's
	Arguments: other instance
	Output: ---
	*/
	void Swap(AnimationClass& other);
	/*
	Method: AnimationClass
	Usage: constructor, will create a number of frames
	Arguments:
		FrameClass *a_pFrame -> pointer to a frame class object 
		int a_nFrames -> number of frames to create
	Output: class object
	*/
	AnimationClass(FrameClass *a_pFrame, int a_nFrames);
	/*
	Method: CheckInterpolation const;
	Usage: Checks the interpolation of the frames
	Arguments:
		FrameClass *a_pFrame -> pointer to frame object
		int a_nFrames
	Output: ---
	*/
	void CheckInterpolation(FrameClass *a_pFrame, int a_nFrames) const;
private:
	/*
	Method: Interpolation const;
	Usage: Interpolates the frames from the first to the last frame
	Arguments:
		FrameClass *a_pFrame -> frame pointer
		int a_nFirstKeyFrame -> First frame to interpolate
		int a_nLastKeyFrame -> Last frame to interpolate
	Output: ---
	*/
	void Interpolation(FrameClass *a_pFrame, int a_nFirstKeyFrame, int a_nLastKeyFrame) const;
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<AnimationClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<AnimationClass*>;

}
#endif //__ANIMATIONCLASS_H__