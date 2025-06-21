#pragma once
#include "raylib.h"


enum ButtonState
{
	ButtonDefault,
	ButtonSelect,
	ButtonPress
};

class Button
{
	float timer;
	Rectangle rect;
	bool active;
	enum ButtonState state;
public:
	Button(float x,float y,float w,float h);
	bool IfSelect();
	void Reset();
	Rectangle GetRect();
	enum ButtonState Draw();
};
