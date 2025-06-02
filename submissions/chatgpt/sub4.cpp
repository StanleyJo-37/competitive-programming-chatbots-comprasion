#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> notes(n);
        for (int i = 0; i < n; ++i) {
            cin >> notes[i];
        }

        set<int> used; // To store the unique notes after possible increment

        // For each note, try to add it to the set.
        // If it's already present, try to add note+1.
        for (int i = 0; i < n; ++i) {
            if (used.find(notes[i]) == used.end()) {
                // If notes[i] is not used, use it.
                used.insert(notes[i]);
            } else if (used.find(notes[i] + 1) == used.end()) {
                // If notes[i] is used, but notes[i]+1 is not, use notes[i]+1.
                used.insert(notes[i] + 1);
            }
            // If both are used, do nothing (cannot increase further).
        }

        // The size of the set is the maximal diversity.
        cout << used.size() << '\n';
    }
    return 0;
}