/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __LIGHTCLASS_H_
#define __LIGHTCLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

class ReEngDLL LightClass
{
	//Private Fields
	float m_fIntensity = 0.0f;
	vector3 m_v4Position;
	vector3 m_vColor;
public:
	/*
	Method: LightClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	LightClass(void);
	/* 	Constructor */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	LightClass(vector3 a_v4Position, vector3 a_v3Color, float a_vIntensity);
	/* Copy Constructor */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	LightClass(const LightClass& other);
	/* Copy Assignment operator */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	LightClass& operator=(const LightClass& other);
	/* Destructor */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	~LightClass(void);
	
	//Helper Methods
	/* Swaps the information of two objects*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void Swap(LightClass& other);

	//Accessors
	/* Sets the position of the light */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetPosition(vector3 a_v4Position);
	/* Gets the position of the light */
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	vector3 GetPosition(void);
	/* Property SetPosition/GetPosition */
	//__declspec(property(put = SetPosition, get = GetPosition)) vector3 Position;

	/* Sets the color of the light */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetColor(vector3 a_v3Color);
	/* Gets the color of the light*/
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	vector3 GetColor(void);
	/* Property SetColor/GetColor */
	//__declspec(property(put = SetColor, get = GetColor)) vector3 Color;

	/* Set Intensity of the light */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetIntensity(float a_fIntensity);
	/* Gets the intensity of the light*/
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	float GetIntensity(void);
	/* Property SetIntensity/GetIntensity */
	//__declspec(property(put = SetIntensity, get = GetIntensity)) float Intensity;

protected:
	//Protected methods
	/* Initializates the object values*/
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void);
	/* Releases the object*/
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<LightClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<LightClass*>;

}
#endif //__LIGHT_H__