#include"cartItem.hpp"

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
