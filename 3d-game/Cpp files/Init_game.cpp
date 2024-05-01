#include "Init_game.hpp"

//Основной алгоритм обнаружения расстояния до пересечения прямых в пространстве (Private)
bool init_game::collision(Vector2f const &v11, Vector2f const &v12, Vector2f const &v21, Vector2f const &v22, Vector2f* crossing) {
    Vector2f dir1 = v12 - v11;
    Vector2f dir2 = v22 - v21;
    float det = dir1.x * dir2.y - dir1.y * dir2.x;
    if (fabs(det) < numeric_limits<float>::epsilon()) {
        return false;
    }
    
    // Расчет параметров для точки пересечения
    float t = ((v21.x - v11.x) * dir2.y - (v21.y - v11.y) * dir2.x) / det;
    float u = ((v21.x - v11.x) * dir1.y - (v21.y - v11.y) * dir1.x) / det;
    
    if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
        if (crossing) {
            crossing->x = v11.x + t * dir1.x;
            crossing->y = v11.y + t * dir1.y;
        }
        return true;
    }
    
    return false;
}

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
    for (int i = 0; i < n-2; ++i) {
        float angle = rad(-60.f / 2 + (60.f * i / (n-2))); // Распределение углов вдоль дуги
        sector.setPoint(i+1, Vector2f(cos(angle) * radius, sin(angle) * radius));
    }
    sector.setPoint(n-1, Vector2f(0, 0));
    player.setPosition(40, 30);
    player.setFillColor(Color::Red);
    sector.setPosition(45, 35);
    sector.setFillColor(Color::Green);
}

//Алгоритм рисования вертикальных полосок
void init_game::draw_lines(float current_angle, int ind) {
    Vector2f p_pos = player.getPosition()+Vector2f(5.f, 5.f), crossing;
    vector<float> min_dist;
    float angle = rad(-30.f+(60.f * (ind) / (n-2)));
    for (auto obj : target) {
        for (auto dots : wall) {
            if (collision(p_pos, Vector2f(radius*cosf(angle+rad(current_angle))+p_pos.x,radius*sinf(angle + rad(current_angle))+p_pos.y), obj.getPoint(dots.x)+obj.getPosition(), obj.getPoint(dots.y)+obj.getPosition(), &crossing)) {
                float dist = sqrtf(powf(p_pos.x-crossing.x, 2) + powf(p_pos.y-crossing.y, 2));
                min_dist.push_back(dist);
            }
        }
    }
    if (!min_dist.empty()) {
        sort(min_dist.begin(), min_dist.end());
        RectangleShape line;
        line.setSize(Vector2f(screen.x/(n-2), (screen.y/2) * (70/(min_dist[0]))));
        line.setPosition((screen.x/(n-2))*(ind), (screen.y-line.getSize().y)/2);
        line.setFillColor(Color::Black);
        for (float p = 7.f; p >= 1.f; p-=0.005f) {
            if (min_dist[0] < radius/p) {
                Uint8 x = 30 * p;
                line.setFillColor(Color(x, x, x));
                break;
            }
        }
        ray_tr.push_back(move(line));
    }
}
    
//Отрисовка всех объектов игры
void init_game::draw_objs(RenderWindow& window) {
    window.clear();
    for (auto to:ray_tr)
        window.draw(to);
    ray_tr.clear();
    for (auto to:target)
        window.draw(to);
    window.draw(sector);
    window.draw(player);
    window.display();
}
