#pragma once
#include "raylib.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include "cart.hpp"
#include "player.hpp"
#include "board.hpp"
#include "turnManager.hpp"
#include "SQLiteManager.hpp"

#define EXODUS_VERSION "earlybuild 0.1"

class Exodus
{
    bool _dbIsLoad;
    SQLiteManager* _sqlitemanager;
    TurnManager _turnmanager;
    CartManager* _cartmanager;
    Player _players[2];
    Board _board;
public:
    Exodus();
    ~Exodus();
    bool DbIsLoad();
    void DrawCartExplorer();
    void Draw();
};
