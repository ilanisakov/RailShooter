/////////////////////////////////////////////////////////////////////
// File: Character.h
// DSA2 PokemanSafari_M1
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "MyEntityClass.h"

typedef enum {
	CT_POKEMAN, CT_PLAYER, CT_SPACESHIP
} CHARACTER_TYPE;

class Character : public MyEntityClass
{
public:
	CHARACTER_TYPE charType;

	/////////////////////////////////////////////////////////////////
	// Constructor
	/////////////////////////////////////////////////////////////////
	Character(CHARACTER_TYPE type, String name, float time, std::vector<vector3> movementPath);

	/////////////////////////////////////////////////////////////////
	// Render()
	/////////////////////////////////////////////////////////////////
	void UpdateRender();

	void UpdateLocation();

	vector3 GetLocation(void);

	//TODO
	//Handle character path, stats updates here?...
	
private:
	std::vector<vector3>::iterator nextIt;
	std::vector<vector3> path;
	std::vector<vector3> pathDirection;
	std::vector<vector3>::iterator it;
	
	std::vector<vector3>::iterator dirIt;
	
	int currentSeg;
	float lapTime;
	float totalDistance;
	float speed;
	const float offset = 1.0f;
};







#endif   /* _CHARACTER_H_*/


