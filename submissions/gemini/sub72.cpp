#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector to store songs
#include <algorithm> // Required for std::sort and std::max
#include <queue>    // Required for std::priority_queue

// Define a struct to represent a song with its length and beauty.
// Using a struct makes the code more readable than using std::pair directly.
struct Song {
    int t; // Length of the song
    int b; // Beauty of the song
};

// Custom comparison function for sorting songs.
// We want to sort songs by their beauty in descending order.
// If two songs have the same beauty, their relative order doesn't affect the minimum beauty,
// so any tie-breaking (or stable sort) is fine.
bool compareSongs(const Song& s1, const Song& s2) {
    return s1.b > s2.b; // Sort in descending order of beauty
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Total number of songs in the playlist
    int k; // Maximum number of songs allowed to choose
    std::cin >> n >> k;

    // Create a vector to store all songs.
    std::vector<Song> songs(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> songs[i].t >> songs[i].b;
    }

    // Sort the songs based on their beauty in descending order.
    // This is the crucial step. By iterating through songs sorted this way,
    // when we consider songs[i], its beauty (songs[i].b) becomes a candidate
    // for the minimum beauty of our chosen set. All songs processed before
    // (songs[0] to songs[i-1]) have beauty greater than or equal to songs[i].b,
    // making them eligible to be part of the set if songs[i].b is the minimum.
    std::sort(songs.begin(), songs.end(), compareSongs);

    long long current_sum_t = 0; // Stores the sum of lengths of songs currently selected
    long long max_pleasure = 0;  // Stores the maximum pleasure found so far

    // A min-priority queue to keep track of the lengths of the songs we've chosen.
    // We use a min-priority queue because if we have more than 'k' songs,
    // we need to remove the one with the smallest length to maximize the sum.
    // std::priority_queue by default is a max-heap, so std::greater<int> is used for a min-heap.
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    // Iterate through the sorted songs.
    for (int i = 0; i < n; ++i) {
        // Add the current song's length to our running sum.
        current_sum_t += songs[i].t;
        // Add the current song's length to the priority queue.
        pq.push(songs[i].t);

        // If the number of songs in our priority queue (i.e., selected songs)
        // exceeds 'k', we must remove the song with the smallest length.
        // This ensures we always consider at most 'k' songs, and those are
        // the ones with the largest lengths among the eligible songs.
        if (pq.size() > k) {
            current_sum_t -= pq.top(); // Subtract the smallest length from the sum
            pq.pop();                   // Remove the smallest length from the priority queue
        }

        // At this point, 'current_sum_t' holds the sum of lengths of the
        // 'min(i+1, k)' songs with the largest lengths among songs[0]...songs[i].
        // The minimum beauty among these songs is guaranteed to be songs[i].b,
        // because all songs from songs[0] to songs[i] have beauty >= songs[i].b.
        // Calculate the pleasure for this set and update the maximum pleasure found.
        max_pleasure = std::max(max_pleasure, current_sum_t * songs[i].b);
    }

    // Print the maximum pleasure found.
    std::cout << max_pleasure << std::endl;

    return 0; // Indicate successful execution
}