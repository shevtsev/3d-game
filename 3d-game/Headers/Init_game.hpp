#ifndef Init_game_hpp
#define Init_game_hpp

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "Global_functions.hpp"

using namespace sf;
using namespace std;
using namespace gf;

//Класс инициализации
class init_game {
private:
    vector<RectangleShape> target, ray_tr;
    vector <Vector2i> wall = {Vector2i(0, 1), Vector2i(0, 3), Vector2i(2, 3), Vector2i(1, 2)};
    
    //Основной алгоритм обнаружения расстояния до пересечения прямых в пространстве
    bool collision(Vector2f const &v11, Vector2f const &v12, Vector2f const &v21, Vector2f const &v22, Vector2f *crossing);
    
public:
    CircleShape player;
    ConvexShape sector;
    
    //Инициализация объектов карты
    void map_objs_init();
    
    //Инициализация сектора обзора
    void sector_init();
    
    //Алгоритм рисования вертикальных полосок
    void draw_lines(float current_angle, int ind);
    
    //Отрисовка всех объектов игры
    void draw_objs(RenderWindow& window);
};
#endif /* Init_game_hpp */
