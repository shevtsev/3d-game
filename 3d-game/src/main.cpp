#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Headers/Game_start.hpp"
#include "../Headers/Global_functions.hpp"

using namespace sf;
using namespace gf;

int main(int, char const**)
{
    RenderWindow window(VideoMode(screen.x, screen.y), "SFML window");
    game_start start(window);
    return EXIT_SUCCESS;
}
