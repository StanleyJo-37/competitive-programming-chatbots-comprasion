#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector dynamic arrays

// Function to perform counting sort on an array of integers.
// It takes an unsorted array 'arr' as input.
// It returns a new vector containing the sorted elements.
std::vector<int> countingSort(std::vector<int> arr) {
    // Constraints state that 0 <= arr[i] < 100.
    // Therefore, a frequency array (or 'counts' array) of size 100 (indices 0-99) is sufficient
    // to store the occurrences of each number.
    // Initialize all counts to 0.
    std::vector<int> counts(100, 0);

    // Iterate through the input array 'arr' to populate the frequency counts.
    // For each element 'x' found in 'arr', increment the counter at index 'x' in the 'counts' vector.
    for (int x : arr) {
        counts[x]++;
    }

    // Create a new vector 'sorted_result' to store the sorted elements.
    // The total number of elements in the sorted array will be the same as the input array 'arr'.
    // Reserving space can improve performance by reducing memory reallocations during push_back operations,
    // especially for large input sizes.
    std::vector<int> sorted_result;
    sorted_result.reserve(arr.size());

    // Iterate from the smallest possible value (0) to the largest (99) that can be present in 'arr'.
    // For each value 'i', append it to 'sorted_result' 'counts[i]' times.
    // This step reconstructs the sorted array based on the frequencies stored in 'counts'.
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < counts[i]; ++j) {
            sorted_result.push_back(i);
        }
    }

    // Return the newly created sorted array.
    return sorted_result;
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ standard streams from C standard streams,
    // which can significantly speed up I/O.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input,
    // further optimizing input operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare an integer 'n' to store the length of the input array.
    std::cin >> n; // Read the length 'n' from standard input.

    // Declare a vector 'arr' of integers to store the input elements.
    // Initialize it with size 'n'.
    std::vector<int> arr(n);

    // Read 'n' integers from standard input and populate the 'arr' vector.
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    // Call the countingSort function with the input array 'arr'.
    // The function returns a new vector containing the sorted elements, which is stored in 'sorted_arr'.
    std::vector<int> sorted_arr = countingSort(arr);

    // Print the elements of the 'sorted_arr', separated by spaces.
    // This loop iterates through the sorted array.
    for (size_t i = 0; i < sorted_arr.size(); ++i) {
        std::cout << sorted_arr[i]; // Print the current element.
        // If the current element is not the last one in the array, print a space after it.
        // This ensures that there is no trailing space at the end of the line.
        if (i < sorted_arr.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl; // Print a newline character at the very end of the output.

    return 0; // Indicate successful program execution.
}