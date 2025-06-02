#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    vector<pair<int, int>> points(8);
    set<int> x_coords, y_coords;

    // Read all 8 points and collect unique x and y coordinates
    for (int i = 0; i < 8; ++i) {
        cin >> points[i].first >> points[i].second;
        x_coords.insert(points[i].first);
        y_coords.insert(points[i].second);
    }

    // Check if there are exactly 3 distinct x and y coordinates
    if (x_coords.size() != 3 || y_coords.size() != 3) {
        cout << "ugly" << endl;
        return 0;
    }

    // Extract sorted x and y coordinates
    vector<int> xs(x_coords.begin(), x_coords.end());
    vector<int> ys(y_coords.begin(), y_coords.end());

    // Check if the middle point (x2, y2) is missing
    set<pair<int, int>> point_set(points.begin(), points.end());
    if (point_set.count({xs[1], ys[1]})) {
        cout << "ugly" << endl;
        return 0;
    }

    // Check all other 8 points exist
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 1 && j == 1) continue; // Skip the middle point
            if (!point_set.count({xs[i], ys[j]})) {
                cout << "ugly" << endl;
                return 0;
            }
        }
    }

    // If all conditions are met
    cout << "respectable" << endl;
    return 0;
}