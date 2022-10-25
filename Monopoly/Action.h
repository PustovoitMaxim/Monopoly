#pragma once
#include"Player.h"
#include "Game.h"
class Action {
public:
	virtual void invoke(int ind,Game& game) = 0;
};

class Pay2BankAction:public Action {
public:
	Pay2BankAction(unsigned short sum);
	void invoke(int ind, Game& game);
private:
	unsigned short m_sum;
};

class EmptyAction: public Action {
public:
	void invoke(int ind, Game& game);
private:
};
class OwnerAction :public Action {
public:
	void invoke(int ind, Game& game);
};
class TakeChance : public Action {
public:
	void invoke(int current_player, Game& game);
};
class TakeCommChest: public Action{
	void invoke(int current_player, Game& game);
};