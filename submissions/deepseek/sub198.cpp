#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    long long b, d, s;
    cin >> b >> d >> s;

    // The idea is to find the maximum among b, d, s. The minimal missed meals
    // occur when the maximum count is either equal to or just one more than the others.
    // If all three are equal, no meals are missed.
    // Otherwise, the minimal missed meals is (max_val - 1) for each of the other two meals,
    // but only if their current count is less than (max_val - 1).
    long long max_meal = max({b, d, s});
    long long missed = 0;

    // Calculate missed meals for each type if they are less than (max_meal - 1)
    if (b < max_meal - 1) missed += (max_meal - 1 - b);
    if (d < max_meal - 1) missed += (max_meal - 1 - d);
    if (s < max_meal - 1) missed += (max_meal - 1 - s);

    cout << missed << endl;
    return 0;
}