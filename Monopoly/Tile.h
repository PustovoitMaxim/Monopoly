#pragma once
#include"Player.h"
#include <vector>
#include <iostream>
#include "Action.h"
using namespace std;
class Tile {
public:
	Tile();
	virtual Action& get_action(void) = 0;
};
class Street: public Tile {
public:
	enum class StreetColors {
		brown,
		blue,
		pink,
		orange,
		red,
		yellow,
		green,
		dark_blue,
	};
	Street(StreetColors color,const string& caption, const vector<unsigned short> rent,unsigned short price);
	virtual Action& get_action(void) {}
private:
	const unsigned short m_price;
	Player* m_ownership;
	const StreetColors m_color;
	unsigned char m_houses;
	bool m_pledge;
	const vector<unsigned short> m_rent;
	const string m_caption;
};