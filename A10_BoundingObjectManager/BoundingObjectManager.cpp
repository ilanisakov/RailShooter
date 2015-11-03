/////////////////////////////////////////////////////////////////////
// File: BoundingObjectManager.cpp
// DSA2 A10_BoundingObjectManager
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////

#include "BoundingObjectManager.h"
#include "AppClass.h"

BoundingObjectManager* BoundingObjectManager::inst = nullptr;

//Private Constructor
BoundingObjectManager::BoundingObjectManager()
{
	//TODO......

}
//Get instance of camera
BoundingObjectManager* BoundingObjectManager::GetInstance()
{
	if (inst == nullptr)
	{
		inst = new BoundingObjectManager();
	}
	return inst;
}
//Release the camera singleton instance
void BoundingObjectManager::ReleaseInst()
{
	if (inst != nullptr)
	{
		delete inst;
		inst = nullptr;
	}
}










