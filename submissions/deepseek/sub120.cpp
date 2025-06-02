#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

int main() {
    int a, b, l, r;
    cin >> a >> b >> l >> r;
    
    // The initial string is the first 'a' letters in order.
    // After that, Mister B adds 'b' letters, then the computer adds 'a' letters, and so on.
    // The computer's strategy is to pick the lex smallest 'a' distinct letters not in the last 'a' letters of the current string.
    
    // The key observation is that after a few moves, the string starts repeating in cycles.
    // The cycle length is at most 2*(a + b), but in practice, it's often smaller.
    // We need to find the cycle and then compute the answer based on the cycle.
    
    // We'll simulate the string generation until we detect a cycle or until the segment [l, r] is covered.
    // Since l and r can be up to 1e9, we can't simulate the entire string. Instead, we'll find the cycle.
    
    vector<char> s;
    for (int i = 0; i < a; ++i) {
        s.push_back('a' + i);
    }
    
    // We'll keep track of the string's state after each computer's move to detect cycles.
    // The state is defined by the last 'a' characters before the computer's move.
    // Once we see a repeated state, we know a cycle has started.
    
    vector<vector<char>> history;
    unordered_set<string> seen_states;
    string initial_state(s.end() - min(a, (int)s.size()), s.end());
    seen_states.insert(initial_state);
    history.push_back(s);
    
    int cycle_start = -1;
    int cycle_length = 0;
    vector<char> cycle_string;
    
    while (true) {
        // Mister B's turn: add 'b' arbitrary letters.
        // To minimize the number of distinct letters in [l, r], Mister B should add the same letter 'b' times.
        // The optimal letter is the one that already appears in the string, preferably the one that will be repeated.
        char best_char = s.back(); // Repeating the last character minimizes new distinct letters.
        for (int i = 0; i < b; ++i) {
            s.push_back(best_char);
        }
        
        // Computer's turn: add 'a' letters not in the last 'a' letters of s, lex smallest.
        unordered_set<char> last_a_chars(s.end() - a, s.end());
        vector<char> available_chars;
        for (char c = 'a'; c < 'a' + 2 * a; ++c) {
            if (last_a_chars.count(c) == 0) {
                available_chars.push_back(c);
                if (available_chars.size() == a) break;
            }
        }
        for (char c : available_chars) {
            s.push_back(c);
        }
        
        // Check if the current state (last 'a' chars before computer's move) has been seen before.
        string current_state(s.end() - a - b, s.end() - b); // Last 'a' chars before computer's move.
        if (seen_states.count(current_state)) {
            // Found a cycle.
            // The cycle starts when this state was first encountered.
            for (int i = 0; i < history.size(); ++i) {
                string hist_state(history[i].end() - min(a, (int)history[i].size()), history[i].end());
                if (hist_state == current_state) {
                    cycle_start = i;
                    break;
                }
            }
            cycle_length = history.size() - cycle_start;
            // The cycle string is the part of s from cycle_start to now.
            cycle_string.assign(s.begin() + (history[cycle_start].size()), s.end());
            break;
        }
        seen_states.insert(current_state);
        history.push_back(s);
        
        // Early exit if the string is long enough to cover [l, r].
        if (s.size() >= r) {
            break;
        }
    }
    
    // Now, compute the answer for [l, r].
    // If the string is long enough without cycling, just count distinct letters in [l, r].
    if (s.size() >= r && cycle_start == -1) {
        unordered_set<char> distinct_chars(s.begin() + l - 1, s.begin() + r);
        cout << distinct_chars.size() << endl;
        return 0;
    }
    
    // Otherwise, handle the cyclic part.
    // The string consists of:
    // 1. Initial part: history[0] to history[cycle_start - 1]
    // 2. Cyclic part: cycle_string repeated multiple times.
    
    // Compute the total length of the initial part.
    int initial_length = history[cycle_start].size();
    if (r <= initial_length) {
        unordered_set<char> distinct_chars(history[cycle_start].begin() + l - 1, history[cycle_start].begin() + r);
        cout << distinct_chars.size() << endl;
        return 0;
    }
    
    // The cyclic part starts at initial_length + 1.
    int cycle_len = cycle_string.size();
    int full_cycles = (r - initial_length) / cycle_len;
    int remaining = (r - initial_length) % cycle_len;
    
    // The segment [l, r] spans:
    // - part of the initial string (if l <= initial_length)
    // - some full cycles
    // - part of the next cycle
    
    // To find the minimal distinct letters, we need to consider the worst-case scenario where Mister B repeats a single character.
    // The minimal distinct letters in any window is 1 (if possible), but we need to check the actual string.
    
    // The minimal distinct letters in the cycle_string is the answer for large enough r.
    // But since the cycle may contain parts where Mister B repeats a character, the minimal in any window is 1.
    // However, the computer's moves add 'a' distinct letters, so the minimal in any window is at least 1.
    
    // The actual minimal depends on the overlap between the initial part and the cycle.
    // For simplicity, we can assume that the minimal in the cycle is the minimal in any window of size <= cycle_len.
    
    // Compute the minimal distinct letters in any window of size (r - l + 1) in the cycle_string.
    int window_size = r - l + 1;
    if (window_size >= cycle_len) {
        // The window covers the entire cycle, so the answer is the number of distinct letters in the cycle.
        unordered_set<char> distinct_chars(cycle_string.begin(), cycle_string.end());
        cout << distinct_chars.size() << endl;
    } else {
        // We need to find the minimal distinct letters in any window of size 'window_size' in the cycle_string.
        // Since the cycle_string is repeated, we can just check the cycle_string.
        int min_distinct = a + b; // Upper bound.
        for (int i = 0; i + window_size <= cycle_len; ++i) {
            unordered_set<char> distinct_chars(cycle_string.begin() + i, cycle_string.begin() + i + window_size);
            if (distinct_chars.size() < min_distinct) {
                min_distinct = distinct_chars.size();
                if (min_distinct == 1) break; // Can't get better than 1.
            }
        }
        cout << min_distinct << endl;
    }
    
    return 0;
}