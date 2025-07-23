#include "../Headers/Game_start.hpp"

//Функция старта в запуске конструктора
void game_start::start()
{
    map_objs_init();
    sector_init();
    while (window.isOpen())
    {
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
        
        //Вращение игрока
        float current_angle = sector.getRotation();
        rotation(sector, current_angle);
        
        //Движение игрока
        move(sector, player, current_angle);
        
        for (int i = 0; i < n-2; ++i)
            draw_lines(current_angle,i);
            
        draw_objs(window);
    }
}
