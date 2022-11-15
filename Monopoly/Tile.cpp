#include "Tile.h"
#include <iostream>
Tile::Tile(Tile_Type t) :
	m_type(t){
}
Tile::Tile_Type Tile::get_tile_type() const {
	return m_type;
}
Street::Street(StreetColors color, const string& caption, const vector<unsigned short> rent, unsigned short price):
	Tile(Tile_Type::Street),m_price(price), m_ownership(nullptr), m_color(color), m_rent(rent), m_caption(caption)
{
}
Action& Street::get_action(void) {
	throw 0;
}
Action& Action_tile::get_action(void) {
	return *m_action;
}
Action_tile::Action_tile(Action* Action) :
	Tile(Tile_Type::Action_tile), m_action(Action)
{
}
RailRoad::RailRoad(const vector<unsigned short>& rent, const string caption):
	Tile(Tile_Type::RailRoad),m_price(200), m_rent(rent), m_ownership(nullptr), m_caption(caption) {
}
Player* Street::get_ownership(void) {
	return m_ownership;
}
Player* Action_tile::get_ownership(void) { return nullptr; }
Player* RailRoad::get_ownership(void) {
	return m_ownership;
}
Action& RailRoad::get_action(void) {
	return *m_action;
}