#pragma once
#include "raylib.h"
#define MaxHp 100

enum TeamNumb
{
	TeamNULL,
	Team1,
	Team2
};

class Player
{
	TeamNumb team;
	int hp;
public:
	Player();
	Player(TeamNumb team);
	void DrawHpBare(int x,int y);
};
