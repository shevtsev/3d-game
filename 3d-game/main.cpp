#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;

//Все константы игры
const int n = 802;
const Vector2f screen(800.f, 600.f);
const float radius = 100.f; //радиус угла обзора

//Перевод из градусов в радианы
static float rad(float angle) {
    return (angle*3.141592653f)/180.f;
}

//Класс всей математики
class math {
public:
    //Минимальное расстояние до объекта
    float min_d(vector<pair<float, Vector2f>> a) {
        float cnt = 0;
        for (int i = 1; i < a.size(); ++i)
            if (a[i].first < a[cnt].first)
                cnt = i;
        return cnt;
    }

    //Округление в пределах +- 0,01
    bool round_c(float x, float target) {
        if (fabs(target - x) < 0.01f) {
            return true;
        }
        return false;
    }

    //Основной алгоритм обнаружения расстояния до пересечения прямых в пространстве
    bool collision(Vector2f const &v11, Vector2f const &v12, Vector2f const &v21, Vector2f const &v22, Vector2f *crossing) {
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
};

//Класс передвижения
class move_player {
public:
    //Движение во все стороны
    void move(ConvexShape& sector, CircleShape& player, float current_angle) {
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
    void rotation(ConvexShape& sector, Vector2f screen, float current_angle) {
        float step_ang = 4.5f;
        if (Mouse::getPosition().x < screen.x/2){
            sector.setRotation(current_angle-step_ang);
        }
        if (Mouse::getPosition().x > screen.x/2){
            sector.setRotation(current_angle+step_ang);
        }
    }
};

//Класс инициализации
class init_game:public math {
public:
    CircleShape player;
    ConvexShape sector;
    vector<RectangleShape> target, ray_tr;
    vector <Vector2i> wall = {Vector2i(0, 1), Vector2i(0, 3), Vector2i(2, 3), Vector2i(1, 2)};
    
    //Инициализация объектов карты
    void map_objs_init() {
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
    void sector_init() {
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
    void draw_lines(float current_angle) {
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
    void draw_objs(RenderWindow& window) {
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
};

int main(int, char const**)
{
    move_player m_obj;
    math math_obj;
    init_game init;
    init.map_objs_init();
    init.sector_init();
    RenderWindow window(VideoMode(screen.x, screen.y), "SFML window");
    while (window.isOpen())
    {
        //Вращение игрока
        float current_angle = init.sector.getRotation();
        m_obj.rotation(init.sector, screen, current_angle);
        init.draw_lines(current_angle);
        Mouse::setPosition(Vector2i(screen.x/2, screen.y/2));
        
        //Движение игрока
        m_obj.move(init.sector, init.player, current_angle);
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
        init.draw_objs(window);
        
    }

    return EXIT_SUCCESS;
}
