#pragma once
#include"Tile.h"
class AI
{
public:
	AI(Player&);
	Player& get_player();
	virtual bool should_buy(PropertyTile&) = 0;
	virtual bool jail_break(void) = 0;
	virtual bool should_build(Street&) = 0;
	virtual void pledge(PropertyTile&) = 0;
private:
	Player& m_player;
};

class First_AI :public AI
{
public:
	First_AI(Player&);
	virtual bool should_buy(PropertyTile&);
	virtual bool jail_break(void);
	virtual bool should_build(Street&);
	virtual void pledge(PropertyTile&);
};

class Second_AI :public AI
{
public:
	Second_AI(Player&);
	virtual bool should_buy(PropertyTile&);
	virtual bool jail_break(void);
	virtual bool should_build(Street&);
	virtual void pledge(PropertyTile&);
};