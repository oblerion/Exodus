#pragma once
#include "raylib.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include "cart.hpp"
#include "cartItem.hpp"
#include "cartEquip.hpp"
#include "cartMonster.hpp"
#include "player.hpp"
#include "board.hpp"
#include "turnManager.hpp"

class Exodus
{
    TurnManager _turnmanager;
    Player _players[2];
    Board _board;
public:
    Exodus();
    void Draw();
};
