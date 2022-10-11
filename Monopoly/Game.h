#include<iostream>
#include<vector>
#include "Tile.h"
#include "Player.h"
#pragma once
class Game {
public:
	Game(unsigned char count);
	vector<unique_ptr<Tile>> create_field(void)
	{
		vector<unique_ptr<Tile>> field;
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::brown, "mediter-ranean avenue", {}, 60)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::brown, "baltic avenue", {}, 60)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::blue, "oriental avenue", {}, 100)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::blue, "vermont avenue", {}, 100)));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::blue, "connecticut avenue", {}, 100)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::pink, "st.charles place", {}, 140)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::pink, "states avenur", {}, 140)));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::pink, "virginia avenue", {}, 160)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::orange, "st.james place", {}, 180)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::orange, "tannessee avenue", {}, 180)));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::orange, "new york avenue", {}, 200)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::red, "kentucky avenue", {}, 220)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::red, "indiana avenue", {}, 220)));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::red, "illinois avenue", {}, 240)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::yellow, "atlantic avenue", {}, 260)));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::yellow, "ventnor avenue", {}, 260)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::yellow, "marvin gardens", {}, 260)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::green, "pacific avenue", {}, 300)));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::green, "north carolina avenue", {}, 300)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::green, "pennsylvania avenue", {}, 320)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::dark_blue, "park place", {}, 350)));
		field.push_back(unique_ptr<Tile>(new Tile()));
		field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::dark_blue, "boardwalk", {}, 400)));

		return field;
	}
	void move_player(int ind, unsigned char dice);
private:
	struct Player_data
	{
		Player player;
		unsigned char pos;
	};
	vector<unique_ptr<Tile>> m_field;
	vector<Player_data> m_players;
};