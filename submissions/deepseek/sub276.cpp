#include <iostream>
#include <unordered_set>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    // Read the number of English subscribers
    int n;
    cin >> n;
    cin.ignore(); // Ignore the newline after the integer input
    
    // Read the roll numbers of English subscribers
    string englishLine;
    getline(cin, englishLine);
    istringstream englishStream(englishLine);
    unordered_set<string> englishSubscribers;
    string roll;
    while (englishStream >> roll) {
        englishSubscribers.insert(roll);
    }
    
    // Read the number of French subscribers
    int m;
    cin >> m;
    cin.ignore(); // Ignore the newline after the integer input
    
    // Read the roll numbers of French subscribers
    string frenchLine;
    getline(cin, frenchLine);
    istringstream frenchStream(frenchLine);
    unordered_set<string> frenchSubscribers;
    while (frenchStream >> roll) {
        frenchSubscribers.insert(roll);
    }
    
    // Calculate the difference (English only subscribers)
    int englishOnlyCount = 0;
    for (const auto& student : englishSubscribers) {
        if (frenchSubscribers.find(student) == frenchSubscribers.end()) {
            englishOnlyCount++;
        }
    }
    
    // Output the result
    cout << englishOnlyCount << endl;
    
    return 0;
}