#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long a, b, l, r;
    cin >> a >> b >> l >> r;

    long long cycle_len = a + b;
    long long num_chars_in_cycle = 26;

    if (a + b > 26) {
        set<char> distinct_chars;
        long long current_pos = 1;
        
        // Initial string
        for (int i = 0; i < a; ++i) {
            if (current_pos >= l && current_pos <= r) {
                distinct_chars.insert('a' + i);
            }
            current_pos++;
        }

        // Mister B's first move
        for (int i = 0; i < b; ++i) {
            if (current_pos >= l && current_pos <= r) {
                distinct_chars.insert('a'); 
            }
            current_pos++;
        }

        // Computer's first move
        set<char> suffix_chars;
        for (int i = 0; i < a; ++i) {
            suffix_chars.insert('a' + (26 - a + i));
        }
        string computer_chars = "";
        for (int i = 0; i < 26 && computer_chars.length() < a; ++i) {
            if (suffix_chars.find('a' + i) == suffix_chars.end()) {
                computer_chars += ('a' + i);
            }
        }
        for (char c : computer_chars) {
            if (current_pos >= l && current_pos <= r) {
                distinct_chars.insert(c);
            }
            current_pos++;
        }

        if (r < l) { // Should not happen based on constraints but good practice
            cout << 0 << endl;
        } else if (l > current_pos) { // Segment starts after initial cycle
             
            cout << 26 << endl;

        } else {
            cout << distinct_chars.size() << endl;
        }

    } else { 
        set<char> distinct_chars;
        long long current_len = 0;

        // Phase 1: Initial 'a' characters
        for (int i = 0; i < a; ++i) {
            current_len++;
            if (current_len >= l && current_len <= r) {
                distinct_chars.insert('a' + i);
            }
        }

        if (r - l + 1 <= b) {
            cout << 1 << endl;
            return 0;
        }

        set<char> distinct_final_chars;
        long long current_overall_pos = 1;

        // Simulate the initial sequence
        for (long long i = 0; i < a; ++i) {
            if (current_overall_pos >= l && current_overall_pos <= r) {
                distinct_final_chars.insert('a' + i);
            }
            current_overall_pos++;
        }

        if (l > a && r <= a + b) { // Segment entirely within Mister B's first turn
            cout << 1 << endl;
            return 0;
        }

        long long ans;
        long long segment_len = r - l + 1;

        if (segment_len <= b) {
            ans = 1;
        } else if (r <= a) { // Segment completely within initial part
            ans = segment_len;
        } else if (l <= a && r <= a + b) { 
            ans = a - l + 1;
        } else { // Segment is long and potentially includes computer's moves, or starts after first block.
            // This is the general case where the periodic behavior `a+1` distinct characters (Mister B repeats 'a') dominates.
            ans = min(26LL, a + 1);
        }

        cout << ans << endl;

    }

    return 0;
}