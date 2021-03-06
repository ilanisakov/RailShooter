/////////////////////////////////////////////////////////////////////
// File: Projectile.h
// DSA2 PokemanSafari_M1
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////

#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "MyBoundingObjectClass.h"

typedef enum {
	PJ_POKECUBE, PJ_ROCK, PJ_NET
} PROJECTILE_TYPE;

class Projectile : public MyBoundingObjectClass
{
public:
	PROJECTILE_TYPE projType;

	/////////////////////////////////////////////////////////////////
	// Constructor
	/////////////////////////////////////////////////////////////////
	Projectile(PROJECTILE_TYPE type, String name, std::vector<vector3> a_lVectorList);

	/////////////////////////////////////////////////////////////////
	// Render()
	/////////////////////////////////////////////////////////////////
	void UpdateRender();

private:


};












#endif /*_PROJECTILE_H_*/
