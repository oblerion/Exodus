#pragma once
#include "raylib.h"
#include "cart.hpp"
#include "player.hpp"
#include "turnManager.hpp"
#include "buttonText.hpp"

#define BoardHeight 6
#define BoardWidth 5
class Board
{
	ButtonText* btntxt;
	Cart _lstcart[BoardHeight][BoardWidth];
	Cart _cselect;
	Vector2 _pselect;
	Vector2 _posb[BoardHeight][BoardWidth];
	Cart* _Get(int x,int y);
	void _Set(int x,int y,Cart cart);
	// when player click on board
	void _Click(int x,int y,CartManager cartman);
	// when player release on board
	void _ReleaseClick(int x,int y,CartManager cartman);
	void _UITurn(TurnManager* turnmanager);
	void _UIBoard(TurnManager* turnmanager, CartManager cartman);
public:
	Board();
	void Select(Cart cart);
	void Deselect();
	void SetHand(TeamNumb team,int pos,Cart cart);
	void SetInvoc(TeamNumb team,int pos,Cart cart);
	Cart GetHand(TeamNumb team,int pos);
	Cart GetInvoc(TeamNumb team,int pos);
	TeamNumb GetTeam(int y);
	bool IsInvoc(int y,Cart cart);
	bool IsAttack(int x,int y,int x2,int y2);
	void DrawRange();
	void Draw(TurnManager* turnmanager,CartManager cartman);
};
