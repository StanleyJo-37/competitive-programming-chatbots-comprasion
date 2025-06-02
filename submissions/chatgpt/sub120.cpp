#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// Function to get the initial string of length a: "abc..."
// a: number of initial letters
string get_initial(int a) {
    string s = "";
    for (int i = 0; i < a; ++i) s += char('a' + i);
    return s;
}

// Function to get the computer's move given the current suffix of length a
// The computer picks a lexicographically minimal string of length a, all distinct, not in the suffix
string computer_move(const string& suffix, int a) {
    set<char> used(suffix.begin(), suffix.end());
    string t = "";
    char c = 'a';
    while (t.size() < a) {
        if (!used.count(c)) {
            t += c;
            used.insert(c);
        }
        ++c;
    }
    return t;
}

// Function to simulate the periodic block of the game
// Returns the string of one full period (Mister B's move + computer's move)
string get_period(int a, int b) {
    string s = get_initial(a);
    // Mister B's move: to minimize the number of different letters in a segment, he should try to repeat a single letter if possible
    // He can always pick the same letter as the last letter of s, or any letter from the initial a letters
    // Let's try all possible choices for Mister B's move and pick the one that minimizes the number of different letters in the period
    int min_diff = a + b; // upper bound
    string best_period = "";
    for (char ch = 'a'; ch < 'a' + a; ++ch) {
        string s2 = s;
        for (int i = 0; i < b; ++i) s2 += ch;
        string t = computer_move(s2.substr(s2.size() - a, a), a);
        string period = "";
        for (int i = 0; i < b; ++i) period += ch;
        period += t;
        set<char> diff(period.begin(), period.end());
        if ((int)diff.size() < min_diff) {
            min_diff = diff.size();
            best_period = period;
        }
    }
    return best_period;
}

// Function to get the minimum number of different letters in any segment of length seg_len in the period string
int min_diff_in_segment(const string& period, int seg_len) {
    int n = period.size();
    int min_diff = seg_len;
    for (int i = 0; i + seg_len <= n; ++i) {
        set<char> diff(period.begin() + i, period.begin() + i + seg_len);
        min_diff = min(min_diff, (int)diff.size());
    }
    return min_diff;
}

int main() {
    int a, b;
    long long l, r;
    cin >> a >> b >> l >> r;

    // The string is constructed as:
    // [initial a letters] + [period of (b + a) letters repeated]
    // The period is: Mister B's b letters + computer's a letters

    // If the segment [l, r] is fully inside the initial string, answer is just the number of different letters in that segment
    if (r <= a) {
        // All letters are distinct in the initial string
        cout << (r - l + 1) << endl;
        return 0;
    }

    // Otherwise, the segment may overlap the initial string and the periodic part
    // Let's find the period string
    string period = get_period(a, b);
    int period_len = b + a;

    // The segment [l, r] may be very large, but the string is periodic after the first a letters
    // So, the minimum number of different letters in any segment of length up to period_len in the period is the answer

    // The segment [l, r] can be at most r - l + 1 in length
    // But the minimum is achieved in a segment of length min(r - l + 1, period_len)
    int seg_len = min((long long)period_len, r - l + 1);

    // The minimum number of different letters in any segment of length seg_len in the period
    int ans = min_diff_in_segment(period, seg_len);

    // But if l <= a, the segment starts in the initial string, so we need to check the overlap
    if (l <= a) {
        // The segment from l to min(r, a) is in the initial string
        int len1 = min(r, (long long)a) - l + 1;
        // All letters are distinct in the initial string
        ans = min(ans, len1);
        // The rest is in the periodic part, so we need to check the segment that starts at the end of the initial string and continues into the period
        if (r > a) {
            int len2 = r - a;
            // The segment is: last (a - l + 1) letters of initial + first (r - a) letters of the period
            string s = get_initial(a).substr(l - 1, a - l + 1) + period.substr(0, len2);
            set<char> diff(s.begin(), s.end());
            ans = min(ans, (int)diff.size());
        }
    }

    cout << ans << endl;
    return 0;
}