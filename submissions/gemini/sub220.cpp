#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector to store polygon vertices
#include <cmath>    // Required for mathematical functions like std::sqrt, std::acos, std::max, std::min
#include <algorithm> // Required for std::max and std::min
#include <iomanip>  // Required for std::fixed and std::setprecision for output formatting

// Define a Point structure to represent 2D coordinates.
// Using long long for coordinates to handle values up to 10^6,
// ensuring that intermediate squared distances and dot products (which can be up to 8 * 10^12)
// do not overflow standard int types.
struct Point {
    long long x, y;
};

// Function to calculate the squared Euclidean distance between two points.
// Returns long long to maintain precision for large coordinates before converting to double.
long long distSq(Point p1, Point p2) {
    long long dx = p1.x - p2.x;
    long long dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

// Function to calculate the squared distance from a point P to a line segment AB.
// This function finds the point on the segment AB that is closest to P,
// and returns the squared distance from P to that closest point.
// Returns double because the closest point might have fractional coordinates if it's a projection.
double distSqPointSegment(Point p, Point a, Point b) {
    // Vector representing the segment AB.
    long long ab_x = b.x - a.x;
    long long ab_y = b.y - a.y;

    // Vector from point A to point P.
    long long ap_x = p.x - a.x;
    long long ap_y = p.y - a.y;

    // Calculate the dot product of AP and AB.
    // This helps determine where the projection of P falls relative to the segment.
    long long dot_product = ap_x * ab_x + ap_y * ab_y;

    // Calculate the squared length of the segment AB.
    long long len_sq_ab = ab_x * ab_x + ab_y * ab_y;

    // Handle the case where A and B are the same point (degenerate segment).
    // In this case, the segment is just a point, so the distance is from P to A.
    if (len_sq_ab == 0) {
        return static_cast<double>(distSq(p, a));
    }

    // Calculate the parameter 't' for the projection of P onto the line containing AB.
    // t = (AP . AB) / |AB|^2.
    // If t is between 0 and 1, the projection lies on the segment.
    // If t < 0, the projection is outside the segment, closer to A.
    // If t > 1, the projection is outside the segment, closer to B.
    double t = static_cast<double>(dot_product) / len_sq_ab;

    if (t < 0.0) {
        // The closest point on the segment is A.
        return static_cast<double>(distSq(p, a));
    } else if (t > 1.0) {
        // The closest point on the segment is B.
        return static_cast<double>(distSq(p, b));
    } else {
        // The projection of P lies on the segment AB.
        // Calculate the coordinates of this projected point.
        double closest_x = a.x + t * ab_x;
        double closest_y = a.y + t * ab_y;
        // Calculate the squared distance from P to this projected point.
        double dx = p.x - closest_x;
        double dy = p.y - closest_y;
        return dx * dx + dy * dy;
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Number of vertices of the polygon.
    Point p_center; // The coordinates of point P, the center of rotation.

    // Read the number of vertices and the coordinates of point P.
    std::cin >> n >> p_center.x >> p_center.y;

    // Create a vector to store the vertices of the polygon.
    std::vector<Point> vertices(n);
    // Read the coordinates of each vertex.
    for (int i = 0; i < n; ++i) {
        std::cin >> vertices[i].x >> vertices[i].y;
    }

    // Calculate R_max_sq: the maximum squared distance from P to any point in the polygon.
    // For any polygon (convex or non-convex), the point furthest from an external point P
    // will always be one of its vertices.
    double r_max_sq = 0.0;
    for (int i = 0; i < n; ++i) {
        r_max_sq = std::max(r_max_sq, static_cast<double>(distSq(p_center, vertices[i])));
    }

    // Calculate R_min_sq: the minimum squared distance from P to any point in the polygon.
    // Since P is strictly outside the polygon, the minimum distance will be to a point
    // on the polygon's boundary (an edge or a vertex).
    // Initialize r_min_sq with a very large value, or r_max_sq as it's guaranteed to be >= actual min.
    double r_min_sq = r_max_sq; 
    
    // Iterate through all edges of the polygon.
    // An edge connects vertices[i] and vertices[(i + 1) % n] (for the last vertex, it connects to vertices[0]).
    for (int i = 0; i < n; ++i) {
        r_min_sq = std::min(r_min_sq, distSqPointSegment(p_center, vertices[i], vertices[(i + 1) % n]));
    }

    // The area cleared by the snow blower is an annulus (a ring shape).
    // Its area is PI * (R_max^2 - R_min^2).
    // We use acos(-1.0) to get a high-precision value for PI.
    const double PI = acos(-1.0);
    double area = PI * (r_max_sq - r_min_sq);

    // Print the calculated area.
    // std::fixed ensures floating-point numbers are printed in fixed-point notation.
    // std::setprecision(20) sets the number of digits after the decimal point to 20,
    // meeting the required precision for the output.
    std::cout << std::fixed << std::setprecision(20) << area << std::endl;

    return 0; // Indicate successful execution.
}