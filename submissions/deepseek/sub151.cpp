#include <bits/stdc++.h>
using namespace std;

struct Variable {
    char op; // '0' for constant, '&', '|', '^' for operations
    string operand1, operand2;
    bitset<1000> val; // Only used if op is '0'
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    unordered_map<string, Variable> vars;
    vector<string> order;

    for (int i = 0; i < n; ++i) {
        string name, assign, op1, op, op2;
        cin >> name >> assign;
        order.push_back(name);
        Variable var;
        if (assign == ":=") {
            string rest;
            cin >> rest;
            if (rest == "?" || (rest[0] != '0' && rest[0] != '1')) {
                // It's an operation
                var.op = rest[0];
                if (var.op == '?') {
                    var.op1 = "?";
                    cin >> op >> op2;
                    var.op = op[0]; // 'A' for AND, 'O' for OR, 'X' for XOR
                    var.operand2 = op2;
                } else {
                    var.op1 = rest;
                    cin >> op >> op2;
                    var.op = op[0];
                    var.operand2 = op2;
                }
            } else {
                // It's a constant
                var.op = '0';
                for (int j = 0; j < m; ++j) {
                    var.val[m - 1 - j] = (rest[j] == '1');
                }
            }
        } else {
            // Handle cases where := is split (shouldn't happen per input format)
            // Assuming input is correct, so skipping
        }
        vars[name] = var;
    }

    bitset<1000> min_num, max_num;
    for (int bit = 0; bit < m; ++bit) {
        int sum0 = 0, sum1 = 0;
        // Evaluate for bit set to 0 and 1
        for (int b = 0; b <= 1; ++b) {
            unordered_map<string, int> cache;
            for (const auto& name : order) {
                const Variable& var = vars[name];
                if (var.op == '0') {
                    cache[name] = var.val[bit];
                } else {
                    int val1, val2;
                    if (var.op1 == "?") {
                        val1 = b;
                    } else {
                        val1 = cache[var.op1];
                    }
                    if (var.operand2 == "?") {
                        val2 = b;
                    } else {
                        val2 = cache[var.operand2];
                    }
                    int res;
                    switch (var.op) {
                        case 'A': res = val1 & val2; break;
                        case 'O': res = val1 | val2; break;
                        case 'X': res = val1 ^ val2; break;
                        default: res = 0;
                    }
                    cache[name] = res;
                }
            }
            int total = 0;
            for (const auto& entry : cache) {
                total += entry.second;
            }
            if (b == 0) sum0 = total;
            else sum1 = total;
        }
        if (sum0 < sum1) {
            min_num[bit] = 0;
            max_num[bit] = 1;
        } else if (sum0 > sum1) {
            min_num[bit] = 1;
            max_num[bit] = 0;
        } else {
            min_num[bit] = 0;
            max_num[bit] = 0;
        }
    }

    for (int i = m - 1; i >= 0; --i) {
        cout << min_num[i];
    }
    cout << '\n';
    for (int i = m - 1; i >= 0; --i) {
        cout << max_num[i];
    }
    cout << '\n';

    return 0;
}