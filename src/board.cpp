#include "board.hpp"

Cart* Board::_Get(int x, int y)
{
	return &(_lstcart[y][x]);
}
void Board::_Set(int x, int y, Cart cart)
{
	_lstcart[y][x]=cart;
}

void Board::_Click(int x, int y,CartManager cartman)
{
	Cart cart = *_Get(x,y);
	if(cart.IsExist() && _cselect.IsNull())
	{
		Select(cart);
		_Set(x,y,Cart());
		_pselect = {(float)x,(float)y};
	}
	else if(cart.IsNull() && _cselect.IsNull())
	{
		_Set(x,y,cartman.Generate());
	}
}

void Board::_ReleaseClick(int x, int y,CartManager cartman)
{
	Cart* cart = _Get(x,y);
	if(cart->IsNull() &&
		_cselect.IsNull()==false)
	{
		if( IsInvoc(y,_cselect) ||
			(y==0 || y==5))
		{
			_Set(x,y,_cselect);
			Deselect();
		}
	}
	else if(cart->IsExist() && _cselect.IsExist())
	{
		if( cart->GetType()==_cselect.GetType() &&
			cart->GetName()==_cselect.GetName()
		)
		{
			//fuse cart
			if(cartman.Fusion(cart,_cselect)
			)
				Deselect();

		}
		else if(cart->Equip(_cselect))
		{
			Deselect();

		}
	}
}

Board::Board()
{
	btntxt = new ButtonText(23,23,"next turn",16,BLUE);
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


void Board::SetHand(enum TeamNumb team, int pos, Cart cart)
{
	if(team == Team1)
	{
		_Set(pos,0,cart);
	}
	else if(team == Team2)
	{
		_Set(pos,5,cart);
	}
}
void Board::SetInvoc(enum TeamNumb team, int pos, Cart cart)
{
	int ly = 0;
	int lx=0;
	if(team == Team1)
	{
		ly=1;
	}
	else if(team == Team2)
	{
		ly=3;
	}

	if(pos>4)
	{
		ly++;
		lx-=5;
	}
	_Set(lx,ly,cart);
}
Cart Board::GetHand(enum TeamNumb team, int pos)
{
	if(team == Team1)
	{
		return *_Get(pos,0);
	}
	else if(team == Team2)
	{
		return *_Get(pos,5);
	}
	return Cart();
}
Cart Board::GetInvoc(enum TeamNumb team, int pos)
{
	int ly = 0;
	int lx=0;
	if(team == Team1)
	{
		ly=1;
	}
	else if(team == Team2)
	{
		ly=3;
	}

	if(pos>4)
	{
		ly++;
		lx-=5;
	}
	return *_Get(lx,ly);
}
TeamNumb Board::GetTeam(int y)
{
	if(y>=3) return Team2;
	return Team1;
}

bool Board::IsInvoc(int y, Cart cart)
{
	if(y>0 && y<5 && cart.GetType()==CartTypeMonster) return true;
	return false;
}
bool Board::IsAttack(int x, int y, int x2, int y2)
{
	TeamNumb team1 = GetTeam(y);
	TeamNumb team2 = GetTeam(y2);
	if(team1!=team2)
	{
		return true;
	}
	return false;
}


bool collide(int x,int y,int w,int h,int x2,int y2,int w2,int h2)
{
	if(x<x2+w2 && y<y2+h2 && x2<x+w && y2<y+h) return true;
	return false;
}

void Board::DrawRange()
{
	if(!_cselect.IsNull() &&
		_cselect.GetType()==CartTypeMonster)
	{
		Vector2 v2 = _pselect;
		int x = v2.x;
		int y = v2.y;
		TeamNumb team = GetTeam(y);
		int range = 1;
		const int vw = _cselect.GetWidth();
		const int vh = _cselect.GetHeight();

		if(_cselect.GetEquipEffet()==CartEquipRange)
		{
			range = 2;
		}
		//if(y==2 || y==3)
		//{
			if(team==Team1)
			{

			}
			else if(team==Team2)
			{
				for(int i=1;i<range+1;i++)
				{
					int ly = y-i;
					if(ly==2 || ly==1)
					{
						Vector2 vr = _posb[y-i][x];
						if(!_lstcart[y-1][x].IsNull())
						DrawRectangle(vr.x,vr.y,vw,vh,BLUE);
					}

				}
			}
		//}
	}
}

void Board::_UITurn(TurnManager* turnmanager)
{
	DrawText(TextFormat("turn player %d",turnmanager->GetCurantTurn()),-10+GetRenderWidth()/2,23,19,WHITE);
	if(btntxt->Draw()==ButtonPress)
	{
		turnmanager->NextTurn();
	}
}

void Board::_UIBoard(TurnManager* turnmanager, CartManager cartman)
{
	DrawLine(0,3+GetRenderHeight()/2,GetRenderWidth(),3+GetRenderHeight()/2,WHITE);
	for(int j=0;j<BoardHeight;j++)
		for(int i=0;i<BoardWidth;i++)
		{
			Cart c = *_Get(i,j);
			Vector2 pos = _posb[j][i];

			if((j<=2 && turnmanager->GetCurantTurn()==TurnPlayer0) ||
				(j>2 && turnmanager->GetCurantTurn()==TurnPlayer1))
			{
				if(collide( pos.x,
					pos.y,c.GetWidth(),c.GetHeight(),GetMouseX(),GetMouseY(),10,10))
				{
					if( IsMouseButtonDown(0))
					{
						_Click(i,j,cartman);
					}
					else if( IsMouseButtonReleased(0))
					{
						_ReleaseClick(i,j,cartman);
					}
				}
			}

			c.Draw(pos.x,pos.y);
			if(j==0 || j==5)
			{
				TeamNumb tn = GetTeam(j);
				TurnId tt = turnmanager->GetCurantTurn();
				if((tn==Team1 && tt==TurnPlayer0) ||
					(tn==Team2 && tt==TurnPlayer1))
					c.DrawBoardHand(pos.x,pos.y,true);
				else
					c.DrawBoardHand(pos.x,pos.y,false);
			}
			else c.DrawBoard(pos.x,pos.y);


			if(_cselect.IsExist())
			{
				_cselect.Draw(
					GetMouseX()-c.GetWidth()/2,
							  GetMouseY()-c.GetHeight()/2);
			}
		}
	DrawRange();
}


void Board::Draw(TurnManager* turnmanager,CartManager cartman)
{

	_UITurn(turnmanager);
	_UIBoard(turnmanager,cartman);

}
