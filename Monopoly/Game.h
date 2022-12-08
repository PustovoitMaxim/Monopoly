#pragma once
#include<iostream>
#include<vector>
#include "Tile.h"
#include "Player.h"
#include "Action.h"
#include<list>
#include <functional>

class Game {
public:
	Game(unsigned char count);
	void move_player(int ind, unsigned char dice);
	void move_player_int(int ind, int tiles_to_move);
	void move_player_abs(int ind, unsigned char abs_pos);
	void move_player_until(int ind,const std::function<bool (const Tile&)>& f);
	Player& get_player(int ind);
	Tile& get_player_tile(int ind);
	Action& get_next_chance(void);
	Action& get_next_CommChest(void);
	unsigned short getPlayersCount();	
private:
	struct Player_data
	{
		Player player;
		unsigned char pos;
		bool escape_card;
	};
	vector<unique_ptr<Tile>> m_field;
	vector<Player_data> m_players;
	list<unique_ptr<Action>> m_chance;
	list<unique_ptr<Action>> m_comunity_chest;
};