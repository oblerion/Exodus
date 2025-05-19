#pragma once
#include <string>
#include "button.hpp"

class ButtonText : public Button
{
	std::string text;
	int sizefont;
	Color color;

public:
	ButtonText(float x,float y,std::string ptext,int size,Color pcolor);
	bool Draw();
};
