#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> tags(n);
    for (int i = 0; i < n; ++i) {
        cin >> tags[i];
    }

    // Process from the end to the beginning to ensure lex order
    for (int i = n - 2; i >= 0; --i) {
        string &current = tags[i];
        string &next = tags[i + 1];
        
        // If current is already <= next, no need to modify
        if (current <= next) {
            continue;
        }

        // Find the minimal prefix of current that is <= next
        // Compare character by character up to next's length
        int len = min(current.size(), next.size());
        int pos = 1; // Start after '#'
        while (pos < len && current[pos] == next[pos]) {
            pos++;
        }
        
        if (pos < len) {
            if (current[pos] < next[pos]) {
                // No need to truncate, already lex smaller
                continue;
            } else {
                // Truncate to pos characters (including '#')
                current.resize(pos);
            }
        } else {
            // One is prefix of the other
            if (current.size() > next.size()) {
                // Truncate to next's size
                current.resize(next.size());
            }
        }
    }

    for (const string &tag : tags) {
        cout << tag << '\n';
    }

    return 0;
}