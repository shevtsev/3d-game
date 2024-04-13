#include "Move_player.hpp"
//Движение во все стороны
void move_player::move(ConvexShape& sector, CircleShape& player, float current_angle) {
    float speed = 0.05f;
    vector<pair<bool, float>> key_ang = {{Keyboard::isKeyPressed(Keyboard::A), current_angle-90.f}, {Keyboard::isKeyPressed(Keyboard::W), current_angle}, {Keyboard::isKeyPressed(Keyboard::S),  current_angle+180.f}, {Keyboard::isKeyPressed(Keyboard::D), current_angle+90.f}};
    for (auto key : key_ang)
        if (key.first) {
            float dx = speed*cosf(rad(key.second)), dy = speed*sinf(rad(key.second));
            sector.move(dx, dy);
            player.move(dx, dy);
        }
}

//Поворот камеры
void move_player::rotation(ConvexShape& sector, Vector2f screen, float current_angle) {
    float step_ang = 4.5f;
    if (Mouse::getPosition().x < screen.x/2){
        sector.setRotation(current_angle-step_ang);
    }
    if (Mouse::getPosition().x > screen.x/2){
        sector.setRotation(current_angle+step_ang);
    }
}
