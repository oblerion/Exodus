#include "exodus.hpp"


Exodus::Exodus()
{
    _players[0] = Player(Team1);
    _players[1] = Player(Team2);
    srand(time(0));
}

void Exodus::Draw()
{
    _board.Draw(_turnmanager);
    _players[0].DrawHpBare(3,1);
    _players[1].DrawHpBare(3,(GetRenderHeight()/2)+9);

   // _turnmanager.NextTurn();


}

