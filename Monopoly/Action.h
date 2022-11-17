#pragma once
#include"Player.h"
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
private:
	string m_text;
	Action* m_action;
};

class Commuity_card : public Action {
public:
	Commuity_card(string text, Action* action);
private:
	string m_text;
	Action* m_action;
};