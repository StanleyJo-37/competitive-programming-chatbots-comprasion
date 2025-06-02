#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

// Function to parse a date string into tm struct
void parseDate(const string& date, struct tm& tm) {
    istringstream ss(date);
    char delimiter;
    ss >> tm.tm_year >> delimiter >> tm.tm_mon >> delimiter >> tm.tm_mday;
    tm.tm_year -= 1900; // tm_year is years since 1900
    tm.tm_mon -= 1;     // tm_mon is 0-based
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = -1;   // Let mktime determine daylight saving time
}

// Function to calculate the difference in days between two dates
long daysBetweenDates(const string& date1, const string& date2) {
    struct tm tm1 = {0}, tm2 = {0};
    parseDate(date1, tm1);
    parseDate(date2, tm2);
    
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    
    if (time1 == -1 || time2 == -1) {
        cerr << "Error converting date to time" << endl;
        return -1;
    }
    
    double seconds = difftime(time2, time1);
    long days = static_cast<long>(seconds / (60 * 60 * 24));
    
    return abs(days);
}

int main() {
    string date1, date2;
    getline(cin, date1);
    getline(cin, date2);
    
    cout << daysBetweenDates(date1, date2) << endl;
    
    return 0;
}