#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Function to check if a year is a leap year in Gregorian calendar
bool isLeap(int year) {
    // Leap year if divisible by 4, not by 100 unless also by 400
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Number of days in each month for non-leap years
const int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

// Function to parse a date string "yyyy:mm:dd" into year, month, day
void parseDate(const string& s, int& y, int& m, int& d) {
    y = stoi(s.substr(0,4));
    m = stoi(s.substr(5,2));
    d = stoi(s.substr(8,2));
}

// Function to count number of days from 1900:01:01 to the given date (inclusive)
int daysFromEpoch(int y, int m, int d) {
    int days = 0;
    // Add days for all years before current year
    for (int year = 1900; year < y; ++year) {
        days += isLeap(year) ? 366 : 365;
    }
    // Add days for all months before current month in current year
    for (int month = 1; month < m; ++month) {
        if (month == 2 && isLeap(y))
            days += 29;
        else
            days += monthDays[month-1];
    }
    // Add days in current month
    days += d;
    return days;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int y1, m1, d1, y2, m2, d2;
    parseDate(s1, y1, m1, d1);
    parseDate(s2, y2, m2, d2);

    // Calculate days from epoch for both dates
    int days1 = daysFromEpoch(y1, m1, d1);
    int days2 = daysFromEpoch(y2, m2, d2);

    // The answer is the absolute difference plus 1 (both borders included)
    cout << abs(days1 - days2) + 1 << endl;
    return 0;
}