#pragma once
#include"Tile.h"
struct Request {
	PropertyTile* to_give;
	PropertyTile* to_receive;
	int money_to_receive;
	Request();
	bool operator ==(const Request& req) const;

};
class AI
{
public:
	AI(Player&);
	Player& get_player() const;
	virtual bool should_buy(PropertyTile&, Game& game) const = 0;
	virtual bool jail_break(void) const = 0;
	virtual bool should_build(Street&, Game& game) const = 0;
	virtual void pledge(PropertyTile&) const = 0;
	virtual Request exchange_request(Game& game)const = 0;
	virtual bool accept_request(const Request& req)const  = 0;
protected:
	bool log_check(Request& req)const;
	void add_to_log(Request& r)const;
private:
	vector<pair<bool,Request>> offer_history;
	Player& m_player;
};

class First_AI :public AI
{
public:
	First_AI(Player&);
	virtual bool should_buy(PropertyTile&, Game& game) const;
	virtual bool jail_break(void) const;
	virtual bool should_build(Street&, Game& game) const;
	virtual void pledge(PropertyTile&) const;
	virtual Request exchange_request(Game& game)const;
	virtual bool accept_request(const Request&)const;
};

//class Second_AI :public AI
//{
//public:
//	Second_AI(Player&);
//	virtual bool should_buy(PropertyTile&, Game& game) const;
//	virtual bool jail_break(void) const;
//	virtual bool should_build(Street&) const;
//	virtual void pledge(PropertyTile&) const;
//};