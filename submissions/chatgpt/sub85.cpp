#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t; // Read number of test cases
    while (t--) {
        int n;
        cin >> n; // Read number of messages
        string s;
        cin >> s; // Read the message sequence

        int open_questions = 0; // Counter for unanswered client questions
        bool valid = true; // Flag to check if dialog is valid

        // Iterate through each message in the dialog
        for (char c : s) {
            if (c == 'Q') {
                // New client question, increment unanswered questions
                open_questions++;
            } else if (c == 'A') {
                // Manager's answer, try to answer an open question if any
                if (open_questions > 0) {
                    open_questions--;
                }
                // If no open questions, answer is just extra, which is allowed
            }
        }

        // After processing all messages, if there are unanswered questions, it's invalid
        if (open_questions == 0) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}