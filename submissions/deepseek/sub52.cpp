#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    // The maximum number of type1 suits is min(a, d)
    int max_type1 = min(a, d);
    // The maximum number of type2 suits is min(b, c, d)
    int max_type2 = min({b, c, d});

    // We need to find the optimal split between type1 and type2 suits
    // Since jackets (d) are shared, the optimal is to maximize the total coins
    // We can either take as many type1 as possible first, or as many type2 as possible first
    // Compare both scenarios and pick the maximum
    int option1 = min(max_type1, d - max_type2) * e + max_type2 * f;
    int option2 = max_type1 * e + min(max_type2, d - max_type1) * f;

    cout << max(option1, option2) << endl;

    return 0;
}