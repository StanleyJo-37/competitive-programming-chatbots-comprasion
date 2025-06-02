#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // The graph G will have edges between elements that are compared and swapped during Bubble Sort.
    // The key observation is that the graph G is a comparability graph (it's a permutation graph).
    // The maximum independent set in a permutation graph is equal to the length of the longest decreasing subsequence (LDS).
    // This is because in a permutation graph, the largest set of non-adjacent vertices corresponds to the longest sequence of elements that are in decreasing order.
    
    // We will compute the length of the longest decreasing subsequence (LDS) to find the answer.
    vector<int> lds;
    for (int num : a) {
        auto it = lower_bound(lds.begin(), lds.end(), num, greater<int>());
        if (it == lds.end()) {
            lds.push_back(num);
        } else {
            *it = num;
        }
    }
    
    cout << lds.size() << endl;
    return 0;
}