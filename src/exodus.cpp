#include "exodus.hpp"

#define dbpath "db/exodus.db"

Exodus::Exodus()
{
    _players[0] = Player(Team1);
    _players[1] = Player(Team2);
    srand(time(0));
    if(IsPathFile(dbpath))
    {
        _sqlitemanager = new SQLiteManager(dbpath);
        _dbIsLoad = true;
          _sqlitemanager->CreateStatement("getCarts",
                                "SELECT * FROM carts");
        _sqlitemanager->CreateStatement("getCartsLVL1",
                                    "SELECT * FROM carts WHERE cart_level=1;");
        for(int i=1;i<10;i++)
            _sqlitemanager->CreateStatement(
                "getCartsMonsterLVL"+std::to_string(i),
                "SELECT * FROM carts WHERE cart_level="+std::to_string(i)+" AND type_id=3;");

        _sqlitemanager->CreateStatement("getCartObject",
                                    "SELECT * FROM carts WHERE type_id=1;");
        _sqlitemanager->CreateStatement("getCartEquip",
                                    "SELECT * FROM carts WHERE type_id=2;");
        _sqlitemanager->CreateStatement("getCartMonster",
                                    "SELECT * FROM carts WHERE type_id=3;");
        _sqlitemanager->CreateStatement("getOrderGenerate",
                                    "SELECT * FROM carts WHERE cart_generate>0 ORDER BY cart_generate DESC;");
        _cartmanager = new CartManager(_sqlitemanager);
    }
    else
    {
        _sqlitemanager = new SQLiteManager("");
        printf("ERROR : %s not found\n",dbpath);
        _dbIsLoad = false;
    }
    //--------------------------------------------------------
   
    //--------------------------------------------------------


}
bool Exodus::DbIsLoad()
{
    return _dbIsLoad;
}


void Exodus::DrawCartExplorer()
{
    if(_dbIsLoad)
    {
        DrawText("Card browser",GetRenderWidth()/2-MeasureText("Card browser",20)/2,5,20,WHITE);
        int lx,ly;
        lx = 10;
        ly = 30;

        std::string lrqs[3] = {"getCartObject","getCartEquip","getCartMonster"};
        for(int nv=0;nv<3;nv++)
        {
            SQLiteStatement* stmt = _sqlitemanager->LoadStatement(lrqs[nv]);
            for(int i=0;i<stmt->Size();i++)
            {
                Cart c = Cart(*stmt,i);
                const int w = c.GetWidth()+5;
                const int h = c.GetHeight()+5;
                c.Draw(lx,ly);
                if(lx>w*5) {lx=10; ly+=h;}
                else lx+=w;
            }
        }
    /*
    for(int i=0;i<(int)_lstcarts[1].size();i++)
    {
        _lstcarts[1][i].Draw(lx,ly);
        if(lx>w*5) {lx=10; ly+=h;}
        else lx+=w;
    }
    for(int i=0;i<(int)_lstcarts[2].size();i++)
    {
        _lstcarts[2][i].Draw(lx,ly);
        if(lx>w*5) {lx=10; ly+=h;}
        else lx+=w;
    }*/
    }
}


void Exodus::Draw()
{
    if(_dbIsLoad)
    {
        _board.Draw(&_turnmanager,*_cartmanager);
        _players[0].DrawHpBare(3,1);
        _players[1].DrawHpBare(3,(GetRenderHeight()/2)+9);
    }
   // _turnmanager.NextTurn();
}

Exodus::~Exodus()
{
    _sqlitemanager->Close();
    delete _sqlitemanager;
}


