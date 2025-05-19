#include "cartMonster.hpp"

CartMonster::CartMonster(std::string name,int level) :
Cart(name,CartTypeMonster,BLUE,GREEN)
{
	SetLevel(level);
}
