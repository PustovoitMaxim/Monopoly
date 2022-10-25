#include<iostream>
#include<vector>
#include "Tile.h"
#include "Player.h"
#include "Action.h"
#include<list>
#pragma once
class Game {
public:
	Game(unsigned char count);
	void move_player(int ind, unsigned char dice);
	Player& get_player(int ind);
	Tile& get_player_tile(int ind);
	Action& get_next_chance(void);
	Action& get_next_CommChest(void);
private:
	struct Player_data
	{
		Player player;
		unsigned char pos;
	};
	vector<unique_ptr<Tile>> m_field;
	vector<Player_data> m_players;
	list<unique_ptr<Action>> m_chance;
	list<unique_ptr<Action>> m_comunity_chest;
};