#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    int n, r;
    std::cin >> n >> r;

    // The problem reduces to finding R such that the centers of the outer circles
    // form a regular n-gon around the inner circle. The distance between the center
    // of the inner circle and any outer circle is (r + R). The angle between two adjacent
    // outer circles is 2π/n. The distance between centers of two adjacent outer circles is 2R.
    // Using the Law of Cosines on the triangle formed by the inner circle and two adjacent outer circles:
    // (2R)^2 = (r + R)^2 + (r + R)^2 - 2*(r + R)*(r + R)*cos(2π/n)
    // Simplifying, we get: R = (r * sin(π/n)) / (1 - sin(π/n))
    double pi = acos(-1);
    double angle = pi / n;
    double R = (r * sin(angle)) / (1 - sin(angle));

    // Set precision to 7 decimal places to meet the problem's requirements
    std::cout << std::fixed << std::setprecision(7) << R << std::endl;
    return 0;
}