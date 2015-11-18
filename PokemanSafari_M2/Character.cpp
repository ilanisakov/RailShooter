/////////////////////////////////////////////////////////////////////
// File: Character.cpp
// DSA2 PokemanSafari_M1
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////

#include "Character.h"

/////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////
Character::Character(CHARACTER_TYPE type, String name, float time,
	std::vector<vector3> movementPath) : MyEntityClass(name)
{
	this->path = movementPath; // path for the character
	this->charType = type;
	this->lapTime = time;
	this->currentSeg = 0; //current line segment of the track 
	this->m_v3Position = path[0];
	this->totalDistance = 0;
	
	//getting the magnitudes of the paths
	float x, y, z, mag;
	nextIt = path.begin() + 1;
	for (it = path.begin(); it != path.end(); ++it){
		x = nextIt->x - it->x;
		y = nextIt->y - it->y;
		z = nextIt->z - it->z;
		mag = sqrt(x * x + y * y + z * z);
		pathDirection.push_back(vector3(x/mag, y/mag, z/mag));
		totalDistance = totalDistance + mag;
		++nextIt;
		if (nextIt == path.end())
			nextIt = path.begin();
	}

	//getting constant track speed
	this->speed = totalDistance / (lapTime * 60);

	it = path.begin();
	dirIt = pathDirection.begin();
	nextIt = path.begin() + 1;
	if (nextIt == path.end())
		nextIt = path.begin();
}

/////////////////////////////////////////////////////////////////
// Render()
/////////////////////////////////////////////////////////////////
void Character::UpdateRender()
{

}
/////////////////////////////////////////////////////////////////
// UpdateLocation()
/////////////////////////////////////////////////////////////////
void Character::UpdateLocation(){

	m_v3Velocity = vector3(dirIt->x * speed, dirIt->y * speed, dirIt->z * speed);
	
	//MyEntityClass's Update
	Update();

	//checking if it's time to move onto the next path segment
	if (m_v3Position.x >= nextIt->x - offset && m_v3Position.x <= nextIt->x + offset){
		if (m_v3Position.y >= nextIt->y - offset && m_v3Position.y <= nextIt->y + offset){
			if (m_v3Position.z >= nextIt->z - offset && m_v3Position.z <= nextIt->z + offset){
				std::cout << "SWITCH" << std::endl;
				it++;
				if (it == path.end())
					it = path.begin();
				dirIt++;
				if (dirIt == pathDirection.end())
					dirIt = pathDirection.begin();
				nextIt++;
				if (nextIt == path.end())
					nextIt = path.begin();
			}
		}
	}
}
/////////////////////////////////////////////////////////////////
// GetLocation()
/////////////////////////////////////////////////////////////////
vector3 Character::GetLocation(void){
	return m_v3Position;
}




