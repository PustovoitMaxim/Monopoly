#include "Player.h"
void Player::pay(unsigned short sum) {
	m_cash -= sum;
}
Player::Player():
	m_cash(1500)
{
}