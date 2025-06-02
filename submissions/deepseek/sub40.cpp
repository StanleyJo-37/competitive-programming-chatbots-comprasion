#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    unordered_set<int> fav;
    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        fav.insert(x);
    }

    // The total number of teams is 2^n.
    int total_teams = 1 << n;
    // The total number of games is (2^{n+1} - 2) since each team except the champion loses exactly once.
    // But we need to maximize the number of games involving favorite teams.

    // We'll use dynamic programming to track the maximum number of games involving favorite teams.
    // The DP state will represent for a given segment of teams (aligned in a power-of-two size),
    // the maximum number of games involving favorite teams, considering:
    // - The number of favorite teams in the segment.
    // - Whether the segment has a team that can reach the upper bracket final (0, 1, or 2).

    // The DP state is dp[size][cnt][up][lo], where:
    // - size is the current segment size (power of two).
    // - cnt is the number of favorite teams in the segment.
    // - up is the number of favorite teams that can reach the upper bracket final (0, 1, or 2).
    // - lo is the number of favorite teams that can reach the lower bracket final (0 or 1).
    // The value is the maximum number of games involving favorite teams in this segment.

    // Initialize DP for segments of size 1 (individual teams).
    vector<vector<vector<vector<int>>>> dp(total_teams + 1,
        vector<vector<vector<int>>>(k + 1,
        vector<vector<int>>(3,
        vector<int>(2, -1))));

    for (int i = 1; i <= total_teams; ++i) {
        int cnt = fav.count(i) ? 1 : 0;
        if (cnt > k) continue;
        // For a single team, it can be in the upper bracket (up=1 if favorite, 0 otherwise).
        // It cannot be in the lower bracket yet (lo=0).
        dp[i][cnt][cnt][0] = 0;
    }

    // Iterate over segment sizes in powers of two.
    for (int size = 2; size <= total_teams; size <<= 1) {
        // Iterate over all possible segments of the current size.
        for (int l = 1; l <= total_teams; l += size) {
            int r = l + size - 1;
            int mid = (l + r) / 2;
            int half_size = size / 2;

            // The left segment is [l, mid], right segment is [mid+1, r].
            // We need to merge the DP states of left and right segments.
            vector<vector<vector<vector<int>>>> new_dp(k + 1,
                vector<vector<vector<int>>>(3,
                vector<vector<int>>(2, -1)));

            // Iterate over all possible counts of favorite teams in left and right segments.
            for (int cnt_l = 0; cnt_l <= k; ++cnt_l) {
                for (int up_l = 0; up_l <= 2; ++up_l) {
                    for (int lo_l = 0; lo_l <= 1; ++lo_l) {
                        if (dp[mid][cnt_l][up_l][lo_l] == -1) continue;
                        for (int cnt_r = 0; cnt_r <= k - cnt_l; ++cnt_r) {
                            for (int up_r = 0; up_r <= 2; ++up_r) {
                                for (int lo_r = 0; lo_r <= 1; ++lo_r) {
                                    if (dp[r][cnt_r][up_r][lo_r] == -1) continue;
                                    int total_cnt = cnt_l + cnt_r;
                                    if (total_cnt > k) continue;

                                    // The current segment's upper bracket can have:
                                    // - up_l + up_r favorite teams (but capped at 2).
                                    int new_up = min(up_l + up_r, 2);

                                    // The current segment's lower bracket can have:
                                    // - lo_l or lo_r (but only one can survive in the lower bracket).
                                    int new_lo = 0;
                                    if (lo_l || lo_r) {
                                        new_lo = 1;
                                    }

                                    // The number of games added is:
                                    // - Upper bracket game: if up_l + up_r >= 1, then 1 game is added.
                                    int games = dp[mid][cnt_l][up_l][lo_l] + dp[r][cnt_r][up_r][lo_r];
                                    if (up_l + up_r >= 1) {
                                        games += (up_l + up_r);
                                    }

                                    // Lower bracket games:
                                    // - First lower bracket game: if lo_l or lo_r is present, 1 game is added.
                                    if (lo_l + lo_r >= 1) {
                                        games += (lo_l + lo_r);
                                    }
                                    // - Second lower bracket game: if (up_l + up_r - new_up) > 0 and (lo_l or lo_r), then 1 game is added.
                                    // The number of teams dropping from upper to lower is (up_l + up_r - new_up).
                                    int drop = (up_l + up_r) - new_up;
                                    if (drop > 0 && (lo_l || lo_r)) {
                                        games += 2; // Because the drop and lower bracket team play.
                                    }

                                    // Update the new_dp state.
                                    if (games > new_dp[total_cnt][new_up][new_lo]) {
                                        new_dp[total_cnt][new_up][new_lo] = games;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Update the DP for the current segment.
            for (int cnt = 0; cnt <= k; ++cnt) {
                for (int up = 0; up <= 2; ++up) {
                    for (int lo = 0; lo <= 1; ++lo) {
                        if (new_dp[cnt][up][lo] > dp[r][cnt][up][lo]) {
                            dp[r][cnt][up][lo] = new_dp[cnt][up][lo];
                        }
                    }
                }
            }
        }
    }

    // The answer is the maximum value in the DP for the full segment [1, 2^n] with all k favorite teams.
    int max_games = 0;
    for (int up = 0; up <= 2; ++up) {
        for (int lo = 0; lo <= 1; ++lo) {
            if (dp[total_teams][k][up][lo] > max_games) {
                max_games = dp[total_teams][k][up][lo];
            }
        }
    }

    // Add one more game for the grand finals if there are favorite teams in either upper or lower bracket.
    if (max_games > 0) {
        max_games += 1;
    }

    cout << max_games << endl;
    return 0;
}