#include "button.hpp"

Button::Button(float x,float y,float w,float h)
{
	timer = 0;
	rect = {x,y,w,h};
	active=true;
	state = ButtonDefault;
}

bool Button::IfSelect()
{
	return state==ButtonSelect;
}

Rectangle Button::GetRect()
{
	return rect;
}

void Button::Reset()
{
	active=true;
	state = ButtonDefault;
}

enum ButtonState Button::Draw()
{
	if(timer>0)
		timer -= GetFrameTime();

	if(active)
	{
		if(CheckCollisionRecs(rect,
			(Rectangle){(float)GetMouseX(),(float)GetMouseY(),10,10}))
		{
			state = ButtonSelect;
			if(IsMouseButtonDown(0) && timer<=0){
				state = ButtonPress;
				timer = 0.5f;
			}
		}
		else
			state = ButtonDefault;
	}
	return state;
}
