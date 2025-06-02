#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

// dp[round][ub_teams_mask][lb_teams_mask]
// round: current round (from n down to 0)
// ub_teams_mask: bitmask of favorite teams remaining in upper bracket
// lb_teams_mask: bitmask of favorite teams remaining in lower bracket
// The values in the map represent the maximum number of games involving favorite teams.
map<int, map<int, map<int, int>>> memo;

int solve(int n, int ub_teams_mask, int lb_teams_mask, const vector<bool>& is_favorite) {
    // Base case: If no rounds left, no more games can be played.
    if (n == 0) {
        return 0;
    }

    // Check if the result is already memoized
    if (memo.count(n) && memo[n].count(ub_teams_mask) && memo[n][ub_teams_mask].count(lb_teams_mask)) {
        return memo[n][ub_teams_mask][lb_teams_mask];
    }

    int max_games = 0;
    int total_teams = 1 << n; // Total teams in current stage
    int ub_size = total_teams / 2; // Teams in upper bracket for this round
    int lb_size = total_teams / 2; // Teams in lower bracket for this round initially

    // Iterate through all possible pairings in the upper bracket
    // A bitmask 'i' represents the teams that win their upper bracket matches
    // within the current set of favorite teams.
    // We only care about how favorite teams split. Non-favorite teams
    // don't contribute to the mask but are part of the game logic.
    for (int ub_wins_mask = 0; ub_wins_mask < (1 << ub_size); ++ub_wins_mask) {
        // ub_wins_mask represents winners from the first set of games in UB.
        // We need to ensure that if a favorite team 'j' is in ub_teams_mask
        // and its corresponding bit in ub_wins_mask is set, it means 'j' won.
        // And if it's not set, it means 'j' lost.

        // Calculate the next upper bracket mask and the teams dropping to lower bracket
        int next_ub_mask = 0;
        int ub_to_lb_mask = 0;
        int current_games = 0; // Games involving favorite teams in this round

        // Simulate Upper Bracket games
        for (int i = 0; i < ub_size; ++i) { // Iterating through pairs
            int team1_original_idx = i * 2;
            int team2_original_idx = i * 2 + 1;

            bool team1_fav = (ub_teams_mask >> team1_original_idx) & 1;
            bool team2_fav = (ub_teams_mask >> team2_original_idx) & 1;

            // If either team is a favorite, this game counts.
            if (team1_fav || team2_fav) {
                current_games++;
            }

            // Determine the winner and loser for these two teams
            bool winner_is_team1 = (ub_wins_mask >> i) & 1; // 1 means team1 wins, 0 means team2 wins

            if (winner_is_team1) { // Team 1 wins, Team 2 loses
                if (team1_fav) {
                    next_ub_mask |= (1 << (i)); // Winner advances to next UB round
                }
                if (team2_fav) {
                    ub_to_lb_mask |= (1 << (i)); // Loser drops to LB
                }
            } else { // Team 2 wins, Team 1 loses
                if (team2_fav) {
                    next_ub_mask |= (1 << (i)); // Winner advances to next UB round
                }
                if (team1_fav) {
                    ub_to_lb_mask |= (1 << (i)); // Loser drops to LB
                }
            }
        }

        // Simulate Lower Bracket Round 1 (LB vs LB)
        // lb_teams_mask contains 2^(n-1) teams. These play 2^(n-2) games.
        // Each game has a winner (advances in LB) and a loser (eliminated).
        int lb_round1_games_count = (1 << (n - 1)) / 2;
        for (int lb_wins_mask_r1 = 0; lb_wins_mask_r1 < (1 << lb_round1_games_count); ++lb_wins_mask_r1) {
            int next_lb_mask_r1_winners = 0; // Teams that won in LB round 1
            int next_lb_mask_r1_losers = 0;  // Teams that lost in LB round 1 (eliminated)

            for (int i = 0; i < lb_round1_games_count; ++i) {
                int team1_original_idx = i * 2;
                int team2_original_idx = i * 2 + 1;

                bool team1_fav = (lb_teams_mask >> team1_original_idx) & 1;
                bool team2_fav = (lb_teams_mask >> team2_original_idx) & 1;

                if (team1_fav || team2_fav) {
                    current_games++;
                }

                bool winner_is_team1 = (lb_wins_mask_r1 >> i) & 1;

                if (winner_is_team1) {
                    if (team1_fav) {
                        next_lb_mask_r1_winners |= (1 << i);
                    }
                    if (team2_fav) {
                        next_lb_mask_r1_losers |= (1 << i); // Losers are eliminated, but we use this to track fav teams
                    }
                } else {
                    if (team2_fav) {
                        next_lb_mask_r1_winners |= (1 << i);
                    }
                    if (team1_fav) {
                        next_lb_mask_r1_losers |= (1 << i); // Losers are eliminated
                    }
                }
            }

            // Simulate Lower Bracket Round 2 (LB R1 winners vs UB losers)
            // The teams that won LB R1 (next_lb_mask_r1_winners) play against
            // teams that dropped from UB (ub_to_lb_mask).
            int lb_round2_games_count = (1 << (n - 1)) / 2; // Same number of games as R1
            for (int lb_wins_mask_r2 = 0; lb_wins_mask_r2 < (1 << lb_round2_games_count); ++lb_wins_mask_r2) {
                int next_lb_mask = 0; // Teams remaining in LB for the next round
                int current_lb_r2_games = 0;

                for (int i = 0; i < lb_round2_games_count; ++i) {
                    // Check if current game involves favorite teams (one from ub_to_lb_mask, one from next_lb_mask_r1_winners)
                    bool ub_loser_fav = (ub_to_lb_mask >> i) & 1;
                    bool lb_r1_winner_fav = (next_lb_mask_r1_winners >> i) & 1;

                    if (ub_loser_fav || lb_r1_winner_fav) {
                        current_lb_r2_games++;
                    }

                    bool winner_is_ub_loser = (lb_wins_mask_r2 >> i) & 1;

                    if (winner_is_ub_loser) { // UB loser wins, LB R1 winner loses
                        if (ub_loser_fav) {
                            next_lb_mask |= (1 << i);
                        }
                    } else { // LB R1 winner wins, UB loser loses
                        if (lb_r1_winner_fav) {
                            next_lb_mask |= (1 << i);
                        }
                    }
                }

                // Recursively call for the next round (n-1)
                // Add current games plus the result of the recursive call.
                max_games = max(max_games, current_games + current_lb_r2_games +
                                           solve(n - 1, next_ub_mask, next_lb_mask, is_favorite));
            }
        }
    }

    // Grand Finals (n=1 becomes Grand Finals)
    if (n == 1) {
        // If both UB and LB have a favorite team, and they meet in GF, it's 1 game.
        // This is implicitly handled by the base case and subsequent calls where
        // when n=1, a favorite team in UB and LB will contribute 1 to current_games
        // if they meet in the final.
        // The structure assumes games are always played if teams are present.
        // If ub_teams_mask and lb_teams_mask both have a favorite team at n=1,
        // it means there are 2 teams left total. If both are favorite, this game counts.
        // If one is favorite, this game counts. If neither are favorite, it doesn't.
        // The recursive call at n=1 will be `solve(0, ...)` which returns 0.
        // So the game itself must be counted here.
        if (ub_teams_mask == 1 && lb_teams_mask == 1) { // Both finalists are favorite
            max_games = max(max_games, 1);
        } else if (ub_teams_mask == 1 || lb_teams_mask == 1) { // One finalist is favorite
            max_games = max(max_games, 1);
        }
        // If neither is favorite, 0 games added.
    }


    // Store the result in memoization table
    memo[n][ub_teams_mask][lb_teams_mask] = max_games;
    return max_games;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    // is_favorite array to quickly check if a team is a favorite.
    // Teams are 1-indexed in problem, convert to 0-indexed for bitmasks.
    vector<bool> is_favorite(1 << n, false);
    for (int i = 0; i < k; ++i) {
        int team_num;
        cin >> team_num;
        is_favorite[team_num - 1] = true;
    }

    // Initial state: all favorite teams are in the upper bracket.
    // ub_initial_mask represents the bitmask of favorite teams.
    int ub_initial_mask = 0;
    for (int i = 0; i < (1 << n); ++i) {
        if (is_favorite[i]) {
            ub_initial_mask |= (1 << i);
        }
    }

    // The initial call starts with all favorite teams in the upper bracket,
    // and no teams yet in the lower bracket.
    // The `is_favorite` vector is passed to allow checking individual team favorites.
    cout << solve(n, ub_initial_mask, 0, is_favorite) << endl;

    return 0;
}