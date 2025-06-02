#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    // We use two deques to keep track of the indices of the minimum and maximum values in the current window.
    deque<int> minq, maxq;
    int l = 0, ans = 0;

    for(int r = 0; r < n; ++r) {
        // Maintain minq: remove from back while current value is less than the last in minq
        while(!minq.empty() && a[r] <= a[minq.back()]) minq.pop_back();
        minq.push_back(r);

        // Maintain maxq: remove from back while current value is greater than the last in maxq
        while(!maxq.empty() && a[r] >= a[maxq.back()]) maxq.pop_back();
        maxq.push_back(r);

        // If the difference between max and min in the window is more than 1, move left pointer
        while(a[maxq.front()] - a[minq.front()] > 1) {
            // Move left pointer forward, and pop from deques if their front is out of window
            ++l;
            if(minq.front() < l) minq.pop_front();
            if(maxq.front() < l) maxq.pop_front();
        }

        // Update the answer with the current window size
        ans = max(ans, r - l + 1);
    }

    cout << ans << endl;
    return 0;
}