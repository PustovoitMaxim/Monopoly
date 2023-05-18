#pragma once
#include "Player.h"
#include "Game.h"
class Action
{
public:
	virtual void invoke(Game& game, unsigned char ind) = 0;
	virtual string get_caption() = 0;
};
class Pay2BankAction :public Action
{
public:
	Pay2BankAction(unsigned short sum);
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
private:
	unsigned short m_sum;
};
class EmptyAction :public Action
{
public:
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
private:
};
class GoToAction :public Action
{
public:
	GoToAction(unsigned char where);
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
private:
	unsigned char m_where;
};
class TakeChanceCard : public Action
{
public:
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
};
class TakeCommunityCard : public Action
{
public:
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
};
class Move2Nearest :public Action
{
public:
	Move2Nearest(Tile::Tile_Type type);
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
private:
	Tile::Tile_Type m_tile_type;
};

class Go2JailAction :public Action
{
public:
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
};

class MoveAction :public Action
{
public:
	MoveAction(char naskoka);
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
private:
	char m_naskoka;
};

class PrisonDenierAction :public Action
{
public:
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
};


class GetFromBank :public Action
{
public:
	GetFromBank(unsigned short sum);
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
private:
	unsigned short m_sum;
};

class PayEverybodyAction :public Action
{
public:
	PayEverybodyAction(unsigned char sum);
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
private:
	unsigned char m_sum;
};

class GetFromEverybodyAction :public Action
{
public:
	GetFromEverybodyAction(unsigned char sum);
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
private:
	unsigned char m_sum;
};

class StreetAction :public Action
{
public:
	StreetAction(Street& street);
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
private:
	Street& m_street;
};

class RailRoadAction :public Action
{
public:
	RailRoadAction(RailRoad& railroad);
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
private:
	RailRoad& m_railroad;
};

class ServiceAction :public Action
{
public:
	ServiceAction(Service& service);
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
private:
	Service& m_service;
};

class Go2NearestRailroadPayTwiceAction :public Action
{
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
};

class PayForHousesActionCommun :public Action
{
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
};

class PayForHousesActionChance :public Action
{
	virtual void invoke(Game& game, unsigned char ind);
	virtual string get_caption();
};