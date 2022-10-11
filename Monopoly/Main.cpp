#include"Game.h"
#include <random>

using namespace std;
int main()
{
	Game game(4);

	random_device rd;     // Only used once to initialise (seed) engine
	mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
	uniform_int_distribution<int> uni(2, 12); // Guaranteed unbiased

	int curr_player = 0;
	while (true) {
		unsigned char dices = uni(rng);
		game.move_player(curr_player, dices);
		curr_player = (curr_player + 1) % 4;

	}
 }