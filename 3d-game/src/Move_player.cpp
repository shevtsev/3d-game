#include "../Headers/Move_player.hpp"

//Движение во все стороны
void move_player::move(ConvexShape& sector, CircleShape& player, float const &current_angle) {
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        float dx = speed*cosf(rad(current_angle)), dy = speed*sinf(rad(current_angle));
        sector.move(dx, dy);
        player.move(dx, dy);
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        float dx = speed*cosf(rad(current_angle+180.f)), dy = speed*sinf(rad(current_angle+180.f));
        sector.move(dx, dy);
        player.move(dx, dy);
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        float dx = speed*cosf(rad(current_angle-90.f)), dy = speed*sinf(rad(current_angle-90.f));
        sector.move(dx, dy);
        player.move(dx, dy);
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        float dx = speed*cosf(rad(current_angle+90.f)), dy = speed*sinf(rad(current_angle+90.f));
        sector.move(dx, dy);
        player.move(dx, dy);
    }
}

//Поворот камеры
void move_player::rotation(ConvexShape& sector, float const &current_angle) {
    if (Keyboard::isKeyPressed(Keyboard::Left)){
        sector.setRotation(current_angle-step_ang);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)){
        sector.setRotation(current_angle+step_ang);
    }
}
