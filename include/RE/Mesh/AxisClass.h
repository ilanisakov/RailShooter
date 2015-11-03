/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __AxisClass_H_
#define __AxisClass_H_

#include "RE\Mesh\PrimitiveManagerSingleton.h"
using namespace ReEng;
//System Class
class ReEngDLL AxisClass 
{
	bool m_bVisibleOrigin = false;	//Visibility of the Origin of the object
	bool m_bVisibleCenter = false;	//Visibility of the Center of the object
	bool m_bVisiblePivot =  false;	//Visibility of the Pivot of the object

	float m_fSize = 0.0f;

	vector3 m_v3Pivot;		//Pivot of rotation in local space
	vector3 m_v3Centroid;	//Centroid of shape in local space

	matrix4 m_m4ToWorld;//Model to World matrix
	matrix4 m_mPivot;	//Pivot origin in global coordinates
	matrix4 m_mCentroid;//Centroid in global coordinates

	PrimitiveManagerSingleton* m_pPrimitiveMngr = nullptr;
public:
	/*
	Method: AxisClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	AxisClass(void);
	/* Copy Constructor */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	AxisClass(AxisClass const& other);
	/* Copy Assignment Operator	*/
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	AxisClass& operator=(AxisClass const& other);
	/*	Destructor	*/
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	~AxisClass(void);

	/* Gets the "ModelToWorld" matrix associated with the bounding box */
	/*
	Method: Usage:
	Arguments: ---
	Output:
	*/
	matrix4 GetModelMatrix(void);
	/* Sets the "ModelToWorld" matrix associated with the bounding box */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);
	/* "ModelToWorld"
	GetModelMatrix() or SetModelMatrix() */
	//__declspec(property(get = GetModelMatrix, put = SetModelMatrix)) matrix4 ModelMatrix;

	/*Sets the visibility of the OBB the AABB and the BS
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetVisible(bool a_bVisible);
	/* Property:
	SetVisibleOBB()*/
	//__declspec(property(put = SetVisible)) bool Visible;

	/*Sets the visibility of the OBB
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetVisibleOrigin(bool a_bVisible);
	/* Property:
	SetVisibleOBB()*/
	//__declspec(property(put = SetVisibleOrigin)) bool VisibleOrigin;
	
	/*Sets the visibility of the AABB
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetVisiblePivot(bool a_bVisible);
	/* Property:
	SetVisibleAABB()*/
	//__declspec(property(put = SetVisiblePivot)) bool VisiblePivot;

	/*Sets the visibility of the BS
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetVisibleCentroid(bool a_bVisible);
	/* Property:
	SetVisibleBS()*/
	//__declspec(property(put = SetVisibleCentroid)) bool VisibleCentroid;

	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetCentroid(vector3 a_v3Centroid);
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetPivot(vector3 a_v3Pivot);
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void SetSize(float a_fSize);

	/* Renders the bounding box
		Args:
			a_v3Color -> determinate the color of the box to be rendered, if REDEFAULT
			it will render the shape in the constructed color (white) */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddToRenderList(bool bForceDraw = false);

private:
	/* Released Memory and objects allocated. */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<AxisClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<AxisClass*>;

#endif //__AxisClass_H__