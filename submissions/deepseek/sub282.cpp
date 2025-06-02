#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> H(N);
    for (int i = 0; i < N; ++i) {
        cin >> H[i];
    }

    unordered_map<int, int> arrow_counts;

    for (int i = 0; i < N; ++i) {
        int h = H[i];
        // If there's an arrow at height h, it can pop this balloon and continue at h-1
        if (arrow_counts[h] > 0) {
            arrow_counts[h]--;
            arrow_counts[h - 1]++;
        } else {
            // Need a new arrow for this balloon
            arrow_counts[h - 1]++;
        }
    }

    int total_arrows = 0;
    for (auto& pair : arrow_counts) {
        total_arrows += pair.second;
    }

    cout << total_arrows << endl;

    return 0;
}