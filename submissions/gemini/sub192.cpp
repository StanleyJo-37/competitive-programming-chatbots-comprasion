#include <iostream> // Required for standard input/output operations (std::cin, std::cout, std::endl)
#include <cmath>    // Required for mathematical functions like std::sin and the M_PI constant
#include <iomanip>  // Required for output formatting manipulators like std::fixed and std::setprecision

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation,
    // further improving I/O performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;    // Declare an integer variable 'n' to store the number of outer circles.
    double r; // Declare a double variable 'r' to store the radius of the inner circle.
              // 'r' is read as a double because it will be used in floating-point calculations.

    // Read the input values for 'n' and 'r' from standard input.
    std::cin >> n >> r;

    // Problem Analysis and Formula Derivation:
    // 1. Visualize the setup: An inner circle (radius 'r') is surrounded by 'n' outer circles (radius 'R').
    //    The inner circle touches all outer circles externally.
    //    Each pair of neighboring outer circles also touches each other.
    //
    // 2. Geometric arrangement:
    //    - Place the center of the inner circle at the origin (0,0).
    //    - The centers of the 'n' outer circles will form a regular 'n'-gon around the origin.
    //
    // 3. Distances between centers:
    //    - Since the inner circle (radius 'r') touches an outer circle (radius 'R'),
    //      the distance from the center of the inner circle to the center of any outer circle is `r + R`.
    //    - Since two neighboring outer circles (each radius 'R') touch each other,
    //      the distance between their centers is `R + R = 2R`.
    //
    // 4. Form an isosceles triangle:
    //    Consider a triangle formed by:
    //    - The center of the inner circle (let's call it C_inner).
    //    - The center of one outer circle (C_outer_1).
    //    - The center of an adjacent outer circle (C_outer_2).
    //    This triangle has side lengths:
    //    - C_inner to C_outer_1: `r + R`
    //    - C_inner to C_outer_2: `r + R`
    //    - C_outer_1 to C_outer_2: `2R`
    //    This is an isosceles triangle.
    //
    // 5. Angle at the center:
    //    The 'n' outer circles are arranged symmetrically around the inner circle.
    //    The total angle around the inner circle's center is 360 degrees or `2 * PI` radians.
    //    Therefore, the angle subtended at C_inner by the segment C_outer_1 C_outer_2 is `(2 * PI) / n` radians.
    //
    // 6. Use trigonometry with a right-angled triangle:
    //    Draw an altitude from C_inner to the midpoint of the side C_outer_1 C_outer_2.
    //    This altitude bisects both the angle at C_inner and the side C_outer_1 C_outer_2.
    //    This creates a right-angled triangle with:
    //    - Hypotenuse: `r + R` (distance from C_inner to C_outer_1)
    //    - Angle opposite to one of its legs: `((2 * PI) / n) / 2 = PI / n` radians.
    //    - The leg opposite to this angle: `(2R) / 2 = R` (half the distance between outer circle centers).
    //
    // 7. Apply the sine function:
    //    `sin(angle) = Opposite / Hypotenuse`
    //    `sin(PI / n) = R / (r + R)`
    //
    // 8. Solve for R:
    //    `R = (r + R) * sin(PI / n)`
    //    `R = r * sin(PI / n) + R * sin(PI / n)`
    //    `R - R * sin(PI / n) = r * sin(PI / n)`
    //    `R * (1 - sin(PI / n)) = r * sin(PI / n)`
    //    `R = (r * sin(PI / n)) / (1 - sin(PI / n))`

    // Calculate the angle (in radians) for the sine function.
    // M_PI is a constant defined in <cmath> representing the value of PI.
    double angle_radians = M_PI / n;

    // Calculate the sine of the angle.
    double sin_val = std::sin(angle_radians);

    // Calculate the radius R using the derived formula.
    // Note: 1.0 is used to ensure floating-point division.
    double R_result = (r * sin_val) / (1.0 - sin_val);

    // Output the result.
    // std::fixed ensures that the number is printed in fixed-point notation (not scientific).
    // std::setprecision(9) sets the number of digits after the decimal point to 9.
    // This precision is typically sufficient to meet the 10^-6 error tolerance requirement.
    std::cout << std::fixed << std::setprecision(9) << R_result << std::endl;

    return 0; // Indicate successful program execution.
}