#pragma once	
class Player {
public:
	void pay(unsigned short sum);
	void claim_money(unsigned short sum);
	Player();
private:
	unsigned short m_cash;
};