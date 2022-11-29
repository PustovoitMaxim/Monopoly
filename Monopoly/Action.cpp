#include "Action.h"
#include "Player.h"
#include "Game.h"

Pay2BankAction::Pay2BankAction(unsigned short sum):
m_sum(sum)
{}
void Pay2BankAction::invoke(unsigned char player_ind, Game& game){
	game.get_player(player_ind).pay(m_sum);
}
PayfromBankAction::PayfromBankAction(unsigned short sum) :
	m_sum(sum) {

}
void PayfromBankAction::invoke(unsigned char player_ind, Game& game) {
	game.get_player(player_ind).claim_money(m_sum);
}
void EmptyAction::invoke(unsigned char player_ind, Game& game){}
//void OwnerAction::invoke(unsigned char player_ind, Game& game) {
	//if(game.get_player_tile(player_ind))
//}
void TakeChance::invoke(unsigned char player_ind, Game& game) {
	game.get_next_chance().invoke(player_ind, game);
}

void TakeCommChest::invoke(unsigned char player_ind, Game& game) {
	game.get_next_CommChest().invoke(player_ind, game);
}
money_from_players::money_from_players(unsigned short sum) :
	m_sum(sum) {

} 
Chance_Card::Chance_Card(string text, Action* action) :
	m_text(text), m_action(action)
{
}
void Chance_Card::invoke(unsigned char player_ind, Game& game){
	m_action->invoke(player_ind, game);
}
Commuity_card::Commuity_card(string text, Action* action) :
	m_text(text), m_action(action) 
{
}
void Commuity_card::invoke(unsigned char player_ind, Game& game) {
	m_action->invoke(player_ind, game);
}
void money_from_players::invoke(unsigned char player_ind, Game& game) {
	for (int i = 0; i < game.getPlayersCount(); i++) {
		if (i != player_ind)
			game.get_player(player_ind).pay(m_sum);
		else
			game.get_player(player_ind).claim_money((game.getPlayersCount() - 1) * m_sum);
	}
}

MoveToNearest::MoveToNearest(Tile::Tile_Type tile_type):
	m_tile_type(tile_type)
{
}

void MoveToNearest::invoke(unsigned char player_ind, Game& game) {
	game.move_player_until(player_ind, [=](const Tile& tile) {
		return tile.get_tile_type() == m_tile_type;
		});
}
Move_Abs_Action::Move_Abs_Action(unsigned char to) :
	m_to(to) 
{
}

void Move_Abs_Action::invoke(unsigned char player_ind, Game& game) {
	game.move_player_abs(player_ind, m_to);
}