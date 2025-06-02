#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <string>   // Required for using std::string to read the message sequence

void solve() {
    // Read the total number of messages in the dialog.
    int n;
    std::cin >> n;
    // Read the string describing message types ('Q' for client question, 'A' for manager answer).
    std::string s;
    std::cin >> s;

    // Initialize a counter for client questions that have been asked
    // but have not yet received at least one answer from the manager.
    // This counter represents the number of "pending" questions that
    // *must* eventually receive an answer to satisfy the problem rules.
    int unanswered_questions_needing_first_answer = 0;

    // Iterate through each message in the dialog in chronological order.
    for (char message_type : s) {
        if (message_type == 'Q') {
            // If the current message is a client question ('Q'),
            // it means a new question has been asked. This question
            // now needs at least one answer. So, increment the counter.
            unanswered_questions_needing_first_answer++;
        } else { // message_type == 'A'
            // If the current message is a manager answer ('A'):
            // We need to check if this answer can fulfill a requirement
            // for a question that hasn't received its first answer yet.
            if (unanswered_questions_needing_first_answer > 0) {
                // If there is at least one client question that still needs
                // its first answer (i.e., unanswered_questions_needing_first_answer > 0),
                // then this 'A' can be considered as the first answer to one
                // of those pending questions. So, decrement the counter.
                unanswered_questions_needing_first_answer--;
            }
            // If unanswered_questions_needing_first_answer is already 0,
            // it means all previously asked client questions have already
            // received at least one answer. According to the problem rules,
            // a manager can send "one or several messages" as an answer to
            // a client's question. This implies that an 'A' can be an
            // *additional* answer to a question that has already been
            // initially answered. In this scenario, this 'A' does not
            // fulfill a new "first answer" requirement, so the counter
            // `unanswered_questions_needing_first_answer` remains unchanged.
        }
    }

    // After processing all messages in the dialog, we check the final state
    // of the counter.
    // If `unanswered_questions_needing_first_answer` is 0, it means all client
    // questions that were asked have received at least one answer. This dialog
    // *may* correspond to the rules of work.
    if (unanswered_questions_needing_first_answer == 0) {
        std::cout << "Yes\n";
    } else {
        // If `unanswered_questions_needing_first_answer` is greater than 0,
        // it means there are client questions that were asked but never
        // received even a single answer from the manager. This violates
        // the rule "each message of the client must be followed by one or
        // several messages, which are the answer of a support manager."
        // Therefore, this dialog certainly breaches the rules.
        std::cout << "No\n";
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // This is a common practice in competitive programming to prevent TLE (Time Limit Exceeded).
    std::ios_base::sync_with_stdio(false); // Unties C++ streams from C standard streams.
    std::cin.tie(NULL);                   // Unties cin from cout, preventing flushes.

    // Read the number of test cases.
    int t;
    std::cin >> t;
    // Loop through each test case and call the `solve` function.
    while (t--) {
        solve();
    }

    return 0; // Indicate successful program execution.
}