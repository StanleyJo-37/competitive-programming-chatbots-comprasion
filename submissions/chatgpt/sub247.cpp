#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Helper function to find the maximum length of substring consisting of only 'ch'
// after changing at most k other characters
int maxBeauty(const string& s, int k, char ch) {
    int n = s.size();
    int max_len = 0;
    int left = 0, count = 0;
    // Sliding window: right is the end of the window
    for (int right = 0; right < n; ++right) {
        // If current character is not ch, increment count (number of changes needed)
        if (s[right] != ch) count++;
        // If count exceeds k, move left pointer to reduce count
        while (count > k) {
            if (s[left] != ch) count--;
            left++;
        }
        // Update maximum length found so far
        max_len = max(max_len, right - left + 1);
    }
    return max_len;
}

int main() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    // Compute the answer for both 'a' and 'b', take the maximum
    int ans = max(maxBeauty(s, k, 'a'), maxBeauty(s, k, 'b'));
    cout << ans << endl;
    return 0;
}