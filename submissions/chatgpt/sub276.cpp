#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    int n, m;
    // Read number of students subscribed to English newspaper
    cin >> n;
    unordered_set<int> english;
    // Read roll numbers for English newspaper subscribers
    for (int i = 0; i < n; ++i) {
        int roll;
        cin >> roll;
        english.insert(roll);
    }
    // Read number of students subscribed to French newspaper
    cin >> m;
    unordered_set<int> french;
    // Read roll numbers for French newspaper subscribers
    for (int i = 0; i < m; ++i) {
        int roll;
        cin >> roll;
        french.insert(roll);
    }
    // Compute the difference: students in English set but not in French set
    int count = 0;
    for (const int& roll : english) {
        if (french.find(roll) == french.end()) {
            ++count;
        }
    }
    // Output the total number of students who are subscribed to only English newspaper
    cout << count << endl;
    return 0;
}