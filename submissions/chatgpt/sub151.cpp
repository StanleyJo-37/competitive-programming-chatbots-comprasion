#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Structure to represent a variable's definition
struct VarDef {
    // 0: constant, 1: operation
    bool is_const;
    // If constant
    string const_val;
    // If operation
    string op1, op2, op; // operands and operation
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<string> var_names(n); // variable names in order
    unordered_map<string, int> var_idx; // name to index
    vector<VarDef> defs(n);

    // Read variable definitions
    for (int i = 0; i < n; ++i) {
        string name, assign, rest;
        cin >> name >> assign;
        var_names[i] = name;
        var_idx[name] = i;

        string s;
        getline(cin, s);
        // Remove leading spaces
        int p = 0;
        while (p < (int)s.size() && s[p] == ' ') ++p;
        s = s.substr(p);

        // Check if it's a constant
        if (s[0] == '0' || s[0] == '1') {
            defs[i].is_const = true;
            defs[i].const_val = s;
        } else {
            defs[i].is_const = false;
            // Parse: op1 OP op2
            int sp1 = s.find(' ');
            defs[i].op1 = s.substr(0, sp1);
            int sp2 = s.find(' ', sp1 + 1);
            defs[i].op = s.substr(sp1 + 1, sp2 - sp1 - 1);
            defs[i].op2 = s.substr(sp2 + 1);
        }
    }

    // For each bit position, we will simulate two cases:
    // 1. Peter's bit is 0
    // 2. Peter's bit is 1
    // For each bit, we will decide which value (0 or 1) gives min/max sum

    string min_ans(m, '0'), max_ans(m, '0');

    // For each bit position (from leftmost to rightmost)
    for (int bit = 0; bit < m; ++bit) {
        // For each variable, store value if Peter's bit is 0 and 1
        vector<int> val0(n), val1(n);

        // For Peter's number, at this bit, 0 or 1
        // We simulate both cases
        for (int peter_bit = 0; peter_bit <= 1; ++peter_bit) {
            vector<int> vals(n);
            for (int i = 0; i < n; ++i) {
                if (defs[i].is_const) {
                    // Constant: take the bit at position 'bit'
                    vals[i] = defs[i].const_val[bit] - '0';
                } else {
                    // Operation
                    int a, b;
                    // Operand 1
                    if (defs[i].op1 == "?") {
                        a = peter_bit;
                    } else {
                        a = vals[var_idx[defs[i].op1]];
                    }
                    // Operand 2
                    if (defs[i].op2 == "?") {
                        b = peter_bit;
                    } else {
                        b = vals[var_idx[defs[i].op2]];
                    }
                    // Apply operation
                    if (defs[i].op == "AND") {
                        vals[i] = a & b;
                    } else if (defs[i].op == "OR") {
                        vals[i] = a | b;
                    } else if (defs[i].op == "XOR") {
                        vals[i] = a ^ b;
                    }
                }
            }
            // Store result for this bit value
            if (peter_bit == 0) val0 = vals;
            else val1 = vals;
        }
        // Now, for this bit, sum all variable values for both cases
        int sum0 = 0, sum1 = 0;
        for (int i = 0; i < n; ++i) {
            sum0 += val0[i];
            sum1 += val1[i];
        }
        // For min: if sum0 < sum1, pick 0; if sum1 < sum0, pick 1; if equal, pick 0 (minimum number)
        if (sum0 < sum1) {
            min_ans[bit] = '0';
        } else if (sum1 < sum0) {
            min_ans[bit] = '1';
        } else {
            min_ans[bit] = '0';
        }
        // For max: if sum0 > sum1, pick 0; if sum1 > sum0, pick 1; if equal, pick 0 (minimum number)
        if (sum0 > sum1) {
            max_ans[bit] = '0';
        } else if (sum1 > sum0) {
            max_ans[bit] = '1';
        } else {
            max_ans[bit] = '0';
        }
    }

    cout << min_ans << '\n' << max_ans << '\n';
    return 0;
}