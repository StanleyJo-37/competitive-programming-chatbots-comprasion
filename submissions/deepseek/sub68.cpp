#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(m);
    
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    
    long long result = LLONG_MAX;
    
    // Tommy hides one of his lanterns (i), then Banban picks the best pair (a[j] * b[k]) from the remaining.
    for (int hide = 0; hide < n; ++hide) {
        long long max_product = LLONG_MIN;
        // Iterate over all possible pairs (a[j], b[k]) where j != hide.
        for (int j = 0; j < n; ++j) {
            if (j == hide) continue;
            for (int k = 0; k < m; ++k) {
                long long product = a[j] * b[k];
                if (product > max_product) {
                    max_product = product;
                }
            }
        }
        // Tommy wants the minimal possible max_product after hiding one lantern.
        if (max_product < result) {
            result = max_product;
        }
    }
    
    cout << result << endl;
    return 0;
}