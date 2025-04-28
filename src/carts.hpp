#pragma once
#include <map>
#include "exodus.hpp"

const std::map<std::string,Cart> cartitem = {
{"potion",CartItem("potion")}
};

const std::map<std::string,Cart> cartequip = {
    {"shield",CartEquip("shield")}
};

const std::map<std::string,Cart> cartmonster = {
    {"wolf",CartItem("wolf")}
};
