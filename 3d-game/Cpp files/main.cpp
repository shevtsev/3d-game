#include <SFML/Graphics.hpp>
#include "Move_player.hpp"
#include "Init_game.hpp"
using namespace sf;
using namespace std;

//Класс запуска всех функций и цикла игры
class game_start: public init_game, move_player {
protected:
    RenderWindow& window;
public:
    game_start(RenderWindow& win) : window(win)
    {
        map_objs_init();
        sector_init();
        while (window.isOpen())
        {
            //Вращение игрока
            float current_angle = sector.getRotation();
            rotation(sector, screen, current_angle);
            draw_lines(current_angle);
            Mouse::setPosition(Vector2i(screen.x/2, screen.y/2));
            
            //Движение игрока
            move(sector, player, current_angle);
            // Process events
            Event event;
            while (window.pollEvent(event))
            {
                // Close window: exit
                if (event.type == Event::Closed) {
                    window.close();
                }

                // Escape pressed: exit
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
            draw_objs(window);
        }
    }
};

int main(int, char const**)
{
    RenderWindow window(VideoMode(screen.x, screen.y), "SFML window");
    game_start start(window);
    return EXIT_SUCCESS;
}
