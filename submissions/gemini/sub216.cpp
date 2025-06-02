#include <iostream>
#include <vector>
#include <algorithm>

// Structure to hold car price and fuel tank capacity
struct Car {
    long long price;
    long long capacity;
};

// Comparison function for sorting cars by price
bool compareCars(const Car& a, const Car& b) {
    return a.price < b.price;
}

// Function to check if a car with given fuel tank capacity V can reach the cinema
// within target_t minutes.
// dists: vector of distances between consecutive points (0, gas stations, s)
// max_d_val: maximum distance among all segments in dists
bool check(long long V, long long target_t, const std::vector<long long>& dists, long long max_d_val) {
    // If the car's fuel capacity V is less than the maximum distance between any two
    // consecutive points (gas stations or start/end), it's impossible to cover that
    // distance even in normal mode (1 liter/km).
    // In normal mode, a car travels D km using D liters of fuel. If V < D, it's impossible.
    if (V < max_d_val) {
        return false;
    }

    long long current_time = 0;
    for (long long D : dists) {
        // For each segment of length D, we want to minimize time.
        // To minimize time, we maximize distance covered in accelerated mode (1 min/km, 2 liters/km).
        // Let x be distance in accelerated mode, y be distance in normal mode.
        // x + y = D
        // Fuel consumed: 2x + y <= V
        // Time taken: x + 2y
        // Substitute y = D - x into fuel constraint: 2x + (D - x) <= V  =>  x + D <= V  =>  x <= V - D
        // Also, x cannot exceed D (segment length) and x must be non-negative.
        // So, x_max = min(D, max(0LL, V - D)).
        // Since we already checked V >= max_d_val, we know V >= D for all D in dists.
        // Thus, V - D >= 0, so max(0LL, V - D) simplifies to V - D.
        long long x_max = std::min(D, V - D);

        // Calculate time for this segment:
        // x_max km in accelerated mode (1 min/km)
        // (D - x_max) km in normal mode (2 min/km)
        current_time += x_max * 1 + (D - x_max) * 2;

        // If total time already exceeds target_t, no need to continue
        if (current_time > target_t) {
            return false;
        }
    }
    return current_time <= target_t;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    long long s, t;
    std::cin >> n >> k >> s >> t;

    std::vector<Car> cars(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> cars[i].price >> cars[i].capacity;
    }

    std::vector<long long> gas_stations(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> gas_stations[i];
    }

    // Prepare points for segments: start (0), gas stations, and cinema (s)
    std::vector<long long> points;
    points.push_back(0);
    for (long long g_pos : gas_stations) {
        points.push_back(g_pos);
    }
    points.push_back(s);
    std::sort(points.begin(), points.end());

    // Calculate distances between consecutive points
    std::vector<long long> dists;
    long long max_d = 0; // Stores the maximum distance between any two consecutive points
    for (size_t i = 0; i < points.size() - 1; ++i) {
        long long d = points[i+1] - points[i];
        dists.push_back(d);
        if (d > max_d) {
            max_d = d;
        }
    }

    // Sort cars by price to enable binary search on price
    std::sort(cars.begin(), cars.end(), compareCars);

    // Precompute maximum fuel capacity for cars up to a certain index (sorted by price).
    // max_V_at_idx[i] stores the maximum capacity among cars[0]...cars[i].
    // This is because if we can afford cars up to index 'i', we can pick the one with highest capacity
    // to maximize our chances of meeting the time constraint.
    std::vector<long long> max_V_at_idx(n);
    if (n > 0) {
        max_V_at_idx[0] = cars[0].capacity;
        for (int i = 1; i < n; ++i) {
            max_V_at_idx[i] = std::max(max_V_at_idx[i-1], cars[i].capacity);
        }
    }

    long long min_affordable_price = -1; // Stores the minimum price found

    // Binary search for the minimum price
    // The search space is the indices of the sorted cars vector.
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid_idx = low + (high - low) / 2;
        long long current_V_to_check = max_V_at_idx[mid_idx];

        // Check if a car with capacity current_V_to_check can make it in time.
        // This capacity is the maximum available among cars with price <= cars[mid_idx].price.
        if (check(current_V_to_check, t, dists, max_d)) {
            // If it's possible, this price (cars[mid_idx].price) is a candidate.
            // Try to find a cheaper car (look in the left half by reducing high).
            min_affordable_price = cars[mid_idx].price;
            high = mid_idx - 1;
        } else {
            // If not possible, we need a car with higher capacity (and thus potentially higher price).
            // Look in the right half by increasing low.
            low = mid_idx + 1;
        }
    }

    std::cout << min_affordable_price << std::endl;

    return 0;
}