#pragma once
#include "AI.h"
class Player
{
public:
	Player();
	const AI& get_AI();
	void pay(int sum);
	void get(int sum);
	void pay2player(Player& p, int sum);
	int skokadenegnischeta();
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
private:
	unique_ptr<const AI> m_AI;
	int m_money;
};