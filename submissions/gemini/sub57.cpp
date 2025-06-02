#include <iostream> // Required for standard input/output operations (e.g., scanf, printf)
#include <string>   // Not strictly necessary if using scanf for parsing, but often included
#include <cmath>    // Required for std::abs() function to calculate absolute difference

// Function to determine if a given year is a leap year according to Gregorian calendar rules.
// A year is a leap year if it is perfectly divisible by 4,
// EXCEPT if it is perfectly divisible by 100 AND NOT perfectly divisible by 400.
// For example, 1900 is not a leap year (divisible by 100, not by 400).
// 2000 is a leap year (divisible by 400).
// 2004 is a leap year (divisible by 4, not by 100).
bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// An array storing the standard number of days in each month.
// The array is 1-indexed for convenience, meaning index 1 corresponds to January,
// index 2 to February, and so on, up to index 12 for December.
// February is initially set to 28 days; it will be adjusted to 29 days for leap years
// within the `count_days_from_epoch` function.
int days_in_month_arr[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Function to calculate the total number of days from a fixed reference point (epoch)
// to a specified date. The epoch chosen here is 1900:01:01, which is considered day 1.
// This approach simplifies calculating the difference between two dates:
// calculate days for each date from the epoch, then find the absolute difference.
long long count_days_from_epoch(int year, int month, int day) {
    long long total_days = 0;

    // Step 1: Add days for all full years passed since the epoch year (1900)
    // up to the year *before* the target year.
    // For example, if the target year is 1901, we count days for 1900.
    for (int y = 1900; y < year; ++y) {
        total_days += 365; // Add days for a common year
        if (is_leap_year(y)) {
            total_days += 1; // Add an extra day if 'y' was a leap year
        }
    }

    // Step 2: Add days for all full months passed in the *current* target year
    // up to the month *before* the target month.
    // For example, if the target month is March, we count days for January and February.
    for (int m = 1; m < month; ++m) {
        total_days += days_in_month_arr[m]; // Add standard days for month 'm'
        // If month 'm' is February (index 2) and the current target year is a leap year,
        // add an additional day for February.
        if (m == 2 && is_leap_year(year)) {
            total_days += 1;
        }
    }

    // Step 3: Add the days within the target month itself.
    total_days += day;

    return total_days;
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    // These are common competitive programming optimizations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int y1, m1, d1; // Variables to store year, month, day for the first date
    int y2, m2, d2; // Variables to store year, month, day for the second date

    // Read the first date from standard input.
    // scanf is used for its ability to parse formatted strings directly (e.g., "yyyy:mm:dd").
    scanf("%d:%d:%d", &y1, &m1, &d1);
    // Read the second date from standard input.
    scanf("%d:%d:%d", &y2, &m2, &d2);

    // Calculate the total number of days from the epoch for both dates.
    long long days1 = count_days_from_epoch(y1, m1, d1);
    long long days2 = count_days_from_epoch(y2, m2, d2);

    // The problem asks for "how many days are between them". This implies the absolute
    // difference between the two calculated day counts.
    // std::abs() is used to ensure the result is non-negative, regardless of date order.
    printf("%lld\n", std::abs(days1 - days2));

    return 0; // Indicate successful program execution
}
