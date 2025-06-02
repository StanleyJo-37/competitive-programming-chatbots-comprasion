#include <vector>
#include <string>

using namespace std;

string bits_war(const vector<int>& numbers) {
    int oddScore = 0;
    int evenScore = 0;
    
    for (int num : numbers) {
        int absNum = abs(num);
        int bitCount = 0;
        
        // Count the number of '1' bits in the absolute value of the number
        while (absNum > 0) {
            bitCount += absNum & 1;
            absNum >>= 1;
        }
        
        // Adjust the score based on the number's parity and sign
        if (num % 2 != 0) {
            oddScore += (num > 0) ? bitCount : -bitCount;
        } else {
            evenScore += (num > 0) ? bitCount : -bitCount;
        }
    }
    
    if (oddScore > evenScore) {
        return "odds win";
    } else if (evenScore > oddScore) {
        return "evens win";
    } else {
        return "tie";
    }
}