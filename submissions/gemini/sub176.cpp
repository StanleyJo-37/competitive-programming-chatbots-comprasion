#include <iostream>

// Function to calculate the n-th triangular number T_n = n*(n+1)/2.
// Triangular numbers are defined for non-negative integers.
// For summation purposes, if n is negative, we consider T_n to be 0.
long long calculate_T(long long n) {
    if (n < 0) {
        return 0;
    }
    return n * (n + 1) / 2;
}

// Function to calculate the n-th tetrahedral number Te_n = n*(n+1)*(n+2)/6.
// Tetrahedral numbers are defined for non-negative integers.
// For summation purposes, if n is negative, we consider Te_n to be 0.
long long calculate_Te(long long n) {
    if (n < 0) {
        return 0;
    }
    return n * (n + 1) * (n + 2) / 6;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This unties cin from cout and disables synchronization with C stdio.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T; // Read the number of test cases.

    while (T--) {
        long long x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2; // Read the coordinates for each test case.

        // The problem asks for the maximum possible sum of values along a path
        // from (x1, y1) to (x2, y2), moving only right or down.
        // Let A(x, y) be the value at cell (x, y).
        // Observations from the problem description and matrix pattern:
        // 1. Moving right from (x, y) to (x, y+1) adds (x+y-1) to the previous value:
        //    A(x, y+1) = A(x, y) + (x+y-1)
        // 2. Moving down from (x, y) to (x+1, y) adds (x+y) to the previous value:
        //    A(x+1, y) = A(x, y) + (x+y)
        //
        // Since (x+y) is always greater than (x+y-1) for x,y >= 1,
        // moving down from (x,y) always results in a larger value at the next cell
        // compared to moving right from (x,y).
        //
        // Consider any path that contains a 'Right then Down' sequence:
        // (x, y) -> (x, y+1) -> (x+1, y+1)
        // The sum contribution from these three cells is A(x,y) + A(x,y+1) + A(x+1,y+1).
        //
        // Now consider swapping this to a 'Down then Right' sequence:
        // (x, y) -> (x+1, y) -> (x+1, y+1)
        // The sum contribution from these three cells is A(x,y) + A(x+1,y) + A(x+1,y+1).
        //
        // The difference in sum between 'D then R' and 'R then D' is:
        // (A(x,y) + A(x+1,y) + A(x+1,y+1)) - (A(x,y) + A(x,y+1) + A(x+1,y+1))
        // = A(x+1,y) - A(x,y+1)
        // Using the rules:
        // A(x+1,y) = A(x,y) + (x+y)
        // A(x,y+1) = A(x,y) + (x+y-1)
        // So, A(x+1,y) - A(x,y+1) = (A(x,y) + x+y) - (A(x,y) + x+y-1) = 1.
        //
        // This means replacing any 'R then D' sequence with 'D then R' increases the total path sum by 1.
        // Therefore, to maximize the sum, we should avoid any 'R then D' sequences.
        // This implies that all 'Down' moves must occur before all 'Right' moves.
        //
        // The optimal path is:
        // (x1, y1) -> (x1+1, y1) -> ... -> (x2, y1)  (all down moves)
        // then
        // (x2, y1) -> (x2, y1+1) -> ... -> (x2, y2)  (all right moves)
        //
        // We need a formula for A(x,y).
        // A(x,1) = x*(x+1)/2 (n-th triangular number, T_x)
        // A(1,y) = 1 + (y-1)*y/2 (1 + T_{y-1})
        //
        // Using A(x,y) = A(x, y-1) + (x+y-2) (derived from A(x,y+1) = A(x,y) + (x+y-1) by shifting y to y-1)
        // A(x,y) = A(x,1) + Sum_{j=1 to y-1} (x+j-1)
        // A(x,y) = x*(x+1)/2 + Sum_{k=x to x+y-2} k
        // A(x,y) = x*(x+1)/2 + (Sum_{k=1 to x+y-2} k) - (Sum_{k=1 to x-1} k)
        // A(x,y) = x*(x+1)/2 + T_{x+y-2} - T_{x-1}
        // A(x,y) = x*(x+1)/2 + (x+y-2)(x+y-1)/2 - (x-1)x/2
        // A(x,y) = (x^2+x)/2 + (x+y-2)(x+y-1)/2 - (x^2-x)/2
        // A(x,y) = (2x)/2 + (x+y-2)(x+y-1)/2
        // A(x,y) = x + T_{x+y-2}
        // This formula is used to calculate cell values.

        long long total_path_sum = 0;

        // Sum of values for the first segment (down moves): (x1, y1) to (x2, y1)
        // This sum is Sum_{i=x1 to x2} A(i, y1)
        // A(i, y1) = i + T_{i+y1-2}
        // Sum = Sum_{i=x1 to x2} i  +  Sum_{i=x1 to x2} T_{i+y1-2}

        // Part 1: Sum of 'i' from x1 to x2 (arithmetic series sum)
        // Number of terms = x2 - x1 + 1
        // Sum = (number of terms) * (first term + last term) / 2
        total_path_sum += (x2 - x1 + 1) * (x1 + x2) / 2;

        // Part 2: Sum of T_{i+y1-2} from i=x1 to x2
        // Let k = i+y1-2.
        // When i = x1, k = x1+y1-2.
        // When i = x2, k = x2+y1-2.
        // This is Sum_{k=x1+y1-2 to x2+y1-2} T_k.
        // The sum of triangular numbers from S to E is Te_E - Te_{S-1}.
        long long start_k_segment1 = x1 + y1 - 2;
        long long end_k_segment1 = x2 + y1 - 2;
        total_path_sum += calculate_Te(end_k_segment1) - calculate_Te(start_k_segment1 - 1);

        // Sum of values for the second segment (right moves): (x2, y1+1) to (x2, y2)
        // Note: The cell (x2, y1) is already included in the first segment's sum.
        // This sum is Sum_{j=y1+1 to y2} A(x2, j)
        // A(x2, j) = x2 + T_{x2+j-2}
        // Sum = Sum_{j=y1+1 to y2} x2  +  Sum_{j=y1+1 to y2} T_{x2+j-2}

        // Part 3: Sum of 'x2' from y1+1 to y2
        // Number of terms = y2 - (y1+1) + 1 = y2 - y1.
        // If y1 = y2, this sum is 0, which is correct as there are no right moves.
        total_path_sum += x2 * (y2 - y1);

        // Part 4: Sum of T_{x2+j-2} from j=y1+1 to y2
        // Let k = x2+j-2.
        // When j = y1+1, k = x2+y1+1-2 = x2+y1-1.
        // When j = y2, k = x2+y2-2.
        // This is Sum_{k=x2+y1-1 to x2+y2-2} T_k.
        // The sum of triangular numbers from S to E is Te_E - Te_{S-1}.
        long long start_k_segment2 = x2 + y1 - 1;
        long long end_k_segment2 = x2 + y2 - 2;
        total_path_sum += calculate_Te(end_k_segment2) - calculate_Te(start_k_segment2 - 1);
        
        std::cout << total_path_sum << "\n"; // Output the maximum path value.
    }

    return 0;
}
