#pragma once
#include "raylib.h"

enum TurnId
{
		TurnPlayer0=0,
		TurnPlayer1
};

class TurnManager
{
	int turnnumb;
	enum TurnId turnid;

public:
	TurnManager();
	void NextTurn();
	TurnId GetCurantTurn();
};
