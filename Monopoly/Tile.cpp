#include "Tile.h"

Tile::Tile() {

}

Street::Street(StreetColors color, const string& caption, const vector<unsigned short> rent, unsigned short price):
	m_price(price), m_ownership(nullptr), m_color(color), m_rent(rent), m_caption(caption)
{
}