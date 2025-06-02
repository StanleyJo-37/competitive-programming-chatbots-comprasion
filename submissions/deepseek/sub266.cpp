#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<unordered_map<string, string>> solution(vector<int> nums) {
    vector<unordered_map<string, string>> result;
    
    // Iterate over each number in the input array
    for (int num : nums) {
        unordered_map<string, string> obj;
        // Convert the number to a string key and its corresponding character code to a string value
        obj[to_string(num)] = string(1, static_cast<char>(num));
        result.push_back(obj);
    }
    
    return result;
}