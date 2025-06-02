#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    // Separate trees into left and right of x=0
    vector<pair<int, int>> left, right; // (position, apples)
    for (int i = 0; i < n; ++i) {
        int x, a;
        cin >> x >> a;
        if (x < 0) left.push_back({x, a});
        else right.push_back({x, a});
    }

    // Sort left in decreasing order (closest to 0 first: -1, -2, ...)
    sort(left.begin(), left.end(), [](const pair<int,int>& p1, const pair<int,int>& p2){
        return p1.first > p2.first;
    });
    // Sort right in increasing order (closest to 0 first: 1, 2, ...)
    sort(right.begin(), right.end());

    // The optimal strategy is to start in the direction with fewer or equal trees,
    // and alternate as long as possible, collecting apples from both sides.
    // If both sides have the same number, we can collect all.
    // If not, we can collect from min(left.size(), right.size())*2 + 1 trees (starting from the side with more trees).

    int lsize = left.size();
    int rsize = right.size();

    int total1 = 0, total2 = 0;

    // Try starting from left
    int cnt = min(lsize, rsize + 1);
    for (int i = 0; i < cnt && i < lsize; ++i) total1 += left[i].second;
    for (int i = 0; i < cnt-1 && i < rsize; ++i) total1 += right[i].second;

    // Try starting from right
    cnt = min(rsize, lsize + 1);
    for (int i = 0; i < cnt && i < rsize; ++i) total2 += right[i].second;
    for (int i = 0; i < cnt-1 && i < lsize; ++i) total2 += left[i].second;

    // Output the maximum apples collected from both strategies
    cout << max(total1, total2) << endl;
    return 0;
}