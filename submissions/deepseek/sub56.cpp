#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to compute the nth term of the sequence f(n) = f(n-1) + n, f(1) = 1
// This is equivalent to the triangular numbers: f(n) = n(n+1)/2
long long computeTerm(int n) {
    return (long long)n * (n + 1) / 2;
}

// Function to determine the color of a term based on its value
string getColor(long long term) {
    // The sequence of colors is ['red', 'yellow', 'blue'], repeating every 3 terms
    // The color is determined by (term - 1) % 3:
    // 0: red, 1: yellow, 2: blue
    int mod = (term - 1) % 3;
    if (mod == 0) return "red";
    if (mod == 1) return "yellow";
    return "blue";
}

vector<long long> same_col_seq(long long val, int k, const string& colour) {
    vector<long long> result;
    int n = 1;
    long long currentTerm = computeTerm(n);
    
    // Find the smallest n such that computeTerm(n) > val
    while (currentTerm <= val) {
        n++;
        currentTerm = computeTerm(n);
    }
    
    // Now check terms starting from n onwards until we find k terms with the desired color
    while (result.size() < k) {
        currentTerm = computeTerm(n);
        // Check if the current term is within the range [val, 2*k*val]
        if (currentTerm > 2 * k * val) {
            break;
        }
        if (getColor(currentTerm) == colour) {
            result.push_back(currentTerm);
        }
        n++;
    }
    
    return result;
}