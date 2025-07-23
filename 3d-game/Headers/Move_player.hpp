#ifndef Move_player_hpp
#define Move_player_hpp

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "Global_functions.hpp"

using namespace sf;
using namespace std;
using namespace gf;

//Класс передвижения
class move_player {
private:
    const float speed = 0.05f;
    const float step_ang = 3.f;
public:
    //Движение во все стороны
    void move(ConvexShape& sector, CircleShape& player, float const &current_angle);

    //Поворот камеры
    void rotation(ConvexShape& sector, float const &current_angle);
};
#endif /* Move_player_hpp */
