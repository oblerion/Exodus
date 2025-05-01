#pragma once
#include <vector>
#include "exodus.hpp"

const std::vector<Cart> cartitem = {
    CartItem(CartObjHeal)
};

const std::vector<Cart> cartequip = {
    CartEquip(CartEquipDefence),
    CartEquip(CartEquipAttack)
};

const std::vector<Cart> cartmonster = {
    CartMonster("sheep",1),
    CartMonster("wolf",2)
};
