#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store scores and frequency/prefix sums

void solve() {
    // N: The number of students in the class.
    int N;
    std::cin >> N; // Read the number of students

    // A: A vector to store the scores of N students.
    // We need to store the original scores to iterate through them later
    // and check the boasting condition for each student.
    std::vector<int> A(N);

    // freq: A frequency array to store the count of students for each score.
    // Scores range from 0 to 100, so an array of size 101 is sufficient
    // to cover indices 0 through 100. Initialize all counts to 0.
    std::vector<int> freq(101, 0);

    // Read the scores and populate the frequency array.
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i]; // Read the score for the i-th student
        freq[A[i]]++;      // Increment the count for this score in the frequency array
    }

    // prefix_sum: A prefix sum array to store the cumulative count of students
    // up to a certain score. prefix_sum[k] will store the number of students
    // with scores less than or equal to k.
    // Size 101 for scores 0 to 100. Initialize all to 0.
    std::vector<int> prefix_sum(101, 0);

    // Calculate the prefix sums.
    // The number of students with score <= 0 is simply freq[0].
    prefix_sum[0] = freq[0];
    // For any other score k, the number of students with score <= k is
    // the number of students with score <= (k-1) plus the number of students
    // with score exactly k.
    for (int i = 1; i <= 100; ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + freq[i];
    }

    // boast_count: A counter for the number of students who will boast.
    int boast_count = 0;

    // Iterate through each student's original score to determine if they boast.
    for (int i = 0; i < N; ++i) {
        int current_score = A[i]; // Get the score of the current student

        // count_le: Number of students scoring less than or equal to current_score.
        // This is directly available from the prefix_sum array.
        int count_le = prefix_sum[current_score];

        // count_gt: Number of students scoring greater than current_score.
        // The total number of students is N.
        // So, count_gt = N - count_le.
        int count_gt = N - count_le;

        // Check the boasting condition:
        // If the number of students scoring less than or equal to current_score
        // is greater than the number of students scoring greater than current_score.
        if (count_le > count_gt) {
            boast_count++; // Increment the boast_count if the condition is met
        }
    }

    // Output the total number of students who will boast for the current test case.
    std::cout << boast_count << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // T: The number of test cases.
    int T;
    std::cin >> T; // Read the number of test cases

    // Loop through each test case.
    while (T--) {
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}
