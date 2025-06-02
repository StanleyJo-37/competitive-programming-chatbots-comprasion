#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Helper function to generate unique names for soldiers
string generateName(int idx) {
    // Generate names like: Aa, Ab, Ac, ..., Az, Ba, Bb, ..., Zz, Aaa, etc.
    string name;
    int first = idx / 26;
    int second = idx % 26;
    name += char('A' + first);
    name += char('a' + second);
    return name;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<string> s(n - k + 1);
    for (int i = 0; i < n - k + 1; ++i) {
        cin >> s[i];
    }

    vector<string> names(n);

    // Assign unique names to the first k-1 soldiers
    for (int i = 0; i < k - 1; ++i) {
        names[i] = generateName(i);
    }

    int nameIdx = k - 1; // Next unique name index

    // For each group starting at i, decide the name for soldier at i + k - 1
    for (int i = 0; i < n - k + 1; ++i) {
        if (s[i] == "YES") {
            // Assign a new unique name
            names[i + k - 1] = generateName(nameIdx++);
        } else {
            // Assign the same name as the first soldier in the current group
            names[i + k - 1] = names[i];
        }
    }

    // Output the names
    for (int i = 0; i < n; ++i) {
        cout << names[i];
        if (i != n - 1) cout << " ";
    }
    cout << endl;
    return 0;
}