#include"AI.h"
#include"Player.h"
#include"Game.h"
#include<algorithm>
AI::AI(Player& p)
	:m_player(p)
{
}

First_AI::First_AI(Player& p)
	: AI(p)
{
}

//Second_AI::Second_AI(Player& p)
//	: AI(p)
//{
//}
Player& AI::get_player() const
{
	return m_player;
}

//First_AI:Have Enough Money - BUY!
bool First_AI::should_buy(PropertyTile& prop_tile, Game& game) const
{
	if (get_player().skokadenegnischeta() >= prop_tile.get_price())
	{
		/*if (prop_tile.get_tile_type() == Tile::Tile_Type::Street)
		{
			Street* s = dynamic_cast<Street*>(&prop_tile);
			if (game.IsStreetEmpty(s->get_color())||game.IsStreetOnlyMine(s->get_color(),get_player()))
				return true;
			return false;
		}*/
		return true;
	}

	return false;
}

bool First_AI::jail_break(void) const
{
	if (get_player().skokadenegnischeta() >= 50)
		return true;
	return false;
}

bool First_AI::should_build(Street& s, Game& game) const
{
	if ((*this).get_player().skokadenegnischeta() >= (game.get_pos_by_player((*this).get_player()) / 10 + 1) * 50)
		return true;
	return false;
}

void First_AI::pledge(PropertyTile& prop_tile) const
{
}

Request::Request():to_give(nullptr),to_receive(nullptr),money_to_receive(0){}

bool Request::operator ==(const Request& req) const {
	return to_give == req.to_give && money_to_receive == req.money_to_receive;
}

void AI::add_to_log(Request& r)const {
	bool result = accept_request(r);
	offer_history.push_back(pair<bool,Request>(result,r));
}
bool AI::log_check(Request& req) const {
	if (offer_history.size() < 3)
		return true;
	else {
		int logs_to_check = 3;
		if (all_of(offer_history.end() - logs_to_check, offer_history.end(), [=](pair<bool,Request> log)->bool{return(!log.first && !(req == log.second)); }))
			return false;
		else {
			return true;
		}
	}
}
Request First_AI::exchange_request(Game& game)const {
	Request req;
	vector<Street*> wanna_buy = game.wanna_exchange(get_player());
	Street* most_val = nullptr;
	for (int i = wanna_buy.size() - 1; i > 0;i--) {
			most_val = wanna_buy[i];
		req.to_give = most_val;
		if (most_val && get_player().skokadenegnischeta() - (most_val->get_price() + most_val->get_price() / 10 > 0)){
			req.money_to_receive = most_val->get_price() + most_val->get_price() / 10;
			if (log_check(req)) {
				add_to_log(req);
				return req;
			}
			else
				continue;
		}
	}
	return req;
}
bool First_AI::accept_request(const Request& req)const {
	if (req.to_give == nullptr)
		return false;
	else {
		if (req.to_give->get_ownership() == &get_player() && req.money_to_receive == (req.to_give->get_price()+req.to_give->get_price()/10))
			return true;
		return false;
	}
}


//Second_AI:Money>price+500
//bool Second_AI::should_buy(PropertyTile& prop_tile) const
//{
//	if (get_player().skokadenegnischeta() >= (prop_tile.get_price()+500))
//		return true;
//	return false;
//}
//
//bool Second_AI::jail_break(void) const
//{
//	if (get_player().skokadenegnischeta() >= 550)
//		return true;
//	return false;
//}
//
//bool Second_AI::should_build(Street&) const
//{
//	return 1;
//}
//
//void Second_AI::pledge(PropertyTile& prop_tile) const
//{
//}

