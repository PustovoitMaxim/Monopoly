#pragma once
#include"Player.h"
#include"Tile.h"
#include<string>
class Game;
using namespace std;
class Action {
public:
	virtual void invoke(unsigned char player_ind,Game& game) = 0;
};

class Pay2BankAction:public Action {
public:
	Pay2BankAction(unsigned short sum);
	virtual void invoke(unsigned char player_ind, Game& game);
private:
	unsigned short m_sum;
};
class PayfromBankAction :public Action {
public:
	PayfromBankAction(unsigned short sum);
	virtual void invoke(unsigned char player_ind, Game& game);
private:
	unsigned short m_sum;
};
class money_from_players :public Action {
public:
	money_from_players(unsigned short sum);
	virtual void invoke(unsigned char player_ind, Game& game);
private:
	unsigned short m_sum;
};
class EmptyAction: public Action {
public:
	virtual void invoke(unsigned char player_ind, Game& game);
private:
};
class OwnerAction :public Action {
public:
	virtual void invoke(unsigned char player_ind, Game& game);
};
class TakeChance : public Action {
public:
	virtual void invoke(unsigned char player_ind, Game& game);
};

class TakeCommChest: public Action{
public:
	virtual void invoke(unsigned char player_ind, Game& game);
};

class Chance_Card :public Action {
public:
	Chance_Card(string text, Action* action);
	virtual void invoke(unsigned char player_ind, Game& game);
private:
	string m_text;
	std::unique_ptr<Action> m_action;
};
class Commuity_card : public Action {
public:
	Commuity_card(string text, Action* action);
	virtual void invoke(unsigned char player_ind, Game& game);
private:
	string m_text;
	std::unique_ptr<Action> m_action;
};
class Move_Abs_Action : public Action {
public:
	Move_Abs_Action(unsigned char to);
	virtual void invoke(unsigned char player_ind, Game& game);

private:
	unsigned char m_to;
};

class MoveToNearest : public Action {
public:
	MoveToNearest(Tile::Tile_Type tile_type);	
	virtual void invoke(unsigned char player_ind, Game& game);

private:
	Tile::Tile_Type m_tile_type;
};

