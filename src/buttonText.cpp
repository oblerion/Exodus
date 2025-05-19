#include "buttonText.hpp"

ButtonText::ButtonText(float x, float y, std::string ptext, int size, Color pcolor) :
Button(x,y,(float)MeasureText(ptext.c_str(),size)*size,size)
{
	sizefont = size;
	text = ptext;
	color = pcolor;
}


bool ButtonText::Draw()
{
	bool rb = Button::Draw();

	Rectangle r = GetRect();
	DrawRectangleRec(r,color);
	DrawText(text.c_str(),(int)r.x,(int)r.y,sizefont,WHITE);
	return rb;
}

