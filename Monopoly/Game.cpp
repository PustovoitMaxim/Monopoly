#include<iostream>
#include<vector>
#include"Game.h"
using namespace std;

Game::Game(unsigned char count) :
	m_players(count)
{
	m_field = create_field();

}
void Game::move_player(int ind, unsigned char dice) {
	m_players[ind].pos = (m_players[ind].pos+dice) % 40;

}