/////////////////////////////////////////////////////////////////////
// File: ScoreManager.cpp
// DSA2 PokemanSafari_M1
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////

#include "ScoreManager.h"

ScoreManager* ScoreManager::inst = nullptr;

/////////////////////////////////////////////////////////////////////
//  ScoreManager() - Private singleton constructor
/////////////////////////////////////////////////////////////////////
ScoreManager::ScoreManager()
{
	scoreCount = 0;
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}

/////////////////////////////////////////////////////////////////////
// GetInstance() - return the singleton inst of BO manager
/////////////////////////////////////////////////////////////////////
ScoreManager* ScoreManager::GetInstance()
{
	if (inst == nullptr)
	{
		inst = new ScoreManager();
	}
	return inst;
}

/////////////////////////////////////////////////////////////////////
// ReleaseInst() - Release the Score manager singleton instance
/////////////////////////////////////////////////////////////////////
void ScoreManager::ReleaseInst()
{
	if (inst != nullptr)
	{
		delete inst;
		inst = nullptr;
	}
}

/////////////////////////////////////////////////////////////////////
// ~ScoreManager()
/////////////////////////////////////////////////////////////////////
ScoreManager::~ScoreManager()
{
	ReleaseInst();
}

/////////////////////////////////////////////////////////////////////
// GetScore()
/////////////////////////////////////////////////////////////////////
int ScoreManager::GetScore()
{
	return scoreCount;
}

/////////////////////////////////////////////////////////////////////
// GetReport()
/////////////////////////////////////////////////////////////////////
void ScoreManager::GetReport()
{
	//render verbose stats of #of pokeman to screen/console
}

void ScoreManager::Update()
{
	char buff[19];
	sprintf(buff, "Score: %d", scoreCount);
	m_pMeshMngr->PrintLine(buff, REYELLOW);

	for (std::vector<SCORE_MSG*>::iterator it = scoreQueue.begin();
		it != scoreQueue.end(); it++)
	{
		SCORE_MSG* msg = (*it);
		if (msg->TTL == 0)
		{

			delete (*it);
			scoreQueue.erase(it);

			break;
		}
		else
		{
			msg->TTL--;
			m_pMeshMngr->PrintLine(msg->msg, REGREEN);
		}
	}
}

/////////////////////////////////////////////////////////////////////
// Increment()
/////////////////////////////////////////////////////////////////////
void ScoreManager::Increment()
{
	scoreCount++;
}

void ScoreManager::AddScore(int score, String name)
{
	scoreCount += score;
	scoreObjects.push_back(score);

	SCORE_MSG* msg = new SCORE_MSG;
	msg->TTL = 270;
	char buff[50];
//TODO - fix name in manager
	//sprintf(buff, "+%d (%s)", score, name.c_str());
	sprintf(buff, "+%d (%s)", score, "Pokeman");
	msg->msg = buff;

	if (scoreQueue.size() == 5)
	{
		delete *(scoreQueue.begin());
		scoreQueue.erase(scoreQueue.begin());
	}

	scoreQueue.push_back(msg);
}

void ScoreManager::DeductScore()
{
	int i = rand() % (scoreObjects.size() - 1);
	scoreCount -= scoreObjects.at(i);
	scoreObjects.erase(scoreObjects.begin()+i);
}

/////////////////////////////////////////////////////////////////////
// CaughtPokeman()
/////////////////////////////////////////////////////////////////////
//void ScoreManager::CaughtPokeman(Character* c)
//{
//	//make a score object?
//	//update based on character stats
//}

/////////////////////////////////////////////////////////////////////
// HitSpaceship()
/////////////////////////////////////////////////////////////////////
//void ScoreManager::HitSpaceship(Character *c)
//{
//	//increment score
//	//decrement damage on ship?
//	//if 0 destory it?
//}

/////////////////////////////////////////////////////////////////////
// NetAttack()
/////////////////////////////////////////////////////////////////////
void ScoreManager::NetAttack()
{
	//randomly remove a score object(for a pokeman)
}






