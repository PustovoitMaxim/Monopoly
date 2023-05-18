#include "Game.h"
#include "Action.h"
#include <random>
using namespace std;

vector<unique_ptr<Tile>>create_field(void);
void Shuffle_cards(list<unique_ptr<Action>>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		random_device rd;     // Only used once to initialise (seed) engine
		mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
		uniform_int_distribution<int> first_random(0, v.size() - 1);// Guaranteed unbiased
		uniform_int_distribution<int> second_random(0, v.size() - 1);
		int q1 = first_random(rng);
		int q2 = second_random(rng);
		list<unique_ptr<Action>>::iterator k = v.begin();
		list<unique_ptr<Action>>::iterator l = v.begin();
		while (q1--)
			k++;
		while (q2--)
			l++;
		swap(*l, *k);

	}
}
list<unique_ptr<Action>>create_chance_cards(void)
{
	list<unique_ptr<Action>>l;
	l.push_back(unique_ptr<Action>(new GoToAction(24)));
	l.push_back(unique_ptr<Action>(new Pay2BankAction(15)));
	l.push_back(unique_ptr<Action>(new MoveAction(-3)));
	l.push_back(unique_ptr<Action>(new Move2Nearest(Tile::Tile_Type::Service)));
	l.push_back(unique_ptr<Action>(new Go2NearestRailroadPayTwiceAction));
	l.push_back(unique_ptr<Action>(new PrisonDenierAction));
	l.push_back(unique_ptr<Action>(new Go2JailAction));
	l.push_back(unique_ptr<Action>(new GetFromBank(150)));
	l.push_back(unique_ptr<Action>(new GoToAction(39)));
	l.push_back(unique_ptr<Action>(new GetFromBank(50)));
	l.push_back(unique_ptr<Action>(new Go2NearestRailroadPayTwiceAction));
	l.push_back(unique_ptr<Action>(new PayEverybodyAction(50)));
	l.push_back(unique_ptr<Action>(new GoToAction(0)));
	l.push_back(unique_ptr<Action>(new GoToAction(11)));
	l.push_back(unique_ptr<Action>(new GoToAction(5)));
	l.push_back(unique_ptr<Action>(new PayForHousesActionChance));
	//Shuffle_cards(l);
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
	//Shuffle_cards(l);
	return l;


}

Game::PlayerData::PlayerData() :
	player(new Player),
	pos(0),
	prison_counter(0),
	is_prison_denied(0)
{

}
void Game::GoToJail(unsigned char ind)
{
	m_players[ind].pos = 10;
	m_players[ind].prison_counter = 3;
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
	return *(m_players[ind]).player;
}
Tile& Game::get_tile(unsigned char ind)
{
	return *(m_field[(m_players[ind]).pos]);
}
vector<unique_ptr<Tile>>create_field(void)
{
	vector<unique_ptr<Tile>> field;

	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Start, new EmptyAction())));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Brown, "Mediter Ranean Avenue", { 2,10,30,90,160,250 }, 60)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::CommChest, new TakeCommunityCard())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Brown, "Baltic Avenue", { 4,20,60,180,320,450 }, 60)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Tax, new Pay2BankAction(200))));
	field.push_back(unique_ptr<Tile>(new RailRoad("Reading Railroad", 200)));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Blue, "Oriental Avenue", { 6,30,90,270,400,550 }, 100)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Chance, new TakeChanceCard())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Blue, "Vermont Avenue", { 6,30,90,270,400,550 }, 100)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Blue, "Connecticut Avenue", { 8,40,100,300,450,600 }, 120)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Jail, new EmptyAction())));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Pink, "St. Charles Place", { 10,50,150,450,625,750 }, 140)));
	field.push_back(unique_ptr<Tile>(new Service("Electric Company", 150)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Pink, "States Avenue", { 10,50,150,450,625,750 }, 140)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Pink, "Virginia Avenue", { 12,60,180,500,700,900 }, 160)));
	field.push_back(unique_ptr<Tile>(new RailRoad("Pennsilvania Railroad", 200)));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Orange, "St. James  Place", { 14,70,200,550,750,950 }, 180)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::CommChest, new TakeCommunityCard())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Orange, "Tennessee Avenue", { 14,70,200,550,750,950 }, 180)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Orange, "New York Avenue", { 16,80,220,600,800,1000 }, 200)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::FreeParking, new EmptyAction())));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Red, "Kentucky Avenue", { 18,90,250,700,875,1050 }, 220)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Chance, new TakeChanceCard())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Red, "Indiana Avenue", { 18,90,250,700,875,1050 }, 220)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Red, "Illinois Avenue", { 20,100,300,750,925,1100 }, 240)));
	field.push_back(unique_ptr<Tile>(new RailRoad("B & O Railroad", 200)));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Yellow, "Atlantic Avenue", { 22,110,330,800,975,1150 }, 260)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Yellow, "Ventnor Avenue", { 22,110,330,800,975,1150 }, 260)));
	field.push_back(unique_ptr<Tile>(new Service("Water Works", 150)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Yellow, "Marvin Gardens", { 24,120,360,850,1025,1200 }, 280)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::GoToJail, new Go2JailAction())));

	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Green, "Pacific Avenue", { 26,130,390,900,1100,1275 }, 300)));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Green, "Nortn Carolina Avenue", { 26,130,390,900,1100,1275 }, 300)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::CommChest, new TakeCommunityCard())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::Green, "Pennsulvania Avenue", { 28,150,450,1000,1200,1400 }, 320)));
	field.push_back(unique_ptr<Tile>(new RailRoad("Short Line", 200)));

	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Chance, new TakeChanceCard())));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::DarkBlue, "Park Place", { 35,175,500,1100,1300,1500 }, 350)));
	field.push_back(unique_ptr<Tile>(new ActionTile(Tile::Tile_Type::Tax, new Pay2BankAction(100))));
	field.push_back(unique_ptr<Tile>(new Street(Street::StreetColors::DarkBlue, "Boardwalk", { 50,200,600,1200,1400,1700 }, 400)));

	return field;
}

void Game::MovePlayer(char dice_1, char dice_2, unsigned char ind)
{
	if (m_players[ind].prison_counter > 0)
	{
		if (m_players[ind].is_prison_denied)
		{
			m_players[ind].prison_counter = 0;
			m_players[ind].is_prison_denied = false;
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
	if (m_players[ind].pos > (m_players[ind].pos + dice_1 + dice_2) % 40 && dice_1 + dice_2 > 0)
		m_players[ind].player->get(200);
	m_players[ind].pos = (m_players[ind].pos + dice_1 + dice_2) % 40;
	m_field[m_players[ind].pos]->get_action().invoke(*this, ind);

	PropertyTile* p = dynamic_cast<PropertyTile*>(&get_tile(ind));
	bool can_build = true;
	if (p != nullptr && m_players[ind].player->skokadenegnischeta() >= 0)
	{
		if (p->get_ownership() == nullptr)
		{
			if (m_players[ind].player->get_AI().should_buy(*p, (*this)))
			{
				m_players[ind].player->pay(p->get_price());
				p->set_ownership(m_players[ind].player.get());
				can_build = false;
			}
		}
		if (p->get_tile_type() == Tile::Tile_Type::Street && can_build)
		{
			Street& s = *dynamic_cast<Street*>(p);
			if ((*this).IsStreetCaptured(*m_players[ind].player, s.get_color()))
			{
				if (s.get_houses() < 5 && m_players[ind].player->get_AI().should_build(s, *this))
				{
					m_players[ind].player->pay((get_pos_ind(ind) / 10 + 1) * 50);
					s.set_houses(s.get_houses() + 1);
				}
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
		m_players[ind].player->get(200);
	}
	m_field[m_players[ind].pos]->get_action().invoke(*this, ind);
	PropertyTile* p = dynamic_cast<PropertyTile*>(&get_tile(ind));
	bool can_build = true;
	if (p != nullptr)
	{
		if (p->get_ownership() == nullptr)
		{
			if (m_players[ind].player->get_AI().should_buy(*p, (*this)))
			{
				m_players[ind].player->pay(p->get_price());
				p->set_ownership(m_players[ind].player.get());
				can_build = false;
			}
		}
	}
	if (p->get_tile_type() == Tile::Tile_Type::Street && can_build)
	{
		Street& s = *dynamic_cast<Street*>(p);
		if ((*this).IsStreetCaptured(*m_players[ind].player, s.get_color()))
		{
			if (s.get_houses() < 5 && m_players[ind].player->get_AI().should_build(s, *this))
			{
				m_players[ind].player->pay((get_pos_ind(ind) / 10 + 1) * 50);
				s.set_houses(s.get_houses() + 1);
			}
		}
	}
}

void Game::GoTo(unsigned char where_to, unsigned char ind)
{
	const int start_pos = m_players[ind].pos;
	m_players[ind].pos = where_to;
	if (start_pos > where_to)
		m_players[ind].player.get()->get(200);
	m_field[m_players[ind].pos]->get_action().invoke(*this, ind);
}

void Game::SetPrisonDenied(unsigned char ind)
{
	m_players[ind].is_prison_denied = 1;
}

bool Game::IsStreetCaptured(Player& p, Street::StreetColors color)
{
	int a = 0;
	for (unique_ptr<Tile>& tile : m_field)
	{
		if ((*tile).get_tile_type() == Tile::Tile_Type::Street)
		{
			Street* s = dynamic_cast<Street*>(tile.get());
			if (s->get_color_type() == color && s->get_ownership() == &p)
				a++;
		}
	}
	if (color == Street::StreetColors::DarkBlue || color == Street::StreetColors::Brown)
	{
		if (a == 2)
			return true;
		return false;
	}
	else
	{
		if (a == 3)
			return true;
		return false;

	}
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
	unsigned short dice1 = 1 + std::rand() / ((RAND_MAX + 1u) / 6);
	unsigned short dice2 = 1 + std::rand() / ((RAND_MAX + 1u) / 6);
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
				if (h != 5)
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
	for (int i = 0; i < m_players.size(); ++i)
	{
		if (!has_player(i))
			continue;
		if ((m_players[i].player)->skokadenegnischeta() <= 0)
		{
			ClearingOwnership(*m_players[i].player);
			m_players[i].player.reset();
		}
	}
	return (current + 1) % m_players.size();

}

unsigned short Game::GetPlayersAmount()
{
	unsigned short a = 0;
	for (int i = 0; i < m_players.size(); i++)
		if (has_player(i))
			a++;
	return a;
}

void Game::log(ostream& s, unsigned char ind, int hod, pair<unsigned short, unsigned short>p)
{
	vector<vector<int>> property_info(m_players.size());
	for (int i = 0; i < m_field.size(); ++i)
	{
		PropertyTile* p = dynamic_cast<PropertyTile*>(m_field[i].get());
		if (p != nullptr)
		{
			for (int j = 0; j < m_players.size(); ++j)
			{
				if (m_players[j].player.get() == p->get_ownership() && has_player(j))
					property_info[j].push_back(i);
			}
		}
	}

	cout << hod << ":" << "player " << int(ind) << " throwed dices " << p.first << " and " << p.second << endl;
	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players[i].player.get() == nullptr)
		{
			cout << "Player" << i << " is dead" << endl;
			continue;
		}
		cout << "Player " << char(i + '0') << " is on " << int(m_players[i].pos) << " pos and has $" << m_players[i].player->skokadenegnischeta() << "    prison counter:" << int(m_players[i].prison_counter) << endl;
	}
	cout << endl;
	for (int i = 0; i < m_players.size(); ++i)
	{
		bool flag = 1;
		Player& current_player = *m_players[i].player;
		cout << "Player " << i << " has ";
		for (int j = 0; j < property_info[i].size(); ++j)
		{
			PropertyTile* pt = dynamic_cast<PropertyTile*>(&*m_field[property_info[i][j]]);
			if (pt != nullptr)
			{
				if (pt->get_tile_type() == Tile::Tile_Type::Street)
				{
					Street* s = dynamic_cast<Street*>(pt);
					cout << vector<string>{"Brown", "Blue", "Pink", "Orange", "Red", "Yellow", "Green", "DarkBlue"}[s->get_color()] << ":" << s->get_caption() << ", ";
					flag = 0;
				}
				else
				{
					cout << pt->get_caption() << ", ";
					flag = 0;
				}
			}
		}
		if (flag)
			cout << "nothing";
		cout << endl << endl;
	}

	cout << endl;
}

vector<Street::StreetColors>Game::WhichStreetsAreCapturedBy(Player& p)
{
	vector<Street::StreetColors>v;
	if (IsStreetCaptured(p, Street::StreetColors::Blue))
		v.push_back(Street::StreetColors::Blue);
	if (IsStreetCaptured(p, Street::StreetColors::Brown))
		v.push_back(Street::StreetColors::Brown);
	if (IsStreetCaptured(p, Street::StreetColors::DarkBlue))
		v.push_back(Street::StreetColors::DarkBlue);
	if (IsStreetCaptured(p, Street::StreetColors::Green))
		v.push_back(Street::StreetColors::Green);
	if (IsStreetCaptured(p, Street::StreetColors::Orange))
		v.push_back(Street::StreetColors::Orange);
	if (IsStreetCaptured(p, Street::StreetColors::Pink))
		v.push_back(Street::StreetColors::Pink);
	if (IsStreetCaptured(p, Street::StreetColors::Red))
		v.push_back(Street::StreetColors::Red);
	if (IsStreetCaptured(p, Street::StreetColors::Yellow))
		v.push_back(Street::StreetColors::Yellow);
	return v;
}

bool Game::IsStreetEmpty(Street::StreetColors color)
{
	for (unique_ptr<Tile>& tile : m_field)
	{
		if ((*tile).get_tile_type() == Tile::Tile_Type::Street)
		{
			Street* s = dynamic_cast<Street*>(tile.get());
			if (s->get_color_type() == color && s->get_ownership() != nullptr)
				return false;
		}
	}
	return true;
}

bool Game::IsStreetOnlyMine(Street::StreetColors color, Player& p)
{
	for (unique_ptr<Tile>& tile : m_field)
	{
		if ((*tile).get_tile_type() == Tile::Tile_Type::Street)
		{
			Street* s = dynamic_cast<Street*>(tile.get());
			if (s->get_color() == color && (s->get_ownership() != &p && s->get_ownership() != nullptr))
				return false;
		}
	}
	return true;
}

void Game::ClearingOwnership(Player& p)
{
	for (unique_ptr<Tile>& tile : m_field)
	{
		PropertyTile* pt = dynamic_cast<PropertyTile*>(tile.get());
		if (pt != nullptr)
		{
			if (pt->get_ownership() == &p)
				pt->set_ownership(nullptr);
		}
	}
}

unsigned char Game::get_pos_ind(unsigned char ind)
{
	return m_players[ind].pos;
}

unsigned char Game::get_pos_by_player(Player& p)
{
	for (int i = 0; i < m_players.size(); ++i)
		if (m_players[i].player.get() == &p)
			return i;
	throw "Ashibka";
}

bool Game::has_player(unsigned char ind)
{
	return m_players[ind].player.get() != nullptr;
}
vector<unique_ptr<Tile>>& Game::get_field() {
	return m_field;
}

vector<Street*> Game::wanna_exchange(Player& player) {
	vector<int> districts(8, 0);
	vector<Street*> tiles;
	vector<int> total_streets{2,3,3,3,3,3,3,2};
	for (unique_ptr<Tile>& tile : m_field) {
		Street* s = dynamic_cast<Street*>(tile.get());
		if (s) {
			if (s->get_ownership() == &player)
				districts[s->get_color_type()]++;
		}
	}
	for (unique_ptr<Tile>& tile : m_field) {
		Street* s = dynamic_cast<Street*>(tile.get());
			if (s) {
				if (s->get_ownership() && (s->get_ownership() != &player) && (total_streets[s->get_color_type()]-districts[s->get_color_type()]==1))
					tiles.push_back(s);
			}
	}
	return tiles;
}