#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];

    // Tommy wants to minimize the maximum product Banban can get after hiding one of his lanterns
    long long result = LLONG_MAX;

    // Try hiding each of Tommy's lanterns one by one
    for (int hide = 0; hide < n; ++hide) {
        // Prepare Tommy's lanterns after hiding one
        vector<long long> tommy;
        for (int i = 0; i < n; ++i) {
            if (i != hide) tommy.push_back(a[i]);
        }

        // Banban will choose the pair (one from tommy, one from banban) with the maximum product
        long long max_product = LLONG_MIN;
        for (int i = 0; i < tommy.size(); ++i) {
            for (int j = 0; j < m; ++j) {
                long long prod = tommy[i] * b[j];
                if (prod > max_product) max_product = prod;
            }
        }

        // Tommy wants to minimize this maximum product
        if (max_product < result) result = max_product;
    }

    cout << result << endl;
    return 0;
}