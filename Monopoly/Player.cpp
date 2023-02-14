#include "Player.h"
void Player::pay(unsigned short sum)
{
	m_money -= sum;
}
void Player::get(unsigned short sum)
{
	m_money += sum;
}
Player::Player() :
	m_money(1500),
	m_AI(new First_AI(*this))
{

}

short Player::skokadenegnischeta()
{
	return m_money;
}

AI& Player::get_AI()
{
	return *m_AI;
}
