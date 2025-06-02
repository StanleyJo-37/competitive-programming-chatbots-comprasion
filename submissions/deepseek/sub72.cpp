#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> songs(n);
    for (int i = 0; i < n; ++i) {
        cin >> songs[i].second >> songs[i].first; // (beauty, length)
    }

    // Sort songs in descending order of beauty to process songs with higher beauty first
    sort(songs.begin(), songs.end(), greater<pair<int, int>>());

    long long max_pleasure = 0;
    long long sum_length = 0;
    // Min-heap to keep track of the smallest lengths in the current set
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < n; ++i) {
        int b = songs[i].first;
        int t = songs[i].second;
        
        // Add current song's length to the sum
        sum_length += t;
        pq.push(t);

        // If we have more than k songs, remove the one with smallest length
        if (pq.size() > k) {
            sum_length -= pq.top();
            pq.pop();
        }

        // Current pleasure is sum_length * current beauty (since songs are sorted by beauty)
        max_pleasure = max(max_pleasure, sum_length * b);
    }

    cout << max_pleasure << '\n';
    return 0;
}