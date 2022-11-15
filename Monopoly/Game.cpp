#include<iostream>
#include<vector>
#include"Game.h"
#include"Action.h"
using namespace std;

vector<unique_ptr<Tile>> create_field(void)
{
	vector<unique_ptr<Tile>> field;
	field.push_back(unique_ptr<Tile>(new Action_tile(new EmptyAction())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::brown, "mediter-ranean avenue", {}, 60)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new TakeCommChest())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::brown, "baltic avenue", {}, 60)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new Pay2BankAction(200))));
	field.push_back(unique_ptr<Tile>(new RailRoad({},"Riga railway station")));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::blue, "oriental avenue", {}, 100)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new TakeChance())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::blue, "vermont avenue", {}, 100)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::blue, "connecticut avenue", {}, 100)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new EmptyAction())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::pink, "st.charles place", {}, 140)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new EmptyAction())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::pink, "states avenur", {}, 140)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::pink, "virginia avenue", {}, 160)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new EmptyAction())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::orange, "st.james place", {}, 180)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new TakeCommChest())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::orange, "tannessee avenue", {}, 180)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::orange, "new york avenue", {}, 200)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new EmptyAction())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::red, "kentucky avenue", {}, 220)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new TakeChance())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::red, "indiana avenue", {}, 220)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::red, "illinois avenue", {}, 240)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new EmptyAction())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::yellow, "atlantic avenue", {}, 260)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::yellow, "ventnor avenue", {}, 260)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new EmptyAction())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::yellow, "marvin gardens", {}, 260)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new EmptyAction())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::green, "pacific avenue", {}, 300)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::green, "north carolina avenue", {}, 300)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new TakeCommChest())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::green, "pennsylvania avenue", {}, 320)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new EmptyAction())));
	field.push_back(unique_ptr<Tile>(new Action_tile(new TakeChance())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::dark_blue, "park place", {}, 350)));
	field.push_back(unique_ptr<Tile>(new Action_tile(new Pay2BankAction(100))));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::dark_blue, "boardwalk", {}, 400)));

	return field;
}
list<unique_ptr<Action>> create_chance_cards(void) {
	list<unique_ptr<Action>> chance_cards;
	chance_cards.push_back(unique_ptr<Action>(new EmptyAction()));
	return chance_cards;
}
list<unique_ptr<Action>> create_community_cards(void) {
	list<unique_ptr<Action>> community_cards;
	community_cards.push_back(unique_ptr<Action>(new EmptyAction()));
	return community_cards;
}
Game::Game(unsigned char count) :
	m_players(count)
{
	m_field = create_field();
	m_chance = create_chance_cards();
	m_comunity_chest = create_community_cards();
}
void Game::move_player(int ind, unsigned char dice) {
	m_players[ind].pos = (m_players[ind].pos+dice) % 40;
	m_field[m_players[ind].pos]->get_action().invoke(ind, *this);
}

Player& Game::get_player(int ind)
{
	return m_players[ind].player;
}

Tile& Game::get_player_tile(int ind)
{
	return *m_field[m_players[ind].pos];
}

Action& Game::get_next_chance(void) {
	m_chance.push_back(unique_ptr<Action>());
	swap(m_chance.front(), m_chance.back());
	m_chance.pop_front();
	return *m_chance.back();
}
Action& Game::get_next_CommChest(void) {
	m_comunity_chest.push_back(unique_ptr<Action>());
	swap(m_chance.front(), m_chance.back());
	m_comunity_chest.pop_front();
	return *m_comunity_chest.back();
}
unsigned short Game::getPlayersCount() {
	return this->m_players.size();
}
void Game::move_player_int(int ind, int tiles_to_move) {
	m_players[ind].pos = (m_players[ind].pos+tiles_to_move) % 40;
	m_field[m_players[ind].pos]->get_action().invoke(ind, *this);
}
void Game::move_player_abs(int ind, unsigned char abs_pos) {
	m_players[ind].pos = abs_pos;
	m_field[m_players[ind].pos]->get_action().invoke(ind, *this);
}
void Game::move_player_until(int ind, const std::function<bool(const Tile&)>& f){}