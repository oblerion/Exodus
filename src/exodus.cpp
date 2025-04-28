#include "exodus.hpp"

Cart::Cart()
{
    _name = "";
    _type = CartTypeNULL;
    _w = (GetScreenWidth()*0.8f)/5;
    _h = (GetScreenHeight()*0.8f)/6;
    _level = 1;
}
Cart::Cart(std::string pname,enum CartType ptype,Color pcol1,Color pcol2) : Cart()
{
    _name=pname;
    _type=ptype;
    _col1 = pcol1;
    _col2 = pcol2;
}
bool Cart::IsNull()
{
    return _type==CartTypeNULL;
}

std::string Cart::GetName()
{
    return _name;
}

enum CartType Cart::GetType()
{
    return _type;
}

int Cart::GetLevel()
{
    return _level;
}
void Cart::SetLevel(int level)
{
    _level = level;
}


int Cart::GetWidth()
{
    return _w;
}
int Cart::GetHeight()
{
    return _h;
}


void Cart::Fuse(Cart cart)
{
    if(cart.GetType()==_type && cart.GetName()==_name)
    {
        SetLevel(cart.GetLevel()+_level);
    }
}

void Cart::MiniDraw(int x, int y)
{
    if(!IsNull())
    {
        DrawRectangle(x-5,y+2,_w,_h/2,BLACK);
        DrawRectangleLines(x,y,_w,_h/2,_col1);
        DrawRectangleLines(x-5,y+2,_w,_h/2,_col2);
        DrawText(_name.c_str(),x+5,y+5,19,_col1);
        const char* slvl = TextFormat("lvl %d",_level);
        DrawText(slvl,x+5,y+22,19,_col1);
    }
}

void Cart::Draw(int x, int y)
{
    if(!IsNull())
    {
        DrawRectangle(x-5,y+2,_w,_h,BLACK);
        DrawRectangleLines(x,y,_w,_h,_col1);
        DrawRectangleLines(x-5,y+2,_w,_h,_col2);
        DrawText(_name.c_str(),x+5,y+5,19,_col1);
        const char* slvl = TextFormat("lvl %d",_level);
        DrawText(slvl,x+5,y+22,19,_col1);
    }
}

void Cart::DrawBoard(int x, int y)
{
    if(IsNull())
    {
        DrawRectangle(x,y,_w,_h,GRAY);
    }
}

void Cart::DrawBoardHand(int x, int y)
{
    if(IsNull())
    {
        DrawRectangle(x,y,_w,_h,DARKGRAY);
    }
}



CartItem::CartItem(std::string name) :
Cart(name,CartTypeItem,GRAY,WHITE)
{

}


CartEquip::CartEquip(std::string name) :
Cart(name,CartTypeEquip,MAGENTA,YELLOW)
{

}
CartMonster::CartMonster(std::string name) :
Cart(name,CartTypeMonster,BLUE,GREEN)
{

}


Cart* Board::_Get(int x, int y)
{
    return &(_lstcart[y][x]);
}
void Board::_Set(int x, int y, Cart cart)
{
    _lstcart[y][x]=cart;
}

Board::Board()
{
    Cart c;
    for(int iy=0;iy<BoardHeight;iy++)
    {
        for(int ix=0;ix<BoardWidth;ix++)
        {
            _posb[iy][ix] = {
                (float)60+(ix*(c.GetWidth()+20)),
                (float)50+(iy*(c.GetHeight()+10))
            };
        }
    }
}
void Board::Select(Cart cart)
{
    _cselect = cart;
}
void Board::Deselect()
{
    _cselect = Cart();
}


void Board::SetHand(int team, int pos, Cart cart)
{
    _lstcart[0+(team*3)][pos] = cart;
}

void Board::SetEquip(int team, int pos, Cart cart)
{
    _lstcart[1+(team*3)][pos] = cart;
}

void Board::SetInvoc(int team, int pos, Cart cart)
{
    _lstcart[2+(team*3)][pos] = cart;
}
Cart Board::GetHand(int team, int pos)
{
    return _lstcart[0+(team*3)][pos];
}
Cart Board::GetEquip(int team, int pos)
{
    return  _lstcart[1+(team*3)][pos];
}
Cart Board::GetInvoc(int team, int pos)
{
    return _lstcart[2+(team*3)][pos];
}
Cart Board::Generate()
{
    int r = GetRandomValue(0,2);
    if(r==0) return CartItem("potion");
    else if(r==1) return CartEquip("sword");
    else if(r==2) return CartMonster("wolf");
    return Cart();
}


bool collide(int x,int y,int w,int h,int x2,int y2,int w2,int h2)
{
    if(x<x2+w2 && y<y2+h2 && x2<x+w && y2<y+h) return true;
    return false;
}
void Board::Draw()
{
    for(int j=0;j<BoardHeight;j++)
    for(int i=0;i<BoardWidth;i++)
    {
        Cart c = *_Get(i,j);
        Vector2 pos = _posb[j][i];

        if(j>2)
        {
            if(collide( pos.x,
                pos.y,c.GetWidth(),c.GetHeight(),GetMouseX(),GetMouseY(),10,10))
            {
                if( IsMouseButtonDown(0))
                {
                    if(c.IsNull()==false && _cselect.IsNull()==true)
                    {
                        Select(c);
                        _Set(i,j,Cart());
                    }
                    else if(j==5 && c.IsNull() && _cselect.IsNull()==true)
                    {
                        _lstcart[j][i] = Generate();
                    }
                }
                else if( IsMouseButtonReleased(0))
                {
                    if(c.IsNull() &&
                        _cselect.IsNull()==false)
                    {
                        _Set(i,j,_cselect);
                        Deselect();
                    }
                    else if(c.IsNull()==false && _cselect.IsNull()==false &&
                        c.GetType()==_cselect.GetType() &&
                        c.GetName()==_cselect.GetName()
                    )
                    {
                        //fuse cart
                        _Get(i,j)->Fuse(_cselect);
                        Deselect();

                    }
                }
            }
        }

        c.Draw(pos.x,pos.y);
        if(j==0 || j==5)
        {
            c.DrawBoardHand(pos.x,pos.y);
        }
        else c.DrawBoard(pos.x,pos.y);


        if(_cselect.GetName().empty()==false)
        {
            _cselect.Draw(GetMouseX()-c.GetWidth()/2,
                          GetMouseY()-c.GetHeight()/2);
        }
    }
}


Exodus::Exodus()
{
    _board.SetHand(0,0,CartItem("potion"));
    _board.SetHand(0,4,CartMonster("wolve"));
    _board.SetEquip(0,0,CartEquip("t"));
    _board.SetEquip(1,4,CartEquip("t"));
    Cart c = CartMonster("t");
    c.SetLevel(3);
    _board.SetInvoc(1,0,c);
    _board.SetInvoc(1,4,c);

}

void Exodus::Draw()
{
    _board.Draw();
}

