#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    // Read input values
    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    // The problem is to maximize the total cost of suits made from the available items.
    // There are two types of suits:
    // 1. Type 1: 1 tie + 1 jacket, cost = e
    // 2. Type 2: 1 scarf + 1 vest + 1 jacket, cost = f
    // Each item can be used at most once.

    // Since both suit types require jackets, and jackets are the limiting resource,
    // we need to decide the order in which to make suits to maximize profit.

    // The greedy approach is to always make the more expensive suit first,
    // because jackets are the bottleneck.

    int max_cost = 0;

    // If suit type 1 is more expensive, make as many of them as possible first.
    if (e > f) {
        // Number of type 1 suits we can make is min(a, d)
        int type1 = min(a, d);
        d -= type1; // Use up jackets
        // Number of type 2 suits we can make is min(b, c, d)
        int type2 = min({b, c, d});
        max_cost = type1 * e + type2 * f;
    } else {
        // Otherwise, make as many type 2 suits as possible first.
        int type2 = min({b, c, d});
        d -= type2; // Use up jackets
        int type1 = min(a, d);
        max_cost = type2 * f + type1 * e;
    }

    // Output the result
    cout << max_cost << endl;
    return 0;
}