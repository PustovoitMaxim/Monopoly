//#include <SFML/Graphics.hpp>
#include <random>
#include "Game.h"
#include "Action.h"
#include "AI.h"
#include"Player.h"
using namespace std;
//using namespace sf;
int infinite_games = 0;
int main()
{
    for (int i = 0; i < 10000; i++) {
        cout << i  <<" " <<  infinite_games << endl;
        int b = 4;
        Game game(b);
        std::srand(13);

        unsigned char current_player = 0;
        int a = 0;
        while (true)
        {
            if (&game.get_player(current_player)) {
                Request r = game.get_player(current_player).get_AI().exchange_request(game);
                if (r.to_give != nullptr && r.to_give->get_ownership() != nullptr) {
                    bool accepted = r.to_give->get_ownership()->get_AI().accept_request(r);
                    if (accepted) {
                        r.to_give->set_ownership(&game.get_player(current_player));
                        game.get_player(current_player).pay(r.money_to_receive);
                        r.to_give->get_ownership()->get(r.money_to_receive);
                    }
                }
            }
            if (a == 15000)
            {
                cout << "Infinite Game" << endl;
                infinite_games++;
                break;
            }
            if (game.has_player(current_player))
            {
                a++;
            }
            else
            {
                current_player = (current_player + 1) % b;
                continue;
            }
            if (a == 623)
                int qq = 0;
            if (game.GetPlayersAmount() <= 1)
            {
                //cout << "Game Over" << endl;
                break;
            }
            if (game.has_player(current_player))
            {
                pair<unsigned short, unsigned short>p = game.throw_dices();
                game.MovePlayer(p.first, p.second, current_player);
                unsigned char t = game.CheckingForNischeta(current_player);
                game.log(cout, current_player, a, p);
                current_player = t;
            }
            if (a == 655)
                int qq = 0;

        }
    }






















    /*sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!",Style::Fullscreen);
    sf::Texture texture;
    texture.loadFromFile("image.jpg");
    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }











    return 0;*/
}