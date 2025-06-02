#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    
    // Precompute the number of 'vv' pairs before each position (left_vv)
    // and the number of 'v's after each position (right_v)
    vector<long long> left_vv(n, 0);
    vector<long long> right_v(n, 0);
    
    // Calculate left_vv: counts the number of ways to choose 'vv' as 'w' before position i
    int v_count = 0;
    for (int i = 1; i < n; ++i) {
        if (s[i-1] == 'v' && s[i] == 'v') {
            v_count++;
        }
        left_vv[i] = v_count;
    }
    
    // Calculate right_v: counts the number of 'v's after position i that can form 'vv' pairs
    v_count = 0;
    for (int i = n-2; i >= 0; --i) {
        if (s[i+1] == 'v' && s[i] == 'v') {
            v_count++;
        }
        right_v[i] = v_count;
    }
    
    // The wow factor is the sum over all 'o's of left_vv[i] * right_v[i]
    long long wow = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'o') {
            wow += left_vv[i] * right_v[i];
        }
    }
    
    cout << wow << endl;
    return 0;
}