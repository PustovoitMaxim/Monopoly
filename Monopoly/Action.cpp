#include "Action.h"
Pay2BankAction::Pay2BankAction(unsigned short sum)
{
	m_sum = sum;
}

void Pay2BankAction::invoke(Game& game, unsigned char ind)
{
	game.get_player(ind).pay(m_sum);
	//cout << get_caption() << " completed" << endl;
}

void EmptyAction::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
}
GoToAction::GoToAction(unsigned char where)
	:m_where(where)
{

}
void GoToAction::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	game.GoTo(m_where, ind);
}
void TakeChanceCard::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	game.get_next_chance().invoke(game, ind);
}
void TakeCommunityCard::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	game.get_next_com_chest().invoke(game, ind);
}
Move2Nearest::Move2Nearest(Tile::Tile_Type type)
{
	m_tile_type = type;
}
void Move2Nearest::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	game.MoveUntil([=](const Tile& tile) {return tile.get_tile_type() == m_tile_type; }, ind);
}

void Go2JailAction::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	game.GoToJail(ind);
}

void MoveAction::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	game.MovePlayer(m_naskoka, 0, ind);
}

MoveAction::MoveAction(char naskoka)
{
	m_naskoka = naskoka;
}

void PrisonDenierAction::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	game.SetPrisonDenied(ind);
}

GetFromBank::GetFromBank(unsigned short sum)
{
	m_sum = sum;
}

void GetFromBank::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	game.get_player(ind).get(m_sum);
}

PayEverybodyAction::PayEverybodyAction(unsigned char sum) :
	m_sum(sum)
{

}

void PayEverybodyAction::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	int count = 0;
	for (int i = 0; i < game.GetPlayersAmount(); i++)
	{
		if (i != ind)
			if (game.has_player(i))
				game.get_player(i).get(m_sum), count++;
	}
	game.get_player(ind).pay(count * m_sum);
}

GetFromEverybodyAction::GetFromEverybodyAction(unsigned char sum)
	:m_sum(sum)
{

}

void GetFromEverybodyAction::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	game.get_player(ind).get((game.GetPlayersAmount() - 1) * m_sum);
	for (int i = 0; i < game.GetPlayersAmount(); i++)
	{
		if (i != ind)
			if (game.has_player(i))
				game.get_player(i).pay(m_sum);
	}
}

StreetAction::StreetAction(Street& street) :
	m_street(street)
{

}

RailRoadAction::RailRoadAction(RailRoad& railroad) :
	m_railroad(railroad)
{
}

ServiceAction::ServiceAction(Service& service) :
	m_service(service)
{
}

void StreetAction::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	if (m_street.get_ownership() != nullptr)
	{
		if (m_street.get_ownership() != &game.get_player(ind))
		{
			game.get_player(ind).pay2player(*m_street.get_ownership(), m_street.get_rent(game, ind));
		}
	}
}

void RailRoadAction::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	vector<int>rents = { 0,25,50,100,200 };
	if (m_railroad.get_ownership() != nullptr)
	{
		if (m_railroad.get_ownership() != &game.get_player(ind))
		{
			unsigned short sum = game.RailroadsCount(*m_railroad.get_ownership());
			game.get_player(ind).pay2player(*m_railroad.get_ownership(), rents[sum]);
		}
	}
}

void ServiceAction::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	if (m_service.get_ownership() != nullptr)
	{
		if (m_service.get_ownership() != &game.get_player(ind))
		{
			pair<unsigned short, unsigned short>p = game.throw_dices();
			unsigned short sum = p.first + p.second;
			if (game.ServiceCount(*m_service.get_ownership()) == 1)
				sum *= 4;
			else
				sum *= 10;
			game.get_player(ind).pay2player(*m_service.get_ownership(), sum);
		}
	}
}

void Go2NearestRailroadPayTwiceAction::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	vector<int>rents = { 0,25,50,100,200 };
	game.MoveUntil([=](const Tile& tile) {
		return tile.get_tile_type() == Tile::Tile_Type::RailRoad;
		}, ind);
	if (dynamic_cast<RailRoad*>(&game.get_tile(ind))->get_ownership() != nullptr)
	{
		game.get_player(ind).pay2player(*dynamic_cast<RailRoad*>(&game.get_tile(ind))->get_ownership(), rents[game.RailroadsCount(*dynamic_cast<RailRoad*>(&game.get_tile(ind))->get_ownership())] * 2);
	}
	if (dynamic_cast<RailRoad*>(&game.get_tile(ind))->get_ownership() != &game.get_player(ind))
		game.get_player(ind).get_AI().should_buy(*dynamic_cast<RailRoad*>(&game.get_tile(ind)), game);
}

void PayForHousesActionCommun::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	pair<unsigned short, unsigned short>p = game.CountOfHousesAndHotels(game.get_player(ind));
	game.get_player(ind).pay(p.first * 40 + p.second * 115);
}

void PayForHousesActionChance::invoke(Game& game, unsigned char ind)
{
	//cout << get_caption() << " completed" << endl;
	pair<unsigned short, unsigned short>p = game.CountOfHousesAndHotels(game.get_player(ind));
	game.get_player(ind).pay(p.first * 25 + p.second * 100);
}

string Pay2BankAction::get_caption()
{
	return "Pay2BankAction";
}

string EmptyAction::get_caption()
{
	return "EmptyAction";
}

string GoToAction::get_caption()
{
	return "GoToAction";
}

string TakeChanceCard::get_caption()
{
	return "TakeChanceCard";
}

string TakeCommunityCard::get_caption()
{
	return "TakeCommunityCard";
}

string Move2Nearest::get_caption()
{
	return "Move2NearestAction";
}

string Go2JailAction::get_caption()
{
	return "Go2JailAction";
}

string MoveAction::get_caption()
{
	return "MoveAction";
}

string PrisonDenierAction::get_caption()
{
	return "PrisonDenierAction";
}

string GetFromBank::get_caption()
{
	return "GetFromBankAction";
}

string PayEverybodyAction::get_caption()
{
	return "PayEverybodyAction";
}

string GetFromEverybodyAction::get_caption()
{
	return "GetFromEverybodyAction";
}

string RailRoadAction::get_caption()
{
	return "RailRoadAction";
}

string ServiceAction::get_caption()
{
	return "ServiceAction";
}

string Go2NearestRailroadPayTwiceAction::get_caption()
{
	return "Go2NearestRailroadPayTwiceAction";
}

string PayForHousesActionCommun::get_caption()
{
	return "PayForHousesActionCommun";
}

string PayForHousesActionChance::get_caption()
{
	return "PayForHousesActionChance";
}

string StreetAction::get_caption()
{
	return "StreetAction";
}