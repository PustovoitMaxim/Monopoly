#include "Player.h"
void Player::pay(int sum)
{
	m_money -= sum;
}
void Player::get(int sum)
{
	m_money += sum;
}
Player::Player() :
	m_money(1500),
	m_AI(new First_AI(*this))
{

}

int Player::skokadenegnischeta()
{
	return m_money;
}

const AI& Player::get_AI()
{
	return *m_AI;
}



void Player::pay2player(Player& p, int sum)
{
	pay(sum);
	p.get(sum);
}