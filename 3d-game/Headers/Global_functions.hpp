#ifndef Global_functions_hpp
#define Global_functions_hpp
#include <SFML/Graphics.hpp>
namespace gf {
    static float rad(float angle) {
        return (angle*3.141592653f)/180.f;
    }
    //Все константы игры
    const int n = 802;
    const sf::Vector2f screen(800.f, 600.f);
    const float radius = 100.f; //радиус угла обзора
}
#endif /* Global_functions_hpp */
