#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store dynamic array of years
#include <algorithm> // Required for std::sort to sort the vector

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C's stdio and disables flushing of cout before cin.
    // It can speed up I/O operations, though for the given small constraints (N <= 5),
    // its impact on performance is negligible.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare an integer variable 'n' to store the number of groups Igor joined.
    std::cin >> n; // Read the value of 'n' from standard input.

    // Declare a std::vector of integers named 'a' to store the years of university entrance
    // for each group Igor is a member of. The vector is initialized with a size of 'n'.
    std::vector<int> a(n); 

    // Loop 'n' times to read each year into the vector 'a'.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read the i-th year into the vector.
    }

    // Sort the vector 'a' in ascending order.
    // According to the problem description, Igor joins his own course's group and all groups
    // for which the year of university entrance differs by no more than 'x' from his own.
    // This means if Igor entered in year 'Y_igor', he joins groups corresponding to years
    // from 'Y_igor - x' to 'Y_igor + x'.
    // The list of years he joined, when sorted, will form a contiguous sequence:
    // Y_igor - x, Y_igor - x + 1, ..., Y_igor - 1, Y_igor, Y_igor + 1, ..., Y_igor + x.
    std::sort(a.begin(), a.end());

    // The total number of groups Igor joined is 'n'.
    // From the range [Y_igor - x, Y_igor + x], the number of elements is (Y_igor + x) - (Y_igor - x) + 1 = 2x + 1.
    // So, we have the equation n = 2x + 1.
    // Since 'n' is guaranteed to be an odd integer, 'x' can be uniquely determined as x = (n - 1) / 2.
    // Igor's university entrance year, 'Y_igor', is the exact middle element of this sorted sequence of years.
    // For a 0-indexed array of size 'n' (where 'n' is odd), the middle element is at index (n - 1) / 2.
    // For example:
    // If n=1, x=0. The middle index is (1-1)/2 = 0.
    // If n=3, x=1. The middle index is (3-1)/2 = 1.
    // If n=5, x=2. The middle index is (5-1)/2 = 2.
    std::cout << a[(n - 1) / 2] << std::endl; // Print the middle element of the sorted vector, which is Igor's entrance year.

    return 0; // Indicate successful execution of the program.
}