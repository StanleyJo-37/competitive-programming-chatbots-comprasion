#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    // Read 8 points
    vector<pair<int, int>> points(8);
    set<int> xs, ys;
    for (int i = 0; i < 8; ++i) {
        cin >> points[i].first >> points[i].second;
        xs.insert(points[i].first);
        ys.insert(points[i].second);
    }

    // To be "respectable", there must be exactly 3 distinct x and 3 distinct y
    if (xs.size() != 3 || ys.size() != 3) {
        cout << "ugly" << endl;
        return 0;
    }

    // Sort the x and y values to get x1 < x2 < x3 and y1 < y2 < y3
    vector<int> vx(xs.begin(), xs.end());
    vector<int> vy(ys.begin(), ys.end());

    // Build the set of all 9 possible points (x_i, y_j)
    set<pair<int, int>> all_points;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            all_points.insert({vx[i], vy[j]});

    // Remove the center point (x2, y2)
    all_points.erase({vx[1], vy[1]});

    // Now, the input points must match exactly the 8 points in all_points
    set<pair<int, int>> input_points(points.begin(), points.end());

    if (input_points == all_points) {
        cout << "respectable" << endl;
    } else {
        cout << "ugly" << endl;
    }

    return 0;
}