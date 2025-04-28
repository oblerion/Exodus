#pragma once
#include "raylib.h"
#include <string>
#include <vector>

enum CartType
{
    CartTypeNULL,
    CartTypeItem,
    CartTypeEquip,
    CartTypeMonster
};
enum CartEffet
{
    CartEffetNULL,
    CartEffetLevelUp,
    CartEffetLevelDown,
    CartEffetHeal,
    CartEffetDamage
};
class Cart
{
    std::string _name;
    enum CartType _type;
    Cart* _subcart;
    int _level;
    float _w;
    float _h;
    Color _col1;
    Color _col2;
    public:
    Cart();
    Cart(std::string name,enum CartType type,Color pcol1,Color pcol2);
    bool IsNull();
    std::string GetName();
    enum CartType GetType();
    int GetLevel();
    void SetLevel(int level);
    int GetWidth();
    int GetHeight();
    void SetSubCart(Cart cart);
    void Fuse(Cart cart);
    void MiniDraw(int x,int y);
    void Draw(int x,int y);
    void DrawBoardHand(int x,int y);
    void DrawBoard(int x,int y);
};

class CartItem : public Cart
{
    public:
    CartItem(std::string name);
};

class CartEquip : public Cart
{
    public:
    CartEquip(std::string name);
};

class CartMonster : public Cart 
{
    public:
    CartMonster(std::string name);
};
#define BoardHeight 6
#define BoardWidth 5
class Board
{
    Cart _lstcart[BoardHeight][BoardWidth];
    Cart _cselect;
    Vector2 _posb[BoardHeight][BoardWidth];
    Cart* _Get(int x,int y);
    void _Set(int x,int y,Cart cart);
    public:
    Board();
    void Select(Cart cart);
    void Deselect();
    void SetHand(int team,int pos,Cart cart);
    void SetEquip(int team,int pos,Cart cart);
    void SetInvoc(int team,int pos,Cart cart);
    Cart GetHand(int team,int pos);
    Cart GetEquip(int team,int pos);
    Cart GetInvoc(int team,int pos);
    void Draw();
};

class Exodus
{
    Board _board;
    public:
    Exodus();
    void Draw();
};
