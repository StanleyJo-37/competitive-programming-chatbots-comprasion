#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;
        string S;
        cin >> S;

        bool strong = false;
        int current_streak = 0;

        for (char c : S) {
            if (c == '*') {
                current_streak++;
                if (current_streak >= K) {
                    strong = true;
                    break;
                }
            } else {
                current_streak = 0;
            }
        }

        cout << (strong ? "YES" : "NO") << '\n';
    }

    return 0;
}