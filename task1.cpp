#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

class Triangle {
protected:
    double a, b, c; // triangle sides

public:
    Triangle(double a = 1, double b = 1, double c = 1) {
        if (isValid(a, b, c)) {
            this->a = a;
            this->b = b;
            this->c = c;
        } else {
            throw std::invalid_argument("Invalid triangle.");
        }
    }

    bool isValid(double a, double b, double c) {
        return (a + b > c && a + c > b && b + c > a);
    }

    void setSides(double a, double b, double c) {
        if (isValid(a, b, c)) {
            this->a = a;
            this->b = b;
            this->c = c;
        } else {
            throw std::invalid_argument("Invalid triangle.");
        }
    }

    double getPerimeter() const {
        return a + b + c;
    }

    void getAngles(double& A, double& B, double& C) const {
        // Law of cosines
        A = acos((b*b + c*c - a*a) / (2 * b * c)) * 180 / PI;
        B = acos((a*a + c*c - b*b) / (2 * a * c)) * 180 / PI;
        C = 180.0 - A - B;
    }

    void printSides() const {
        std::cout << "Sides: a = " << a << ", b = " << b << ", c = " << c << std::endl;
    }
};

class Equilateral : public Triangle {
private:
    double area;

public:
    Equilateral(double side) : Triangle(side, side, side), area(0.0) {}

    void calculateArea() {
        // Area formula for equilateral triangle: (sqrt(3) / 4) * a^2
        area = (sqrt(3) / 4.0) * a * a;
    }

    double getArea() const {
        return area;
    }
};

int main() {
    try {
        Triangle t(3, 4, 5);
        t.printSides();
        std::cout << "Perimeter: " << t.getPerimeter() << std::endl;
        double A, B, C;
        t.getAngles(A, B, C);
        std::cout << "Angles: A = " << A << "°, B = " << B << "°, C = " << C << "°" << std::endl;

        Equilateral eq(5);
        eq.calculateArea();
        eq.printSides();
        std::cout << "Equilateral triangle perimeter: " << eq.getPerimeter() << std::endl;
        std::cout << "Equilateral triangle area: " << eq.getArea() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
