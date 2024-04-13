#include "Init_game.hpp"

//Инициализация объектов карты
void init_game::map_objs_init() {
    target.resize(3);
    player.setRadius(5.f);
    target[0].setSize(Vector2f(100.f, 100.f));
    target[0].setOutlineThickness(3.f);
    target[0].setOutlineColor(sf::Color(95, 95, 95));
    target[1].setSize(Vector2f(40.f, 40.f));
    target[1].setPosition(50, 50);
    target[1].setFillColor(Color::Black);
    target[2].setSize(Vector2f(10.f, 10.f));
    target[2].setPosition(20, 30);
    target[2].setFillColor(Color::Black);
}
    
//Инициализация сектора обзора
void init_game::sector_init() {
    sector.setPointCount(n);
    sector.setFillColor(Color::White);
    sector.setPoint(0, Vector2f(0, 0)); // Центр круга
    for (int i = 1; i <= n-2; ++i) {
        float angle = rad(-60.f / 2 + (60.f * (i - 1) / (n-2))); // Распределение углов вдоль дуги
        sector.setPoint(i, Vector2f(cos(angle) * radius, sin(angle) * radius));
    }
    sector.setPoint(n-1, Vector2f(0, 0));
    player.setPosition(40, 30);
    player.setFillColor(Color::Red);
    sector.setPosition(45, 35);
    sector.setFillColor(Color::Green);
}
    
//Алгоритм рисования вертикальных полосок
void init_game::draw_lines(float current_angle) {
    for (int i = 1; i <= n-2; ++i) {
        Vector2f p_pos = player.getPosition()+Vector2f(5.f, 5.f), crossing;
        vector<pair<float, Vector2f>> min_dist;
        float angle = rad(-30.f+(60.f * (i - 1) / (n-2)));
        for (auto obj : target) {
            for (auto dots : wall) {
                if (collision(p_pos, Vector2f(radius*cosf(angle+rad(current_angle))+p_pos.x,radius*sinf(angle + rad(current_angle))+p_pos.y), obj.getPoint(dots.x)+obj.getPosition(), obj.getPoint(dots.y)+obj.getPosition(), &crossing)) {
                    float dist = sqrtf(powf(p_pos.x-crossing.x, 2) + powf(p_pos.y-crossing.y, 2));
                    min_dist.push_back({dist, crossing});
                }
            }
        }
        if (!min_dist.empty()) {
            pair<float, Vector2f> rez_dist = min_dist[min_d(min_dist)];
            RectangleShape line;
            line.setSize(Vector2f(screen.x/(n-2), (screen.y/2) * (70/rez_dist.first)));
            line.setPosition((screen.x/(n-2))*(i-1), (screen.y-line.getSize().y)/2);
            vector<Uint8> color(3);
            for (float p = 7.f; p >= 1.f; p-=0.01f) {
                if (rez_dist.first < radius/p) {
                    Uint8 x = 30 * p;
                    color = {x, x, x};
                    break;
                }
            }
            line.setFillColor(Color(color[0], color[1], color[2]));
            ray_tr.push_back(line);
            min_dist.clear();
        }
    }
}
    
//Отрисовка всех объектов игры
void init_game::draw_objs(RenderWindow& window) {
    window.clear();
    for (int i = 0; i < ray_tr.size(); ++i)
        window.draw(ray_tr[i]);
    for (int i = 0; i < target.size(); ++i)
        window.draw(target[i]);
    window.draw(sector);
    window.draw(player);
    ray_tr.clear();
    window.display();
}
