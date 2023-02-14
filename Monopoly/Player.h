#pragma once
#include "AI.h"
class Player
{
public:
	Player();
	AI& get_AI();
	void pay(unsigned short sum);
	void get(unsigned short sum);
	short skokadenegnischeta();
private:
	unique_ptr<AI> m_AI;
	short m_money;
};