#include "button.hpp"

Button::Button(float x,float y,float w,float h)
{
	rect = {x,y,w,h};
	active=true;
	select=false;
}

bool Button::IfSelect()
{
	return select;
}

Rectangle Button::GetRect()
{
	return rect;
}

void Button::Reset()
{
	active=true;
	select=false;
}

bool Button::Draw()
{
	if(active)
	{
		if(CheckCollisionRecs(rect,
			(Rectangle){(float)GetMouseX(),(float)GetMouseY(),10,10}))
		{
			select=true;
			if(IsMouseButtonDown(0))
				return true;
		}
		else
			select=false;
	}
	return false;
}
