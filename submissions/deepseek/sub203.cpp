#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

class Participant {
public:
    string name;
    int winningNumber;

    Participant(string name, int winningNumber) : name(name), winningNumber(winningNumber) {}

    // Custom comparator for sorting participants
    static bool compare(const Participant &a, const Participant &b) {
        if (a.winningNumber == b.winningNumber) {
            return a.name < b.name; // Alphabetical order if winning numbers are equal
        }
        return a.winningNumber > b.winningNumber; // Descending order by winning number
    }
};

vector<string> splitNames(const string &st) {
    vector<string> names;
    string current;
    for (char c : st) {
        if (c == ',') {
            if (!current.empty()) {
                names.push_back(current);
                current.clear();
            }
        } else {
            current += c;
        }
    }
    if (!current.empty()) {
        names.push_back(current);
    }
    return names;
}

int calculateSom(const string &name) {
    int som = name.length();
    for (char c : name) {
        if (isalpha(c)) {
            som += tolower(c) - 'a' + 1; // Convert to lowercase and calculate rank
        }
    }
    return som;
}

string rank(const string &st, const vector<int> &we, int n) {
    if (st.empty()) {
        return "No participants";
    }

    vector<string> names = splitNames(st);
    if (n > names.size()) {
        return "Not enough participants";
    }

    vector<Participant> participants;
    for (int i = 0; i < names.size(); ++i) {
        int som = calculateSom(names[i]);
        int winningNumber = som * we[i];
        participants.emplace_back(names[i], winningNumber);
    }

    sort(participants.begin(), participants.end(), Participant::compare);

    return participants[n - 1].name;
}