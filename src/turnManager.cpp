#include "turnManager.hpp"

TurnManager::TurnManager()
{
	turnnumb=0;
	turnid=TurnPlayer0;
}

void TurnManager::NextTurn()
{
	if(turnid==TurnPlayer0)
	{
		turnid = TurnPlayer1;
	}
	else if(turnid==TurnPlayer1)
	{
		turnid = TurnPlayer0;
	}
	turnnumb++;
}


TurnId TurnManager::GetCurantTurn()
{
	return turnid;
}



