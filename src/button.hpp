#pragma once
#include "raylib.h"


class Button
{
	Rectangle rect;
	bool active;
	bool select;
public:
	Button(float x,float y,float w,float h);
	bool IfSelect();
	void Reset();
	Rectangle GetRect();
	bool Draw();
};
