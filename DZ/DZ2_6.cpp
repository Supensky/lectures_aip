#include <cmath>
#include <iostream>

struct Point3D {
    double x, y, z;
    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    double distance(Point3D p) const {
        double dx = x - p.x;
        double dy = y - p.y;
        double dz = z - p.z;
        return sqrt(dx*dx + dy*dy + dz*dz);
    }
};

class Sphere {
private:
    Point3D center;
    double radius;

public:
    // Конструкторы
    Sphere() : center(0, 0, 0), radius(1) {}
    Sphere(Point3D center, double radius) {
        this -> center = center;
        setRadius(radius);
    }
    Sphere(double x, double y, double z, double r) {
        center = {x, y, z};
        setRadius(r);
    }

    // Геттеры
    Point3D getCenter() const { return center; }
    double getRadius() const { return radius; }

    // Сеттеры
    void setCenter(Point3D c) { center = c; }
    void setRadius(double r) {
        if (r <= 0) throw std::invalid_argument("Radius must be positive");
        radius = r;
    }

    // Пересечение сфер
    static bool notCross(const Sphere& a, const Sphere& b) {
        double d = a.center.distance(b.center);
        double r1 = a.getRadius(), r2 = b.getRadius();
        return d > r1 + r2 || d < std::fabs(r1 - r2);
    }
};

int main() {
    // Не пересекается
    std::cout << Sphere::notCross(Sphere(0, 0, 0, 1), Sphere(5, 0, 0, 1)) << "\n";
    // Касаются снаружи
    std::cout << Sphere::notCross(Sphere(0, 0, 0, 1), Sphere(2, 0, 0, 1)) << "\n";
    // Пересекаются
    std::cout << Sphere::notCross(Sphere(0, 0, 0, 2), Sphere(3, 0, 0, 2)) << "\n";
    // Одна внутри другой
    std::cout << Sphere::notCross(Sphere(0, 0, 0, 5), Sphere(1, 0, 0, 1)) << "\n";
}