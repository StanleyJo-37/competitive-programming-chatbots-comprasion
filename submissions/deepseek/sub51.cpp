#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        string S;
        cin >> N >> S;

        // Count occurrences of each color
        int R = count(S.begin(), S.end(), 'R');
        int G = count(S.begin(), S.end(), 'G');
        int B = count(S.begin(), S.end(), 'B');

        // The minimal repaints needed is total rooms minus the max count of any color
        // Because we can repaint the other colors to match the dominant one
        // However, we must consider the mixing rules:
        // If two colors are present, mixing them gives the third color.
        // So, for cases where two colors are present, the minimal repaints is min(R + G, G + B, R + B)
        // But if all three are present, the minimal is (total - max(R, G, B)) or (min(R + G, G + B, R + B) + 1)
        // But upon deeper analysis, the minimal repaints is always (N - max(R, G, B)) because:
        // - If one color dominates, repaint others to match it.
        // - If two colors are present, repaint the lesser to the dominant (no mixing needed).
        // - If all three are present, repaint two colors to the third via mixing (but the minimal is still N - max(R, G, B)).
        // For example, RGB: max is 1, so repaints 2 (as in sample 3).
        cout << N - max({R, G, B}) << '\n';
    }

    return 0;
}