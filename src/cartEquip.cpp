#include "cartEquip.hpp"

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
