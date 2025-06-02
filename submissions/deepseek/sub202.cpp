#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

struct Competitor {
    string name;
    vector<string> results;
    int highest_cleared;
    int misses_at_highest;
    int total_misses;
};

bool compareCompetitors(const Competitor &a, const Competitor &b) {
    if (a.highest_cleared != b.highest_cleared) {
        return a.highest_cleared > b.highest_cleared;
    }
    if (a.misses_at_highest != b.misses_at_highest) {
        return a.misses_at_highest < b.misses_at_highest;
    }
    return a.total_misses < b.total_misses;
}

map<string, string> score_pole_vault(const vector<map<string, vector<string>>> &vaulters) {
    vector<Competitor> competitors;
    
    for (const auto &vaulter : vaulters) {
        Competitor c;
        c.name = vaulter.at("name");
        c.results = vaulter.at("results");
        c.highest_cleared = -1;
        c.misses_at_highest = 0;
        c.total_misses = 0;
        
        for (int i = c.results.size() - 1; i >= 0; --i) {
            const string &result = c.results[i];
            if (result.empty()) continue;
            
            bool has_O = false;
            int misses = 0;
            for (char ch : result) {
                if (ch == 'O') has_O = true;
                else if (ch == 'X') misses++;
            }
            
            if (has_O) {
                if (c.highest_cleared == -1) {
                    c.highest_cleared = i;
                    c.misses_at_highest = misses;
                }
            }
            c.total_misses += misses;
        }
        
        if (c.highest_cleared == -1) {
            c.highest_cleared = -2; // did not clear any height
        }
        
        competitors.push_back(c);
    }
    
    sort(competitors.begin(), competitors.end(), compareCompetitors);
    
    map<string, string> result;
    if (competitors.empty()) return result;
    
    // Group competitors by their ranks
    vector<vector<Competitor>> ranked;
    for (size_t i = 0; i < competitors.size(); ) {
        vector<Competitor> group;
        group.push_back(competitors[i]);
        size_t j = i + 1;
        while (j < competitors.size()) {
            if (competitors[j].highest_cleared == competitors[i].highest_cleared &&
                competitors[j].misses_at_highest == competitors[i].misses_at_highest &&
                competitors[j].total_misses == competitors[i].total_misses) {
                group.push_back(competitors[j]);
                j++;
            } else {
                break;
            }
        }
        ranked.push_back(group);
        i = j;
    }
    
    // Determine the top 3 places
    int place = 1;
    for (size_t i = 0; i < ranked.size() && place <= 3; ++i) {
        const auto &group = ranked[i];
        if (group.empty()) continue;
        
        if (group.size() == 1) {
            if (place == 1) result["1st"] = group[0].name;
            else if (place == 2) result["2nd"] = group[0].name;
            else if (place == 3) result["3rd"] = group[0].name;
            place++;
        } else {
            vector<string> names;
            for (const auto &c : group) {
                names.push_back(c.name);
            }
            sort(names.begin(), names.end());
            stringstream ss;
            for (size_t k = 0; k < names.size(); ++k) {
                if (k != 0) ss << ", ";
                ss << names[k];
            }
            if (place == 1) {
                ss << " (jump-off)";
                result["1st"] = ss.str();
                place += group.size(); // Skip next places if tied for 1st
            } else {
                ss << " (tie)";
                if (place == 2) result["2nd"] = ss.str();
                else if (place == 3) result["3rd"] = ss.str();
                place += group.size();
            }
        }
    }
    
    return result;
}