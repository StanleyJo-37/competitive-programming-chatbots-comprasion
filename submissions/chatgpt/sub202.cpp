#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
using namespace std;

// Structure to hold each competitor's processed data
struct Vaulter {
    string name;
    int max_cleared_height; // highest index with 'O'
    vector<int> cleared_heights; // indices of heights cleared
    vector<int> misses_at_height; // number of X's at each height
    int total_misses; // total number of X's
    vector<string> results; // original results for tie-breaks

    // Constructor to process the results
    Vaulter(const string& n, const vector<string>& res) : name(n), results(res) {
        int n_heights = res.size();
        max_cleared_height = -1;
        total_misses = 0;
        misses_at_height.resize(n_heights, 0);
        for (int i = 0; i < n_heights; ++i) {
            const string& s = res[i];
            int misses = 0;
            for (char c : s) {
                if (c == 'X') ++misses;
            }
            misses_at_height[i] = misses;
            total_misses += misses;
            if (!s.empty() && s.back() == 'O') {
                max_cleared_height = i;
                cleared_heights.push_back(i);
            }
        }
    }
};

// Helper function to join names alphabetically with a separator and suffix
string join_names(const vector<string>& names, const string& suffix) {
    vector<string> sorted_names = names;
    sort(sorted_names.begin(), sorted_names.end());
    stringstream ss;
    for (size_t i = 0; i < sorted_names.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << sorted_names[i];
    }
    if (!suffix.empty()) ss << " " << suffix;
    return ss.str();
}

// Main function to process the competition and determine places
map<string, string> score_pole_vault(const vector<map<string, vector<string>>>& input) {
    vector<Vaulter> vaulters;
    // Parse input into Vaulter structs
    for (const auto& obj : input) {
        string name = obj.at("name")[0];
        vector<string> results = obj.at("results");
        vaulters.emplace_back(name, results);
    }

    // Sort vaulters by max_cleared_height descending
    vector<int> order(vaulters.size());
    for (int i = 0; i < vaulters.size(); ++i) order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b) {
        return vaulters[a].max_cleared_height > vaulters[b].max_cleared_height;
    });

    // Group vaulters by max_cleared_height
    vector<vector<int>> groups;
    int prev_height = -2;
    for (int idx : order) {
        int h = vaulters[idx].max_cleared_height;
        if (groups.empty() || h != prev_height) {
            groups.push_back({});
            prev_height = h;
        }
        groups.back().push_back(idx);
    }

    map<string, string> result;
    int place = 1;
    int group_idx = 0;
    while (place <= 3 && group_idx < groups.size()) {
        vector<int>& group = groups[group_idx];
        // If only one in group, assign place directly
        if (group.size() == 1) {
            string key = (place == 1 ? "1st" : (place == 2 ? "2nd" : "3rd"));
            result[key] = vaulters[group[0]].name;
            ++place;
            ++group_idx;
            continue;
        }
        // Tie-break needed
        // 1. Find greatest height both cleared (which is this group's height)
        int height = vaulters[group[0]].max_cleared_height;
        // 2. Fewest misses at this height
        int min_misses = 1000;
        for (int idx : group) {
            min_misses = min(min_misses, vaulters[idx].misses_at_height[height]);
        }
        vector<int> best_at_height;
        for (int idx : group) {
            if (vaulters[idx].misses_at_height[height] == min_misses)
                best_at_height.push_back(idx);
        }
        if (best_at_height.size() == 1) {
            // Only one winner after first tie-break
            string key = (place == 1 ? "1st" : (place == 2 ? "2nd" : "3rd"));
            result[key] = vaulters[best_at_height[0]].name;
            ++place;
            ++group_idx;
            continue;
        }
        // 3. Fewest total misses
        int min_total_misses = 1000;
        for (int idx : best_at_height) {
            min_total_misses = min(min_total_misses, vaulters[idx].total_misses);
        }
        vector<int> best_total;
        for (int idx : best_at_height) {
            if (vaulters[idx].total_misses == min_total_misses)
                best_total.push_back(idx);
        }
        if (best_total.size() == 1) {
            string key = (place == 1 ? "1st" : (place == 2 ? "2nd" : "3rd"));
            result[key] = vaulters[best_total[0]].name;
            ++place;
            ++group_idx;
            continue;
        }
        // Still tied
        vector<string> tied_names;
        for (int idx : best_total) tied_names.push_back(vaulters[idx].name);
        string key = (place == 1 ? "1st" : (place == 2 ? "2nd" : "3rd"));
        string suffix = (place == 1 ? "(jump-off)" : "(tie)");
        result[key] = join_names(tied_names, suffix);
        // If tie for 1st, no 2nd place
        if (place == 1) {
            place = 3;
            group_idx++;
        } else {
            place++;
            group_idx++;
        }
    }
    return result;
}

// For testing: input parsing and output formatting
int main() {
    // Example input
    vector<map<string, vector<string>>> input = {
        {{"name", {"Sergey"}}, {"results", {"", "O", "XO", "O", "XXO", "XXX", "", ""}}},
        {{"name", {"Jan"}}, {"results", {"", "", "", "O", "O", "XO", "XXO", "XXX"}}},
        {{"name", {"Bruce"}}, {"results", {"", "XO", "XXO", "XXX", "", "", "", ""}}},
        {{"name", {"HerrWert"}}, {"results", {"XXX", "", "", "", "", "", "", ""}}}
    };
    map<string, string> res = score_pole_vault(input);
    // Output result
    for (auto& kv : res) {
        cout << kv.first << ": \"" << kv.second << "\"" << (kv.first == "3rd" ? "" : "; ");
    }
    cout << endl;
    return 0;
}