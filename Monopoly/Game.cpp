#include "Game.h"
#include "Action.h"
#include <random>
using namespace std;

void shuffle(list<unique_ptr<Action>>& v)
{
	list<unique_ptr<Action>>::iterator r = v.end();
	--r;
	int c = v.size();

	random_device rd;     // Only used once to initialise (seed) engine 
	mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case) 
	for (int i = 0; i < v.size(); ++i)
	{
		uniform_int_distribution<int> uni(0, c - 1);// Guaranteed unbiased 

		int q = uni(rng);
		list<unique_ptr<Action>>::iterator l = v.begin();
		while (q--)
			l++;
		swap(*r, *l);
		if (r == v.begin())
			break;
		--r;
		--c;
	}
}
vector<unique_ptr<Tile>>create_field(void);
list<unique_ptr<Action>>create_chance_cards(void)
{
	list<unique_ptr<Action>>l;
	l.push_back(unique_ptr<Action>(new GoToAction(24)));
	l.push_back(unique_ptr<Action>(new Pay2BankAction(15)));
	l.push_back(unique_ptr<Action>(new MoveAction(-3)));
	l.push_back(unique_ptr<Action>(new Go2NearestRailroadPayTwiceAction));
	l.push_back(unique_ptr<Action>(new PrisonDenierAction));
	l.push_back(unique_ptr<Action>(new Go2JailAction));
	l.push_back(unique_ptr<Action>(new GetFromBank(150)));
	l.push_back(unique_ptr<Action>(new GoToAction(39)));
	l.push_back(unique_ptr<Action>(new GetFromBank(50)));
	l.push_back(unique_ptr<Action>(new PayEverybodyAction(50)));
	l.push_back(unique_ptr<Action>(new GoToAction(0)));
	l.push_back(unique_ptr<Action>(new GoToAction(11)));
	l.push_back(unique_ptr<Action>(new GoToAction(5)));
	l.push_back(unique_ptr<Action>(new PayForHousesActionChance));
	shuffle(l);
	return l;
}
list<unique_ptr<Action>>create_commun_cards(void)
{
	list<unique_ptr<Action>>l;
	l.push_back(unique_ptr<Action>(new GoToAction(0)));
	l.push_back(unique_ptr<Action>(new Pay2BankAction(100)));
	l.push_back(unique_ptr<Action>(new Pay2BankAction(50)));
	l.push_back(unique_ptr<Action>(new GetFromBank(100)));
	l.push_back(unique_ptr<Action>(new GetFromBank(20)));
	l.push_back(unique_ptr<Action>(new PrisonDenierAction));
	l.push_back(unique_ptr<Action>(new GetFromEverybodyAction(50)));
	l.push_back(unique_ptr<Action>(new GetFromBank(100)));
	l.push_back(unique_ptr<Action>(new Go2JailAction));
	l.push_back(unique_ptr<Action>(new GetFromBank(200)));
	l.push_back(unique_ptr<Action>(new Pay2BankAction(150)));
	l.push_back(unique_ptr<Action>(new GetFromBank(100)));
	l.push_back(unique_ptr<Action>(new GetFromBank(10)));
	l.push_back(unique_ptr<Action>(new GetFromBank(45)));
	l.push_back(unique_ptr<Action>(new GetFromBank(25)));
	l.push_back(unique_ptr<Action>(new PayForHousesActionCommun));
	shuffle(l);
	return l;


}
Game::PlayerData::PlayerData() :
	player(),
	pos(0),
	prison_counter(0),
	is_prison_denied(0)
{

}
void Game::GoToJail(unsigned char ind)
{
	GoTo(10, ind);
}
Game::Game(unsigned char const players_count) :
	m_players(players_count)
{
	m_field = create_field();
	m_chance = create_chance_cards();
	m_community_chest = create_commun_cards();

}
Action& Game::get_next_chance(void)
{
	m_chance.push_back(unique_ptr<Action>());
	swap(m_chance.front(), m_chance.back());
	m_chance.pop_front();
	return *m_chance.back();

}
Action& Game::get_next_com_chest(void)
{
	m_community_chest.push_back(unique_ptr<Action>());
	swap(m_community_chest.front(), m_community_chest.back());
	m_community_chest.pop_front();
	return *m_community_chest.back();
}
Player& Game::get_player(unsigned char ind)
{
	return (m_players[ind]).player;
}
Tile& Game::get_tile(unsigned char ind)
{
	return *(m_field[(m_players[ind]).pos]);
}
vector<unique_ptr<Tile>>create_field(void)
{
	vector<unique_ptr<Tile>> field;

	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Start, new EmptyAction())));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Brown, "Mediter Ranean Avenue", { 100 }, 60)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::CommChest, new TakeCommunityCard())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Brown, "Baltic Avenue", { 100 }, 60)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Tax, new Pay2BankAction(200))));
	field.push_back(unique_ptr<Tile>(new RailRoad("Reading Railroad", 200)));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Blue, "Oriental Avenue", { 100 }, 100)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Chance, new TakeChanceCard())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Blue, "Vermont Avenue", { 100 }, 100)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Blue, "Connecticut Avenue", { 120 }, 100)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Jail, new EmptyAction())));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Pink, "St. Charles Place", { 100 }, 140)));
	field.push_back(unique_ptr<Tile>(new Service("Electric Company", 150)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Pink, "States Avenue", { 100 }, 140)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Pink, "Virginia Avenue", { 100 }, 160)));
	field.push_back(unique_ptr<Tile>(new RailRoad("Pennsilvania Railroad", 200)));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Orange, "St. James  Place", { 100 }, 180)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::CommChest, new TakeCommunityCard())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Orange, "Tennessee Avenue", { 100 }, 180)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Orange, "New York Avenue", { 100 }, 200)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::FreeParking, new EmptyAction())));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Red, "Kentucky Avenue", { 100 }, 220)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Chance, new TakeChanceCard())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Red, "Indiana Avenue", { 100 }, 220)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Red, "Illinois Avenue", { 100 }, 240)));
	field.push_back(unique_ptr<Tile>(new RailRoad("B & O Railroad", 200)));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Yellow, "Atlantic Avenue", { 100 }, 260)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Yellow, "Ventnor Avenue", { 100 }, 260)));
	field.push_back(unique_ptr<Tile>(new Service("Water Works", 150)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Yellow, "Marvin Gardens", { 100 }, 280)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::GoToJail, new Go2JailAction())));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Green, "Pacific Avenue", { 100 }, 300)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Green, "Nortn Carolina Avenue", { 100 }, 300)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::CommChest, new TakeCommunityCard())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Green, "Pennsulvania Avenue", { 100 }, 320)));
	field.push_back(unique_ptr<Tile>(new RailRoad("Short Line", 200)));

	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Chance, new TakeChanceCard())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::DarkBlue, "Park Place", { 100 }, 350)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Tax, new Pay2BankAction(100))));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::DarkBlue, "Boardwalk", { 100 }, 400)));

	return field;
}

void Game::MovePlayer(char dice_1, char dice_2, unsigned char ind)
{
	if (m_players[ind].prison_counter > 0)
	{
		if (m_players[ind].is_prison_denied)
		{
			m_players[ind].prison_counter = 0;
			return;
		}
		else
		{
			if (dice_1 != dice_2)
			{
				m_players[ind].prison_counter--;
				return;
			}
		}
		m_players[ind].prison_counter = 0;
	}
	if (m_players[ind].pos > (m_players[ind].pos + dice_1 + dice_2) % 40)
		m_players[ind].player.get(200);
	m_players[ind].pos = (m_players[ind].pos + dice_1 + dice_2) % 40;
	m_field[m_players[ind].pos]->get_action().invoke(*this, ind);
	PropertyTile* p = dynamic_cast<PropertyTile*>(&get_tile(ind));
	if (p != nullptr)
	{
		if (p->get_ownership() == nullptr)
		{
			if (m_players[ind].player.get_AI().should_buy(*p))
			{
				m_players[ind].player.pay(p->get_price());
				p->set_ownership(m_players[ind].player);
			}
		}
	}
}

void Game::MoveUntil(const std::function<bool(const Tile&)>& f, unsigned char ind)
{
	const int start_pos = m_players[ind].pos;
	while (!f(get_tile(ind)))
		m_players[ind].pos = (m_players[ind].pos + 1) % m_field.size();
	if (m_players[ind].pos < start_pos)
	{
		m_players[ind].player.get(200);
	}
	m_field[m_players[ind].pos]->get_action().invoke(*this, ind);
	PropertyTile* p = dynamic_cast<PropertyTile*>(&get_tile(ind));
	if (p != nullptr)
	{
		if (p->get_ownership() == nullptr)
		{
			m_players[ind].player.get_AI().should_buy(*p);
		}
	}
}

void Game::GoTo(unsigned char where_to, unsigned char ind)
{
	const int start_pos = m_players[ind].pos;
	m_players[ind].pos = where_to;
	if (m_players[ind].pos < start_pos)
	{
		m_players[ind].player.get(200);
	}
	m_field[m_players[ind].pos]->get_action().invoke(*this, ind);
}

void Game::SetPrisonDenied(unsigned char ind)
{
	m_players[ind].is_prison_denied = 1;
}

bool Game::IsStreetCaptured(Player& p, Street::StreetColors color)
{
	for (unique_ptr<Tile>& tile : m_field)
	{
		if ((*tile).get_tile_type() == Tile::Tile_Type::Street)
		{
			Street* s = dynamic_cast<Street*>(tile.get());
			if (s->get_color_type() != color || s->get_ownership() != &p)
				return false;
		}
	}
	return true;
}

unsigned short Game::RailroadsCount(Player& p)
{
	unsigned short a = 0;
	for (unique_ptr<Tile>& tile : m_field)
	{
		if ((*tile).get_tile_type() == Tile::Tile_Type::RailRoad)
		{
			RailRoad* r = dynamic_cast<RailRoad*>(tile.get());
			if (r->get_ownership() == &p)
				a++;
		}
	}
	return a;
}

unsigned short Game::ServiceCount(Player& p)
{
	unsigned short a = 0;
	for (unique_ptr<Tile>& tile : m_field)
	{
		if ((*tile).get_tile_type() == Tile::Tile_Type::Service)
		{
			Service* s = dynamic_cast<Service*>(tile.get());
			if (s->get_ownership() == &p)
				a++;
		}
	}
	return a;
}

pair<unsigned short, unsigned short> Game::throw_dices()
{
	random_device rd;     // Only used once to initialise (seed) engine
	mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
	uniform_int_distribution<int> uni(1, 6);// Guaranteed unbiased
	unsigned char dice1 = uni(rng);
	unsigned char dice2 = uni(rng);
	return pair<unsigned short, unsigned short>(dice1, dice2);
}

pair<unsigned short, unsigned short> Game::CountOfHousesAndHotels(Player& p)
{
	unsigned short houses = 0;
	unsigned short hotels = 0;
	for (unique_ptr<Tile>& tile : m_field)
	{
		if ((*tile).get_tile_type() == Tile::Tile_Type::Street)
		{
			Street* s = dynamic_cast<Street*>(tile.get());
			if (s->get_ownership() == &p)
			{
				unsigned short h = s->get_houses();
				if (h != 4)
					houses += h;
				else
					hotels++;
			}
		}
	}
	return pair<unsigned short, unsigned short>(houses, hotels);
}

unsigned char Game::CheckingForNischeta(unsigned char current)
{
	int i = 0;
	int result = (current + 1) % m_players.size();;
	while (i < m_players.size())
	{
		if ((m_players[i].player).skokadenegnischeta() <= 0)
		{
			m_players.erase(m_players.begin() + i);
			if (i < result)
				--result;
		}
		else
			++i;
	}
	return result % m_players.size();

}

unsigned short Game::GetPlayersAmount()
{
	return m_players.size();
}

void Game::log(ostream& s, unsigned char ind, int hod)
{
	cout << hod << ": player " << char(ind + '0') << " is on " << int(m_players[ind].pos) << " pos and have $" << m_players[ind].player.skokadenegnischeta() << endl;
}