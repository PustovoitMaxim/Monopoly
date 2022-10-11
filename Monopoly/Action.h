#pragma once
#include"Player.h"
class Action {
public:
	virtual void invoke(Player& p) = 0;
};

class Pay2BankAction:public Action {
public:
	Pay2BankAction(unsigned short sum);
	virtual void invoke(Player& p);
private:
	unsigned short m_sum;
};

class EmptyAction {
public:
	virtual void invoke(Player& p);
private:
};