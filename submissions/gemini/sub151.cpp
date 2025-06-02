#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm> // Not strictly needed for this solution, but good practice for competitive programming

// Structure to store information about each variable
struct Variable {
    std::string name;
    int type; // 0 for constant, 1 for operation
    std::string val_str; // For constant type, stores the m-bit binary string
    std::string op;      // For operation type, stores "AND", "OR", or "XOR"
    int op1_idx;         // Index of first operand variable, -1 if '?'
    int op2_idx;         // Index of second operand variable, -1 if '?'
};

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin from cout and disables synchronization with C stdio,
    // leading to faster input/output operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    // Store variable definitions. `variables` vector stores them in order of definition.
    std::vector<Variable> variables(n);
    // Map variable names to their indices for quick lookup when parsing operands.
    std::map<std::string, int> var_name_to_idx;

    for (int i = 0; i < n; ++i) {
        std::string var_name, assign_op, token1, token2, token3;
        // Read variable name, assignment operator (":="), and the first token after ":=".
        std::cin >> var_name >> assign_op >> token1;

        variables[i].name = var_name;
        var_name_to_idx[var_name] = i; // Store the mapping for this variable name.

        // Determine if the variable is a constant assignment or an operation.
        // A constant is an m-bit binary number, so its string representation will have length m.
        // An operand (like '?' or a variable name) will have a length different from m.
        if (token1.length() == m) {
            variables[i].type = 0; // Type 0: Constant
            variables[i].val_str = token1; // Store the binary string value.
        } else {
            variables[i].type = 1; // Type 1: Operation
            // For operations, read the operator and the second operand.
            std::cin >> token2 >> token3;
            variables[i].op = token2; // Store the operator ("AND", "OR", "XOR").

            // Determine the index for the first operand.
            // If it's '?', set index to -1 to signify Peter's chosen bit.
            // Otherwise, look up the variable's index from the map.
            if (token1 == "?") {
                variables[i].op1_idx = -1;
            } else {
                variables[i].op1_idx = var_name_to_idx[token1];
            }

            // Determine the index for the second operand, similar to the first.
            if (token3 == "?") {
                variables[i].op2_idx = -1;
            } else {
                variables[i].op2_idx = var_name_to_idx[token3];
            }
        }
    }

    // `sum_0[k]` will store the sum of the k-th bits of all variables if Peter's k-th bit is 0.
    // `sum_1[k]` will store the sum of the k-th bits of all variables if Peter's k-th bit is 1.
    // Using `long long` for sums, though `int` would suffice as max sum is N (5000).
    std::vector<long long> sum_0(m, 0);
    std::vector<long long> sum_1(m, 0);

    // `current_var_bits` temporarily stores the k-th bit value for each variable
    // during the simulation for a specific bit position `k`.
    std::vector<int> current_var_bits(n);

    // Iterate through each bit position `k` from LSB (0) to MSB (m-1).
    // The independence of bit positions allows us to do this.
    for (int k = 0; k < m; ++k) {
        // --- Simulation for Peter's k-th bit being 0 ---
        int peter_bit_val = 0;
        long long current_sum_for_k_0 = 0;
        for (int i = 0; i < n; ++i) { // Iterate through variables in definition order
            if (variables[i].type == 0) { // If it's a constant variable
                // Get the k-th bit from the constant's binary string.
                // The string is MSB-first, so the k-th bit (from LSB) is at index (m-1-k).
                current_var_bits[i] = variables[i].val_str[m - 1 - k] - '0';
            } else { // If it's an operation variable
                int val1, val2;
                // Get the k-th bit value for the first operand.
                // If op1_idx is -1, it's Peter's bit; otherwise, it's a previously computed variable's bit.
                if (variables[i].op1_idx == -1) {
                    val1 = peter_bit_val;
                } else {
                    val1 = current_var_bits[variables[i].op1_idx];
                }
                // Get the k-th bit value for the second operand, similar to the first.
                if (variables[i].op2_idx == -1) {
                    val2 = peter_bit_val;
                } else {
                    val2 = current_var_bits[variables[i].op2_idx];
                }

                // Perform the specified bitwise operation.
                if (variables[i].op == "AND") {
                    current_var_bits[i] = val1 & val2;
                } else if (variables[i].op == "OR") {
                    current_var_bits[i] = val1 | val2;
                } else { // XOR
                    current_var_bits[i] = val1 ^ val2;
                }
            }
            current_sum_for_k_0 += current_var_bits[i]; // Add this variable's k-th bit to the sum
        }
        sum_0[k] = current_sum_for_k_0; // Store the total sum of k-th bits for peter_bit_val = 0

        // --- Simulation for Peter's k-th bit being 1 ---
        peter_bit_val = 1;
        long long current_sum_for_k_1 = 0;
        for (int i = 0; i < n; ++i) { // Iterate through variables in definition order
            if (variables[i].type == 0) { // If it's a constant variable
                current_var_bits[i] = variables[i].val_str[m - 1 - k] - '0';
            } else { // If it's an operation variable
                int val1, val2;
                if (variables[i].op1_idx == -1) {
                    val1 = peter_bit_val;
                } else {
                    val1 = current_var_bits[variables[i].op1_idx];
                }
                if (variables[i].op2_idx == -1) {
                    val2 = peter_bit_val;
                } else {
                    val2 = current_var_bits[variables[i].op2_idx];
                }

                if (variables[i].op == "AND") {
                    current_var_bits[i] = val1 & val2;
                } else if (variables[i].op == "OR") {
                    current_var_bits[i] = val1 | val2;
                } else { // XOR
                    current_var_bits[i] = val1 ^ val2;
                }
            }
            current_sum_for_k_1 += current_var_bits[i]; // Add this variable's k-th bit to the sum
        }
        sum_1[k] = current_sum_for_k_1; // Store the total sum of k-th bits for peter_bit_val = 1
    }

    // Construct the m-bit binary numbers for minimum and maximum scores.
    // Initialize with '0's, then set bits based on comparisons.
    std::string min_peter_num_str(m, '0');
    std::string max_peter_num_str(m, '0');

    // Iterate through each bit position `k` from LSB (0) to MSB (m-1).
    // The choice for each bit is independent and determined by comparing sum_0[k] and sum_1[k].
    // The tie-breaking rule ("minimum number") means if sums are equal, we choose '0'.
    for (int k = 0; k < m; ++k) {
        // For minimum total score:
        // If choosing 0 for Peter's k-th bit results in a smaller or equal sum of k-th bits
        // across all variables compared to choosing 1, then choose 0.
        // Otherwise (if sum_0[k] > sum_1[k]), choose 1.
        if (sum_0[k] <= sum_1[k]) {
            min_peter_num_str[m - 1 - k] = '0'; // Set the bit at MSB-first index (m-1-k)
        } else {
            min_peter_num_str[m - 1 - k] = '1';
        }

        // For maximum total score:
        // If choosing 0 for Peter's k-th bit results in a larger or equal sum of k-th bits
        // across all variables compared to choosing 1, then choose 0.
        // Otherwise (if sum_0[k] < sum_1[k]), choose 1.
        if (sum_0[k] >= sum_1[k]) {
            max_peter_num_str[m - 1 - k] = '0'; // Set the bit at MSB-first index (m-1-k)
        } else {
            max_peter_num_str[m - 1 - k] = '1';
        }
    }

    // Output the results as m-bit binary strings.
    std::cout << min_peter_num_str << "\n";
    std::cout << max_peter_num_str << "\n";

    return 0;
}
