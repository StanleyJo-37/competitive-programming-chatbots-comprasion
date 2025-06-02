#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// Struct to store song information
struct Song {
    long long t, b;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<Song> songs(n);
    for (int i = 0; i < n; ++i) {
        cin >> songs[i].t >> songs[i].b;
    }

    // Sort songs by beauty in descending order
    sort(songs.begin(), songs.end(), [](const Song &a, const Song &b) {
        return a.b > b.b;
    });

    // Min-heap to keep track of the k-1 largest lengths
    priority_queue<long long, vector<long long>, greater<long long>> minHeap;
    long long sum_lengths = 0;
    long long max_pleasure = 0;

    // Iterate through songs, treating each as the minimum beauty in a set
    for (int i = 0; i < n; ++i) {
        // Add current song's length to the heap and sum
        minHeap.push(songs[i].t);
        sum_lengths += songs[i].t;

        // If we have more than k songs, remove the smallest length
        if ((int)minHeap.size() > k) {
            sum_lengths -= minHeap.top();
            minHeap.pop();
        }

        // Calculate pleasure for current set (up to k songs)
        // The minimum beauty is songs[i].b (since all previous have >= this beauty)
        max_pleasure = max(max_pleasure, sum_lengths * songs[i].b);
    }

    cout << max_pleasure << '\n';
    return 0;
}