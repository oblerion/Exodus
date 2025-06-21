#pragma once
#include <string>
#include "raylib.h"
#include "SQLiteManager.hpp"

enum CartType
{
	CartTypeNULL=0,
	CartTypeItem,
	CartTypeEquip,
	CartTypeMonster
};
enum CartEffet
{
	CartEffetNULL=1,
	CartObjHeal,
	CartObjDamage,
	CartEquipRange,
	CartEquipDefence,
	CartEquipAttack
};
class Cart
{
	std::string _name;
	enum CartType _type;
	enum CartEffet _effet;
	enum CartEffet _equipeffet;
	int _equiplevel;
	std::string _equipname;
	int _level;
	float _width;
	float _height;
	Color _col1;
	Color _col2;
	int _range;
public:

	Cart();
	Cart(SQLiteStatement stmt, int id);
	Cart(std::string name,enum CartType type,Color pcol1,Color pcol2);
	bool IsExist();
	bool IsNull();
	std::string GetName();
	void SetName(std::string pname);
	enum CartType GetType();
	int GetLevel();
	void SetLevel(int level);
	enum CartEffet GetEffet();
	void SetEffet(enum CartEffet effet);
	int GetWidth();
	int GetHeight();
	enum CartEffet GetEquipEffet();
	int GetEquipLevel();
	bool Equip(Cart cart);
	void UnEquip();
	void MiniDraw(int x,int y);
	void Draw(int x,int y);
	void DrawBoardHand(int x,int y,bool bactive);
	void DrawBoard(int x,int y);
};
class CartItem : public Cart
{
public:
	CartItem(enum CartEffet effet);
};

class CartEquip : public Cart
{
public:
	CartEquip(enum CartEffet effet);
};

class CartMonster : public Cart
{
public:
	CartMonster(std::string name,int level);
};

class CartManager
{
	SQLiteManager* dbman;
	Cart _findCart(CartType itype,int plevel);
public:
	CartManager(SQLiteManager* pdbman);
	Cart Generate();
	bool Fusion(Cart* pcart,Cart seccart);
	bool Equip(Cart* pcart,Cart seccart);

};
