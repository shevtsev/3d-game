#ifndef Game_start_hpp
#define Game_start_hpp

#include <SFML/Graphics.hpp>
#include "Move_player.hpp"
#include "Init_game.hpp"

using namespace sf;
using namespace std;

//Класс запуска игры
class game_start: private init_game, move_player {
protected:
    RenderWindow& window;
public:
    void start();
    game_start(RenderWindow& win) : window(win){start();};
};

#endif /* Game_start_hpp */
