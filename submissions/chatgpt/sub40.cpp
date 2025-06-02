#include <bits/stdc++.h>
using namespace std;

// This problem is best solved using DP with memoization.
// We simulate the tournament recursively, always maximizing the number of games
// that include at least one favorite team, by controlling the outcomes optimally.

// For each group of teams (represented as a vector), we recursively simulate the tournament.
// At each round, we pair up teams, and for each pair, we can choose which team wins
// (since we can control the outcome). We want to maximize the number of games
// that include at least one favorite team.

// To avoid recomputation, we use memoization. Since the number of teams is up to 2^17 = 131072,
// we represent the set of favorite teams in the current group as a bitmask (if k is small),
// or as a set (if k is large). But since the number of possible team sets is huge, we use
// a map from vector<int> (sorted) to int for memoization.

// For each group, we return the maximal number of games with at least one favorite team
// that can be played in the tournament for that group.

int n, k;
vector<int> fav; // favorite teams (1-based)

// Memoization: map from vector of favorite teams in current group to maximal games
map<vector<int>, int> memo;

// Helper function to check if a team is favorite
bool is_fav(int team) {
    return binary_search(fav.begin(), fav.end(), team);
}

// Recursive DP function
// teams: vector of team numbers in current group (sorted)
// favs: vector of favorite teams in current group (sorted)
int dp(vector<int>& teams, vector<int>& favs) {
    // If only one team remains, no more games
    if (teams.size() == 1) return 0;

    // Memoization key: only the favorite teams in this group matter
    vector<int> key = favs;
    if (memo.count(key)) return memo[key];

    int sz = teams.size();
    int max_games = 0;

    // For each possible way to pair up teams, we can choose which team wins
    // For each pair, we can choose which team advances (either left or right)
    // For each possible combination of winners, we simulate the next round

    // Since the number of possible combinations is 2^(sz/2), which is too large,
    // we can use the following greedy approach:
    // For each pair, if at least one is favorite, we can ensure a favorite advances.
    // So, for each pair, we maximize the number of games with at least one favorite.

    // Count number of pairs where at least one is favorite
    int games_with_fav = 0;
    vector<int> next_teams;
    vector<int> next_favs;

    for (int i = 0; i < sz; i += 2) {
        int t1 = teams[i], t2 = teams[i+1];
        bool f1 = is_fav(t1), f2 = is_fav(t2);
        if (f1 || f2) games_with_fav++;
        // We can always choose the favorite to advance if there is one
        if (f1 && !f2) {
            next_teams.push_back(t1);
            next_favs.push_back(t1);
        } else if (!f1 && f2) {
            next_teams.push_back(t2);
            next_favs.push_back(t2);
        } else if (f1 && f2) {
            // Both are favorite, we can choose either
            // To maximize future games, we can try both options and take the best
            // But since both are favorite, advancing either is equivalent
            next_teams.push_back(t1);
            next_favs.push_back(t1);
        } else {
            // Neither is favorite, just pick one
            next_teams.push_back(t1);
            // No favorite advances
        }
    }

    // Remove duplicates in next_favs (shouldn't be any, but just in case)
    sort(next_favs.begin(), next_favs.end());

    // Recurse to next round
    max_games = games_with_fav + dp(next_teams, next_favs);

    // Memoize and return
    memo[key] = max_games;
    return max_games;
}

// For double elimination, we need to simulate both upper and lower brackets
// We need to maximize the total number of games with favorite teams in both brackets
// We simulate the tournament round by round, keeping track of which teams are in upper and lower brackets

// To do this, we use a recursive function that, for a given set of teams in upper and lower brackets,
// returns the maximal number of games with favorite teams that can be played from this state

// We use memoization with a map from (upper_favs, lower_favs) to int

struct State {
    vector<int> upper_favs;
    vector<int> lower_favs;
    bool operator<(const State& other) const {
        if (upper_favs != other.upper_favs) return upper_favs < other.upper_favs;
        return lower_favs < other.lower_favs;
    }
};

map<State, int> memo2;

// teams_upper: teams in upper bracket (sorted)
// favs_upper: favorite teams in upper bracket (sorted)
// teams_lower: teams in lower bracket (sorted)
// favs_lower: favorite teams in lower bracket (sorted)
int dp2(vector<int>& teams_upper, vector<int>& favs_upper,
        vector<int>& teams_lower, vector<int>& favs_lower) {
    // If both brackets have only one team, it's the grand final
    if (teams_upper.size() == 1 && teams_lower.size() == 1) {
        // Grand final: one game between the two teams
        // If at least one is favorite, count it
        int res = 0;
        if (is_fav(teams_upper[0]) || is_fav(teams_lower[0])) res = 1;
        return res;
    }

    // Memoization key
    State key = {favs_upper, favs_lower};
    if (memo2.count(key)) return memo2[key];

    int sz = teams_upper.size();
    int games_this_round = 0;

    // Upper bracket: pair up teams, winners advance in upper, losers drop to lower
    vector<int> next_upper_teams, next_upper_favs;
    vector<int> drop_teams, drop_favs;
    for (int i = 0; i < sz; i += 2) {
        int t1 = teams_upper[i], t2 = teams_upper[i+1];
        bool f1 = is_fav(t1), f2 = is_fav(t2);
        if (f1 || f2) games_this_round++;
        // We can always choose the favorite to advance if there is one
        if (f1 && !f2) {
            next_upper_teams.push_back(t1);
            next_upper_favs.push_back(t1);
            drop_teams.push_back(t2);
            if (f2) drop_favs.push_back(t2);
        } else if (!f1 && f2) {
            next_upper_teams.push_back(t2);
            next_upper_favs.push_back(t2);
            drop_teams.push_back(t1);
            if (f1) drop_favs.push_back(t1);
        } else if (f1 && f2) {
            // Both are favorite, we can choose either
            // To maximize future games, we can try both options and take the best
            // But since both are favorite, advancing either is equivalent
            next_upper_teams.push_back(t1);
            next_upper_favs.push_back(t1);
            drop_teams.push_back(t2);
            drop_favs.push_back(t2);
        } else {
            // Neither is favorite, just pick one
            next_upper_teams.push_back(t1);
            drop_teams.push_back(t2);
        }
    }

    // Lower bracket: two phases
    // 1. First, the teams already in lower bracket play each other, losers eliminated, winners advance
    // 2. Then, the winners from phase 1 play the drop_teams from upper bracket, losers eliminated, winners advance

    // Phase 1: lower bracket teams play each other
    vector<int> phase1_teams, phase1_favs;
    vector<int> phase1_winners, phase1_winner_favs;
    int sz_lower = teams_lower.size();
    int games_lower1 = 0;
    for (int i = 0; i < sz_lower; i += 2) {
        int t1 = teams_lower[i], t2 = teams_lower[i+1];
        bool f1 = is_fav(t1), f2 = is_fav(t2);
        if (f1 || f2) games_lower1++;
        // We can always choose the favorite to advance if there is one
        if (f1 && !f2) {
            phase1_winners.push_back(t1);
            phase1_winner_favs.push_back(t1);
        } else if (!f1 && f2) {
            phase1_winners.push_back(t2);
            phase1_winner_favs.push_back(t2);
        } else if (f1 && f2) {
            // Both are favorite, pick one
            phase1_winners.push_back(t1);
            phase1_winner_favs.push_back(t1);
        } else {
            // Neither is favorite, pick one
            phase1_winners.push_back(t1);
        }
    }

    // Phase 2: phase1_winners play