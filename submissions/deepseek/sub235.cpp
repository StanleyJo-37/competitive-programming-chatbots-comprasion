#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> heavy_positions;
    vector<int> metal_positions;

    // Precompute all starting indices of "heavy" and ending indices of "metal"
    for (int i = 0; i + 4 < n; ++i) {
        if (s.substr(i, 5) == "heavy") {
            heavy_positions.push_back(i);
        }
        if (s.substr(i, 5) == "metal") {
            metal_positions.push_back(i + 4); // Store the end index of "metal"
        }
    }

    // For each "metal" end position, count how many "heavy" start positions are before it
    long long result = 0;
    int heavy_ptr = 0;
    int metal_ptr = 0;
    int heavy_size = heavy_positions.size();
    int metal_size = metal_positions.size();

    // Two-pointer approach to count valid (heavy, metal) pairs
    while (heavy_ptr < heavy_size && metal_ptr < metal_size) {
        if (heavy_positions[heavy_ptr] < metal_positions[metal_ptr]) {
            // All metal positions after current metal_ptr are valid for this heavy
            result += (metal_size - metal_ptr);
            heavy_ptr++;
        } else {
            metal_ptr++;
        }
    }

    cout << result << endl;
    return 0;
}