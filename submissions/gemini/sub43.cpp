#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector
#include <algorithm> // Required for std::sort

void solve() {
    int n;
    std::cin >> n; // Read the length of the sequence
    std::vector<long long> a(n); // Declare a vector to store the sequence elements.
                                // Use long long because individual elements can be up to 10^9,
                                // and their sum can exceed the capacity of a 32-bit integer.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read each element of the sequence
    }

    // Sort the array in ascending order.
    // This is crucial for the greedy strategy:
    // Smallest elements will be at the beginning (for Blue),
    // Largest elements will be at the end (for Red).
    std::sort(a.begin(), a.end());

    long long sum_red = 0;   // Stores the sum of elements painted Red
    long long sum_blue = 0;  // Stores the sum of elements painted Blue
    int count_red = 0;       // Stores the count of elements painted Red
    int count_blue = 0;      // Stores the count of elements painted Blue

    // Initialize two pointers:
    // 'left' starts from the beginning of the sorted array (smallest elements).
    // 'right' starts from the end of the sorted array (largest elements).
    int left = 0;
    int right = n - 1;

    bool possible = false; // Flag to track if a valid painting is found

    // The loop continues as long as there are distinct elements available for both red and blue.
    // 'left < right' ensures that the elements pointed to by 'left' and 'right' are distinct.
    while (left < right) {
        // Greedily pick the largest available element for Red.
        sum_red += a[right];
        count_red++;
        right--; // Move the right pointer inwards, as a[right] has been used

        // Greedily pick the smallest available elements for Blue.
        // We need to ensure that count_blue is strictly greater than count_red.
        // We also need to ensure 'left' pointer does not cross 'right' pointer,
        // meaning we are picking distinct elements from those used by Red.
        while (count_blue <= count_red && left < right) {
            sum_blue += a[left];
            count_blue++;
            left++; // Move the left pointer inwards, as a[left] has been used
        }

        // After potentially adding elements to both Red and Blue sets,
        // check if the problem's conditions are met:
        // 1. count_red < count_blue: This is ensured by the inner while loop.
        //    If the inner loop terminates, it's either because count_blue > count_red is met,
        //    or because left >= right (no more distinct elements to pick for blue).
        // 2. sum_red > sum_blue: This is the primary sum condition.
        // 3. Elements are distinct: Ensured by the 'left < right' checks.
        //    The elements for Red are a[right+1]...a[n-1].
        //    The elements for Blue are a[0]...a[left-1].
        //    Since 'left' only increases and 'right' only decreases, and we always ensure
        //    'left < right' when picking elements, these two sets of indices are always disjoint.
        if (count_blue > count_red && sum_red > sum_blue) {
            possible = true; // A valid configuration is found
            break;           // No need to check further, we just need to know if it's possible
        }
    }

    // Output the result based on whether a valid configuration was found
    if (possible) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}
