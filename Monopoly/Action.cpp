#include "Action.h"
#include "Player.h"

Pay2BankAction::Pay2BankAction(unsigned short sum):
m_sum(sum)
{}
void Pay2BankAction::invoke(Player& p){
	p.pay(m_sum);
}
void EmptyAction::invoke(Player& p) {}