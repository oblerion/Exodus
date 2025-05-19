#include "cart.hpp"

Cart::Cart()
{
	_name = "";
	_type = CartTypeNULL;
	_effet = CartEffetNULL;
	_w = (GetScreenWidth()*0.8f)/5;
	_h = (GetScreenHeight()*0.8f)/6;
	_level = 1;
	_equipeffet = CartEffetNULL;
	_equiplevel = 0;
	_equipname = "";
}
Cart::Cart(std::string pname,enum CartType ptype,Color pcol1,Color pcol2) : Cart()
{
	_name=pname;
	_type=ptype;
	_col1 = pcol1;
	_col2 = pcol2;
}
bool Cart::IsExist()
{
	return _type != CartTypeNULL;
}

bool Cart::IsNull()
{
	return _type == CartTypeNULL;
}

std::string Cart::GetName()
{
	return _name;
}
void Cart::SetName(std::string pname)
{
	_name = pname;
}


enum CartType Cart::GetType()
{
	return _type;
}

int Cart::GetLevel()
{
	return _level;
}
void Cart::SetLevel(int level)
{
	_level = level;
}
enum CartEffet Cart::GetEffet()
{
	return _effet;
}
void Cart::SetEffet(enum CartEffet effet)
{
	_effet = effet;
}


int Cart::GetWidth()
{
	return _w;
}
int Cart::GetHeight()
{
	return _h;
}
enum CartEffet Cart::GetEquipEffet()
{
	return _equipeffet;
}
int Cart::GetEquipLevel()
{
	return _equiplevel;
}


bool Cart::Fuse(Cart cart)
{
	if(cart.GetType()==_type &&
		cart.GetName()==_name)
	{
		if(GetType()!=CartTypeMonster)
		{
			SetLevel(cart.GetLevel()+_level);
		}
		else
		{
			if(GetEquipEffet()==CartEffetNULL &&
				cart.GetEquipEffet()==CartEffetNULL
			)
			{
				if(GetName()=="sheep")
				{
					SetName("wolf");
					SetLevel(2);
				}
				else if(GetName()=="wolf")
				{
					SetName("cerberus");
					SetLevel(3);
				}
				else if(GetName()=="cerberus")
				{
					SetName("minautor");
					SetLevel(4);
				}
			}
			else return false;

		}
		return true;
	}
	return false;
}
bool Cart::Equip(Cart cart)
{
	if(cart.GetType()==CartTypeEquip &&
		GetType()==CartTypeMonster)
	{
		_equipeffet = cart.GetEffet();
		_equiplevel = cart.GetLevel();
		_equipname = cart.GetName();
		return true;
	}
	return false;
}
void Cart::UnEquip()
{
	_equipeffet=CartEffetNULL;
	_equiplevel=0;
	_equipname = "";
}

void Cart::MiniDraw(int x, int y)
{
	if(!IsNull())
	{
		DrawRectangle(x-5,y+2,_w,_h/2,BLACK);
		DrawRectangleLines(x,y,_w,_h/2,_col1);
		DrawRectangleLines(x-5,y+2,_w,_h/2,_col2);
		DrawText(_name.c_str(),x+5,y+5,19,_col1);
		const char* slvl = TextFormat("lvl %d",_level);
		DrawText(slvl,x+5,y+22,19,_col1);
	}
}

void Cart::Draw(int x, int y)
{
	if(!IsNull())
	{
		DrawRectangle(x-5,y+2,_w,_h,BLACK);
		DrawRectangleLines(x,y,_w,_h,_col1);
		DrawRectangleLines(x-5,y+2,_w,_h,_col2);
		DrawText(_name.c_str(),x+5,y+5,19,_col1);
		const char* slvl = TextFormat("lvl %d",_level);
		DrawText(slvl,x+5,y+22,19,_col1);
		if(_equipeffet != CartEffetNULL)
		{
			const int my = y + GetHeight()/2;
			DrawRectangle(x-5,my+2,_w,_h/2,BLACK);
			DrawRectangleLines(x,my,_w,_h/2,MAGENTA);
			DrawRectangleLines(x-5,my+2,_w,_h/2,YELLOW);
			DrawText(_equipname.c_str(),x+5,my+5,19,MAGENTA);
			const char* slvl = TextFormat("lvl %d",_equiplevel);
			DrawText(slvl,x+5,my+22,19,MAGENTA);
		}
	}
}

void Cart::DrawBoard(int x, int y)
{
	if(IsNull())
	{
		DrawRectangle(x,y,_w,_h,GRAY);
	}
}

void Cart::DrawBoardHand(int x, int y)
{
	if(IsNull())
	{
		DrawRectangle(x,y,_w,_h,DARKGRAY);
		DrawText("generate card",x+5,y+5,19,WHITE);
	}
}
