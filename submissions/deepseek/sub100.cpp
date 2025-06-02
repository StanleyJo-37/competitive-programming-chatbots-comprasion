#include <iostream>
#include <vector>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> res;
        
        // For even n, we can pair teams and have each win one game against the other in the pair.
        // For odd n, one team will have all ties, and the rest will be paired.
        if (n % 2 == 0) {
            for (int i = 1; i <= n; ++i) {
                for (int j = i + 1; j <= n; ++j) {
                    if (j == i + 1 && i % 2 == 1) {
                        // Alternate wins between pairs (1 beats 2, 3 beats 4, etc.)
                        res.push_back(1);
                    } else if (j == i + 1 && i % 2 == 0) {
                        res.push_back(-1);
                    } else {
                        // For non-consecutive pairs, alternate wins to balance points
                        if ((i + j) % 2 == 0) {
                            res.push_back(1);
                        } else {
                            res.push_back(-1);
                        }
                    }
                }
            }
        } else {
            // For odd n, each team will have (n-1)/2 wins and (n-1)/2 losses.
            // One way is to have team i win against team j if (j - i) is odd (mod n).
            for (int i = 1; i <= n; ++i) {
                for (int j = i + 1; j <= n; ++j) {
                    if ((j - i) % 2 == 1) {
                        res.push_back(1);
                    } else {
                        res.push_back(-1);
                    }
                }
            }
        }
        
        // Output the results
        for (int i = 0; i < res.size(); ++i) {
            cout << res[i] << " ";
        }
        cout << endl;
    }
    return 0;
}