#ifndef Math_hpp
#define Math_hpp

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

using namespace sf;
using namespace std;

class math {
public:
    //Минимальное расстояние до объекта
    float min_d(vector<pair<float, Vector2f>> a);

    //Округление в пределах +- 0,01
    bool round_c(float x, float target);

    //Основной алгоритм обнаружения расстояния до пересечения прямых в пространстве
    bool collision(Vector2f const &v11, Vector2f const &v12, Vector2f const &v21, Vector2f const &v22, Vector2f *crossing);
};

#endif /* Math_hpp */
