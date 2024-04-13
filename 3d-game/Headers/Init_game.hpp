#ifndef Init_game_hpp
#define Init_game_hpp

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "Math.hpp"
#include "Global_functions.hpp"

using namespace sf;
using namespace std;
using namespace gf;

//Все константы игры
const int n = 802;
const Vector2f screen(800.f, 600.f);
const float radius = 100.f; //радиус угла обзора

//Класс инициализации
class init_game: public math {
public:
    CircleShape player;
    ConvexShape sector;
    vector<RectangleShape> target, ray_tr;
    vector <Vector2i> wall = {Vector2i(0, 1), Vector2i(0, 3), Vector2i(2, 3), Vector2i(1, 2)};
    
    //Инициализация объектов карты
    void map_objs_init();
    
    //Инициализация сектора обзора
    void sector_init();
    
    //Алгоритм рисования вертикальных полосок
    void draw_lines(float current_angle);
    
    //Отрисовка всех объектов игры
    void draw_objs(RenderWindow& window);
};
#endif /* Init_game_hpp */
