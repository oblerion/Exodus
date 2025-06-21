#include "buttonText.hpp"

ButtonText::ButtonText(float x, float y, std::string ptext, int size, Color pcolor) :
Button(x,y,(float)MeasureText(ptext.c_str(),size),size)
{
	sizefont = size;
	text = ptext;
	color = pcolor;
}


enum ButtonState ButtonText::Draw()
{
	enum ButtonState state = Button::Draw();
	Rectangle r = GetRect();
	DrawRectangleRec(r,color);
	if(state==ButtonSelect)
		DrawText(text.c_str(),(int)r.x,(int)r.y,sizefont,BLACK);
	else
		DrawText(text.c_str(),(int)r.x,(int)r.y,sizefont,WHITE);
	return state;
}

