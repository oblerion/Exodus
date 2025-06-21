#include "cart.hpp"

Cart::Cart()
{
	_name = "";
	_type = CartTypeNULL;
	_effet = CartEffetNULL;
	_width= (GetScreenWidth()*0.8f)/5;
	_height=(GetScreenHeight()*0.8f)/6;
	_level = 1;
	_equipeffet = CartEffetNULL;
	_equiplevel = 0;
	_equipname = "";
	_range = 1;
}

Cart::Cart(SQLiteStatement stmt, int id) : Cart()
{
	stmt.Launch();
	_name = stmt.GetString("cart_name",id);
	switch(stmt.GetInt("type_id",id))
	{
		case CartTypeNULL:
			_type = CartTypeNULL;
		break;
		case CartTypeItem:
			_type = CartTypeItem;
			_col1 = GRAY;
			_col2 = WHITE;
		break;
		case CartTypeEquip:
			_type = CartTypeEquip;
			_col1 = MAGENTA;
			_col2 = YELLOW;
		break;
		case CartTypeMonster:
			_type = CartTypeMonster;
			_col1 = BLUE;
			_col2 = GREEN;
		break;
		default:;
	}
	switch(stmt.GetInt("effet_id",id))
	{
		case CartEffetNULL:
			_effet = CartEffetNULL;
		break;
		case CartObjHeal:
			_effet = CartObjHeal;
		break;
		case CartObjDamage:
			_effet = CartObjDamage;
		break;
		case CartEquipRange:
			_effet = CartEquipRange;
		break;
		case CartEquipDefence:
			_effet = CartEquipDefence;
		break;
		case CartEquipAttack:
			_effet = CartEquipAttack;
		break;
		default:;
	}
	_level = stmt.GetInt("cart_level",id);
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
	return _width;
}
int Cart::GetHeight()
{
	return _height;
}
enum CartEffet Cart::GetEquipEffet()
{
	return _equipeffet;
}
int Cart::GetEquipLevel()
{
	return _equiplevel;
}



bool Cart::Equip(Cart cart)
{
	if(cart.GetType()==CartTypeEquip &&
		_type==CartTypeMonster &&
		_equipeffet == CartEffetNULL)
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
		DrawRectangle(x-5,y+2,_width,_height/2,BLACK);
		DrawRectangleLines(x,y,_width,_height/2,_col1);
		DrawRectangleLines(x-5,y+2,_width,_height/2,_col2);
		DrawText(_name.c_str(),x+5,y+5,19,_col1);
		const char* slvl = TextFormat("lvl %d",_level);
		DrawText(slvl,x+5,y+22,19,_col1);
	}
}

void Cart::Draw(int x, int y)
{
	if(!IsNull())
	{
		DrawRectangle(x-5,y+2,_width,_height,BLACK);
		DrawRectangleLines(x,y,_width,_height,_col1);
		DrawRectangleLines(x-5,y+2,_width,_height,_col2);
		DrawText(_name.c_str(),x+5,y+5,19,_col1);
		const char* slvl = TextFormat("lvl %d",_level);
		DrawText(slvl,x+5,y+22,19,_col1);
		if(_equipeffet != CartEffetNULL)
		{
			const int my = y + GetHeight()/2;
			DrawRectangle(x-5,my+2,_width,_height/2,BLACK);
			DrawRectangleLines(x,my,_width,_height/2,MAGENTA);
			DrawRectangleLines(x-5,my+2,_width,_height/2,YELLOW);
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
		DrawRectangle(x,y,_width,_height,GRAY);
	}
}

void Cart::DrawBoardHand(int x, int y,bool bactive)
{
	if(IsNull())
	{
		DrawRectangle(x,y,_width,_height,DARKGRAY);
		if(bactive)
			DrawText("generate card",x+5,y+5,19,WHITE);
	}
}

CartItem::CartItem(enum CartEffet effet) :
Cart("",CartTypeItem,GRAY,WHITE)
{
	std::string lname="";
	switch(effet)
	{
		case CartObjHeal: lname="potion";
		break;
		case CartObjDamage: lname="fire ball";
		break;
		default:;
	}
	SetName(lname);
	SetEffet(effet);
}

CartEquip::CartEquip(enum CartEffet effet) :
Cart("",CartTypeEquip,MAGENTA,YELLOW)
{

	std::string lname = "";
	switch(effet)
	{
		case CartEquipDefence : lname = "shield";
		break;
		case CartEquipAttack : lname = "sword";
		break;
		case CartEquipRange : lname = "bow";
		break;
		default:;
	}
	SetName(lname);
	SetEffet(effet);

}

CartMonster::CartMonster(std::string name,int level) :
Cart(name,CartTypeMonster,BLUE,GREEN)
{
	SetLevel(level);
}

CartManager::CartManager(SQLiteManager* pdbman)
{
	dbman = pdbman;
}

Cart CartManager::_findCart(CartType itype, int plevel)
{
	Cart rc;

	SQLiteStatement* stmt = dbman->LoadStatement("getCarts");

	for(int i=0;i<stmt->Size();i++)
	{
		Cart lc = Cart(*stmt,i);
		if(lc.GetLevel()==plevel &&
			lc.GetType()==itype
		)
		{
			rc = lc;
			break;
		}
	}
	return rc;
}

#define LUCKPOUR(p) (GetRandomValue(0,100) < p)
Cart CartManager::Generate()
{
	Cart c;
	SQLiteStatement* stmt = dbman->LoadStatement("getOrderGenerate");
	for(int i=0;i<stmt->Size();i++)
	{
		int fg = (int)(stmt->GetFloat("cart_generate",i)*100);
		if(LUCKPOUR(fg))
		{
			c = Cart(*stmt,i);
			break;
		}
	}
	return c;
}

bool CartManager::Fusion(Cart* pcart, Cart seccart)
{
	bool rb = false;
	if(pcart->GetType()==seccart.GetType() &&
		pcart->GetName()==seccart.GetName()
	)
	{
		if(pcart->GetType()==CartTypeMonster)
		{
			Cart fcart = _findCart(CartTypeMonster,pcart->GetLevel()+1);
			if(!fcart.GetName().empty())
			{
				//*pcart = fcart;
				pcart->SetLevel(pcart->GetLevel()+1);
				pcart->SetName(fcart.GetName());
				rb = true;
			}
		}
		else
		{
			pcart->SetLevel(pcart->GetLevel()+seccart.GetLevel());
			rb = true;
		}
	}
	return rb;
}


