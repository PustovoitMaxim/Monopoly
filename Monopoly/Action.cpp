#include "Action.h"
#include "Player.h"
#include "Game.h"

Pay2BankAction::Pay2BankAction(unsigned short sum):
m_sum(sum)
{}
void Pay2BankAction::invoke(int ind, Game& game){
	game.get_player().pay(m_sum);
}
void EmptyAction::invoke(int ind, Game& game){}
void OwnerAction::invoke(int ind, Game& game) {
	if(game.get_player_tile(ind))
}
void TakeChance::invoke(int current_player, Game& game) {
	game.get_next_chance().invoke(current_player, game);
}
void TakeCommChest::invoke(int current_player, Game& game) {
	game.get_next_CommChest().invoke(current_player, game);
}