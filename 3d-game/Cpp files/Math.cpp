#include "Math.hpp"
//Минимальное расстояние до объекта
float math::min_d(vector<pair<float, Vector2f>> a) {
    float cnt = 0;
    for (int i = 1; i < a.size(); ++i)
        if (a[i].first < a[cnt].first)
            cnt = i;
    return cnt;
}

//Округление в пределах +- 0,01
bool math::round_c(float x, float target) {
    if (fabs(target - x) < 0.01f) {
        return true;
    }
    return false;
}

//Основной алгоритм обнаружения расстояния до пересечения прямых в пространстве
bool math::collision(Vector2f const &v11, Vector2f const &v12, Vector2f const &v21, Vector2f const &v22, Vector2f *crossing) {
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

