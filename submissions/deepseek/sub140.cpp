#include <vector>
#include <string>

using namespace std;

string bitsBattle(const vector<int>& numbers) {
    int oddOnes = 0;
    int evenZeros = 0;
    
    for (int num : numbers) {
        if (num == 0) continue; // Neutral, skip
        
        if (num % 2 != 0) { // Odd number
            unsigned int n = num; // Treat as unsigned to avoid sign bit issues
            while (n > 0) {
                if (n & 1) oddOnes++; // Count '1's
                n >>= 1;
            }
        } else { // Even number
            unsigned int n = num;
            while (n > 0) {
                if ((n & 1) == 0) evenZeros++; // Count '0's (excluding leading zeros)
                n >>= 1;
            }
        }
    }
    
    if (oddOnes > evenZeros) return "odds win";
    if (oddOnes < evenZeros) return "evens win";
    return "tie";
}