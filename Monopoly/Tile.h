#pragma once
#include"Player.h"
#include"Action.h"
#include <vector>
#include <iostream>
using namespace std;

class Tile {
public:
	enum class Tile_Type {
		Street,
		Action_tile,
		RailRoad,
	};
	virtual Action& get_action(void) = 0;
	virtual Player* get_ownership(void)=0;
	Tile_Type get_tile_type(void) const;
protected:
	Tile(Tile_Type t);
private:
	Tile_Type m_type;
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
	virtual Action& get_action(void);
	virtual Player* get_ownership(void);
private:
	const unsigned short m_price;
	Player* m_ownership;
	const StreetColors m_color;
	unsigned char m_houses;
	bool m_pledge;
	const vector<unsigned short> m_rent;
	const string m_caption;
};
class Action_tile : public Tile {
public:
	Action_tile(Action* Action);
	Action& get_action(void);
	virtual Player* get_ownership(void);
public:
	unique_ptr<Action> m_action;
};
class RailRoad : public Tile {
public:
	RailRoad(const vector<unsigned short>& rent, const string caption);
	Action& get_action(void);
	virtual Player* get_ownership(void);
private:
	const unsigned short m_price;
	Player* m_ownership;
	const vector<unsigned short> m_rent;
	const string m_caption;
	unique_ptr<Action> m_action;
};