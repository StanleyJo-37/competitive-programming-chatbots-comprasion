#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> cards(n);
    for (int i = 0; i < n; ++i) {
        cin >> cards[i];
    }

    int sereja = 0, dima = 0;
    int left = 0, right = n - 1;
    bool serejaTurn = true; // Sereja starts first

    while (left <= right) {
        int chosen;
        // Choose the larger of the two ends
        if (cards[left] > cards[right]) {
            chosen = cards[left];
            left++;
        } else {
            chosen = cards[right];
            right--;
        }

        // Add to the current player's score
        if (serejaTurn) {
            sereja += chosen;
        } else {
            dima += chosen;
        }

        // Switch turns
        serejaTurn = !serejaTurn;
    }

    cout << sereja << " " << dima << endl;
    return 0;
}