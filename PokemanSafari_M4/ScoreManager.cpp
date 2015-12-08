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

/////////////////////////////////////////////////////////////////
// Copy Constructor
/////////////////////////////////////////////////////////////////
ScoreManager::ScoreManager(ScoreManager const& other)
{
	//NOthing to do
}

/////////////////////////////////////////////////////////////////
//  Copy Assignment Operator
/////////////////////////////////////////////////////////////////
ScoreManager& ScoreManager::operator=(ScoreManager const& other)
{
	return *this;
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

/////////////////////////////////////////////////////////////////
// Release()  - release the objects memory
/////////////////////////////////////////////////////////////////
void ScoreManager::Release()
{
	for (int i = 0; i < scoreQueue.size(); i++)
	{
		if (scoreQueue[i] != nullptr)
			delete scoreQueue[i];
	}
	scoreQueue.clear();
	scoreObjects.clear();
}

/////////////////////////////////////////////////////////////////////
// Destructor
/////////////////////////////////////////////////////////////////////
ScoreManager::~ScoreManager()
{
	Release();
}

/////////////////////////////////////////////////////////////////////
// GetScore() - return the current score
/////////////////////////////////////////////////////////////////////
int ScoreManager::GetScore()
{
	return scoreCount;
}

/////////////////////////////////////////////////////////////////////
// GetReport() - UNIMPLEMETED
/////////////////////////////////////////////////////////////////////
void ScoreManager::GetReport()
{
	//render verbose stats of #of pokeman to screen/console
}

/////////////////////////////////////////////////////////////////////
// Update() - update scrolling score list
/////////////////////////////////////////////////////////////////////
void ScoreManager::Update()
{
	char buff[19];
	sprintf(buff, "Score: %d", scoreCount);
	m_pMeshMngr->PrintLine(buff, REYELLOW);

	for (std::vector<SCORE_MSG*>::iterator it = scoreQueue.begin();
		it != scoreQueue.end(); it++)
	{
		SCORE_MSG* msg = (*it);
		if (msg->TTL == 0) //If time is up dlete it
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
// AddScore() - add the given amount to the score total and list
//
// @param
//    scr - score amount
//    name - name of pokeman hit
/////////////////////////////////////////////////////////////////////
void ScoreManager::AddScore(int score, String name)
{
	scoreCount += score;
	scoreObjects.push_back(score);

	SCORE_MSG* msg = new SCORE_MSG;
	msg->TTL = 270;
	char buff[50];
	sprintf(buff, "+%d (%s)", score, name.c_str());
	msg->msg = buff;

	//If have 5 already remove first an push back
	if (scoreQueue.size() == 5)
	{
		delete *(scoreQueue.begin());
		scoreQueue.erase(scoreQueue.begin());
	}

	scoreQueue.push_back(msg);
}

/////////////////////////////////////////////////////////////////////
// DeductScore() - random score deduction based off objects
/////////////////////////////////////////////////////////////////////
void ScoreManager::DeductScore()
{
	int i = rand() % (scoreObjects.size() - 1);
	scoreCount -= scoreObjects.at(i);
	scoreObjects.erase(scoreObjects.begin()+i);
	//Add Score MSg...
}






