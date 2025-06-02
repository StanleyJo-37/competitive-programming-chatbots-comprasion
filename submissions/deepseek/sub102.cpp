#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<string> s(n - k + 1);
    for (int i = 0; i < n - k + 1; ++i) {
        cin >> s[i];
    }

    vector<string> names(n);
    // Generate unique names for the first k soldiers
    for (int i = 0; i < k; ++i) {
        names[i] = "A" + string(1, 'a' + i);
    }

    // Process each group starting from position i+1
    for (int i = 0; i < n - k + 1; ++i) {
        if (s[i] == "NO") {
            // The group from i to i+k-1 is not effective, so names[i] must equal names[i+k-1]
            names[i + k - 1] = names[i];
        } else {
            // The group is effective, ensure all names in this group are unique
            // If the last name in the group is not set, set it to a new unique name
            if (i + k - 1 >= names.size()) continue;
            if (i + k - 1 < names.size() && names[i + k - 1].empty()) {
                // Generate a new unique name
                names[i + k - 1] = "A" + string(1, 'a' + (i + k - 1));
            }
        }
    }

    // Fill any remaining names that might be empty (though constraints should prevent this)
    for (int i = 0; i < n; ++i) {
        if (names[i].empty()) {
            names[i] = "A" + string(1, 'a' + i);
        }
    }

    // Output the names
    for (int i = 0; i < n; ++i) {
        cout << names[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;

    return 0;
}