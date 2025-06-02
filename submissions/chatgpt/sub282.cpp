#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> H(N);
    for (int i = 0; i < N; ++i) {
        cin >> H[i];
    }

    // We use a frequency array to keep track of how many arrows are currently at each height.
    // Since heights can be up to 1,000,000, we need an array of size 1,000,002 (to avoid out-of-bounds).
    vector<int> arrows(1'000'002, 0);

    int result = 0; // Number of arrows needed

    for (int i = 0; i < N; ++i) {
        int h = H[i];
        // If there is an arrow at height h+1, it can be used to pop this balloon.
        if (arrows[h + 1] > 0) {
            // Use the arrow at height h+1
            arrows[h + 1]--;
            // After popping, the arrow continues at height h
            arrows[h]++;
        } else {
            // No arrow can pop this balloon, so we need a new arrow
            result++;
            // The new arrow continues at height h-1 after popping this balloon
            arrows[h]++;
        }
    }

    cout << result << '\n';
    return 0;
}