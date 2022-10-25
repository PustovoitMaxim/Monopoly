#include "Tile.h"
#include <iostream>
Tile::Tile() {

}

Street::Street(StreetColors color, const string& caption, const vector<unsigned short> rent, unsigned short price):
	m_price(price), m_ownership(nullptr), m_color(color), m_rent(rent), m_caption(caption)
{
}
Action& Street::get_action(void) {
	throw 0;
}
Action& Action_tile::get_action(void) {
	return *m_action;
}
Action_tile::Action_tile(Action* Action):
	m_action(Action)
{
}
RailRoad::RailRoad(const vector<unsigned short>& rent, const string caption):
	m_price(200), m_rent(rent), m_ownership(nullptr), m_caption(caption) {
}
Action& RailRoad::get_action(void) {
	return *m_action;
}