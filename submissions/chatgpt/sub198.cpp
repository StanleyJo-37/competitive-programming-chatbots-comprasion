#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    // Read the number of breakfasts, dinners, and suppers
    long long b, d, s;
    cin >> b >> d >> s;

    // Find the maximum number of any meal
    long long mx = max({b, d, s});

    // For each meal type, the maximum possible number of that meal is at most
    // (max of the other two) + 1, because Vasiliy could have arrived before that meal
    // and left after that meal, so the difference between the counts of any two meals
    // cannot be more than 1 in the optimal scenario.

    // The minimum number of missed meals is the sum over all meal types of:
    // max(0, mx - 1 - count of that meal)
    // This is because, for the meal type with the maximum count, he could have had
    // all those meals, but for the other two, if they are less than (mx - 1), he must have missed some.

    long long missed = 0;
    missed += max(0LL, mx - 1 - b);
    missed += max(0LL, mx - 1 - d);
    missed += max(0LL, mx - 1 - s);

    cout << missed << endl;
    return 0;
}