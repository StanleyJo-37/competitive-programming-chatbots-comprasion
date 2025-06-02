#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to compute Hamming distance between two 6-digit codes
int hamming(const string& a, const string& b) {
    int dist = 0;
    for (int i = 0; i < 6; ++i) {
        if (a[i] != b[i]) ++dist;
    }
    return dist;
}

int main() {
    int n;
    cin >> n;
    vector<string> codes(n);
    for (int i = 0; i < n; ++i) {
        cin >> codes[i];
    }

    // Find the minimal Hamming distance between any two codes
    int minDist = 6; // Maximum possible is 6
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int d = hamming(codes[i], codes[j]);
            if (d < minDist) minDist = d;
        }
    }

    // The answer is floor((minDist-1)/2)
    // This is because if two codes are at distance d, then if k >= ceil(d/2), 
    // there exists a string within k errors of both codes (the "middle" string).
    // So, the largest k such that all codes are uniquely identified is floor((minDist-1)/2)
    int k = (minDist - 1) / 2;
    cout << k << endl;
    return 0;
}