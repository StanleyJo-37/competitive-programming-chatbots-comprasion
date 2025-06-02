#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    int n;
    double r;
    cin >> n >> r;

    // The centers of the outer circles are placed on a circle of radius (r + R)
    // The angle between centers of two adjacent outer circles is 2*PI/n
    // The distance between centers of two adjacent outer circles must be 2*R (since they touch)
    // The distance between centers of inner and outer circle is (r + R)
    // The chord length between two adjacent outer circle centers is:
    // 2 * (r + R) * sin(PI / n)
    // Set this equal to 2*R and solve for R:
    // 2 * (r + R) * sin(PI / n) = 2 * R
    // (r + R) * sin(PI / n) = R
    // r * sin(PI / n) + R * sin(PI / n) = R
    // r * sin(PI / n) = R * (1 - sin(PI / n))
    // R = r * sin(PI / n) / (1 - sin(PI / n))

    double sin_val = sin(M_PI / n);
    double R = (r * sin_val) / (1.0 - sin_val);

    // Output with at least 7 decimal places to meet the required precision
    cout << fixed << setprecision(7) << R << endl;

    return 0;
}