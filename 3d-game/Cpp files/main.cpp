#include <SFML/Graphics.hpp>
#include "Game_start.hpp"
using namespace sf;

//Запуск окна и объявление старта игры
int main(int, char const**)
{
    RenderWindow window(VideoMode(screen.x, screen.y), "SFML window");
    game_start start(window);
    return EXIT_SUCCESS;
}
