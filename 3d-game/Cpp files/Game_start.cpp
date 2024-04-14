#include "Game_start.hpp"

//Функция старта в запуске конструктора
void game_start::start()
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
