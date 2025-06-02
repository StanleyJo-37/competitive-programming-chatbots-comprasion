#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Function to compute the maximum beauty by changing at most k characters to target (either 'a' or 'b')
int maxBeauty(const string &s, int k, char target) {
    int left = 0, max_len = 0, count = 0;
    for (int right = 0; right < s.size(); ++right) {
        if (s[right] != target) {
            ++count;
        }
        // Shrink the window from the left until count <= k
        while (count > k) {
            if (s[left] != target) {
                --count;
            }
            ++left;
        }
        // Update the maximum length found
        max_len = max(max_len, right - left + 1);
    }
    return max_len;
}

int main() {
    int n, k;
    string s;
    cin >> n >> k >> s;

    // The answer is the maximum between the best possible 'a' substring and the best possible 'b' substring
    int max_a = maxBeauty(s, k, 'a');
    int max_b = maxBeauty(s, k, 'b');
    cout << max(max_a, max_b) << endl;

    return 0;
}