#include "player.hpp"

Player::Player()
{
	team = TeamNULL;
	hp = 0;
}

Player::Player(enum TeamNumb team)
{
	this->team = team;
	hp = MaxHp;
}
void Player::DrawHpBare(int x, int y)
{
	const float per = hp/MaxHp;
	const int bheight = (GetRenderHeight()/2)-10;
	Color col = GREEN;
	const int offy = (1-per)*bheight;
	if(per<0.3) col = RED;
	else if(per<0.5) col = ORANGE;
	DrawRectangleLines(x,y,20,bheight,GRAY);
	DrawRectangleLines(x,y+offy,20,bheight*per,col);
	DrawTextPro(GetFontDefault(),
				TextFormat("Hp: %d",(int)(per*MaxHp)),
				{(float)x,(float)y+(GetRenderHeight()/4)-10},{0,0},-90,20,0.5,WHITE
	);
}
