#pragma once
#include <string>
#include "raylib.h"


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
	float _w;
	float _h;
	Color _col1;
	Color _col2;
public:
	Cart();
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
	bool Fuse(Cart cart);
	bool Equip(Cart cart);
	void UnEquip();
	void MiniDraw(int x,int y);
	void Draw(int x,int y);
	void DrawBoardHand(int x,int y);
	void DrawBoard(int x,int y);
};
