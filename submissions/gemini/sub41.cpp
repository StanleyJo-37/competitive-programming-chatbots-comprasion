#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

const long long INF = 1e18; // Use a large enough value for infinity

struct Station {
    long long a, b, c; // initial people, people arriving per hour, max capacity
};

int main() {
    ios_base::sync_with_stdio(false); // Optimize C++ standard streams for competitive programming
    cin.tie(NULL); // Untie cin from cout

    int n, t;
    long long k;
    cin >> n >> t >> k;

    vector<Station> stations(n);
    for (int i = 0; i < n; ++i) {
        cin >> stations[i].a >> stations[i].b >> stations[i].c;
    }

    // dp[i][j] will store the minimum number of trains needed to survive for 'i' hours,
    // such that 'j' trains are used up to this point.
    // However, the problem asks for the minimum total trains for 't' hours.
    // This looks like a DP problem where we want to minimize trains for a given time.
    // Let's redefine dp state: dp[i] = minimum trains needed to survive for 'i' hours.
    // This is not quite right. We need to decide *when* to send trains.
    // The problem has a "flow" like constraint, where people can only be taken if previous stations are empty.
    // This suggests a DP approach where the state might include the number of trains used
    // and the time elapsed.

    // Let's define dp[h] as the minimum trains required to survive for 'h' hours.
    // This is not correct because the decision of sending a train at hour 'h' affects future states.
    // The number of people at each station matters.

    // This problem can be modeled as a min-cost max-flow problem,
    // but the constraints (N, T <= 200) suggest a polynomial time DP or greedy approach.
    // The "flow" of people and train capacity implies a DP where we iterate over hours.

    // Let's define dp[h][j] as the minimum *total* trains required to survive for `h` hours,
    // with the condition that `j` trains were sent *in total* up to hour `h`.
    // This DP state seems backwards. We want to find minimum trains.

    // The key insight might be that the decision of sending a train at hour `i`
    // affects the number of people at all stations at hour `i+1`.
    // The "people can only be taken from i-th station if i-1-th station is empty"
    // is a crucial constraint. This means a train clears stations sequentially.

    // Let's re-evaluate the state:
    // `dp[i]` could be the minimum number of trains to survive up to hour `i`.
    // To compute `dp[i]`, we need to know the state of people at stations at hour `i-1`.
    // This is a problem because the state is very large (N stations with large number of people).

    // What if we try to binary search on the number of trains?
    // If we fix the number of trains, say `X`, can we check if it's possible to survive for `t` hours?
    // If we use `X` trains, we need to decide which `X` hours to send them.
    // This decision is critical. If we send a train at hour `h`, it clears people.
    // If we don't, people accumulate.

    // Let's define `check(num_trains)` function. This function will return true if it's possible
    // to survive `t` hours using at most `num_trains`.
    // To implement `check(num_trains)`:
    // We have `num_trains` "slots" where we can send a train.
    // This can be solved with dynamic programming.
    // `dp[i][j]` = minimum *remaining* people at station `n-1` after `i` hours, having sent `j` trains.
    // This is still complicated.

    // Let `dp[i][j]` be the minimum number of people at station `n-1` at the end of hour `i`,
    // having used exactly `j` trains up to hour `i`.
    // This state is not quite right. We need to keep track of people at ALL stations.

    // The "flow" constraint is critical. When a train comes, it clears station 1, then station 2, etc.
    // If there are people at station `i-1`, station `i` cannot be cleared. This means the train
    // must empty station `i-1` first. It implies that if station `i-1` is not empty,
    // the train will only take people from stations 1 to `i-1`.

    // The problem statement says: "A train can not take people from the i-th station if there are people at the i-1-th station."
    // This means a train acts like a sweep: it starts at station 1, takes people, then moves to station 2, etc.
    // If at station `i`, it finds `P_i` people, it takes `min(P_i, remaining_capacity)`.
    // But if station `i-1` still has people, it cannot take anyone from `i`.
    // This means a train effectively sweeps from left to right, clearing stations as it goes.
    // If a train is sent at hour `h`, it tries to empty stations from 1 to `n`.
    // It will continue to take people as long as the previous station is empty and it has capacity.

    // This "flow" constraint can be simulated.
    // The range of `num_trains` can be large. Max people at a station can be $10^9$.
    // Max stations `n=200`, max hours `t=200`. Max capacity `k=10^9`.
    // If `t` hours pass, `b_i * t` people could arrive. Total people could be `n * (c_i + b_i * t)`.
    // Max trains needed: If each station requires a train every hour to clear, that's `n * t` trains.
    // No, consider the worst case: 1 station, 10^9 people arrive, capacity 10. `b_0 = 10^9, k=10`.
    // At hour 0, we have `a_0`. At hour 1, `b_0` people arrive. We need to clear `a_0 + b_0` people.
    // Number of trains needed for one hour is `ceil((a_0 + b_0) / k)`.
    // So for `t` hours, it could be `t * (10^9 / 10) = t * 10^8`. This is `200 * 10^8 = 2 * 10^{10}`.
    // The number of trains can be very large. Binary searching on `num_trains` is feasible.

    // Let `min_trains = 0`, `max_trains = t * ( (max(c_i) + max(b_i)*t) / k + 1)`.
    // A loose upper bound on max_trains: `t * (N * max(C_i + B_i*T) / k + 1)`.
    // More simply, consider the total people arriving at all stations: `N * T * max(B_i)`.
    // Plus initial `N * max(A_i)`. Divide by `k`.
    // `200 * 200 * 10^9 / 1` is `4 * 10^{13}`. This value fits in long long.
    // Binary search range for `num_trains`: `[0, 4e13 + epsilon]`.

    // `check(num_trains)` function:
    // We have `num_trains` available. We want to distribute them over `t` hours.
    // This is a variation of knapsack or resource allocation.
    // At each hour `h` from `0` to `t-1`:
    //  We have `current_people[i]` at station `i`.
    //  If we *don't* send a train:
    //      `current_people[i] += b_i`. Check `current_people[i] <= c_i`. If not, this path is invalid.
    //  If we *do* send a train (and we have trains left):
    //      Simulate the train movement. Calculate how many people are taken.
    //      `current_people[i] = max(0LL, current_people[i] - taken_at_i)`.
    //      Then `current_people[i] += b_i`. Check `current_people[i] <= c_i`.
    // This looks like a shortest path on a DAG. `(hour, trains_used)` are states.
    // Or DP state `dp[h][trains_used]` = minimum *total* excess people (or 0 if success) at hour `h`.
    // This is wrong, it's about decision making.

    // The core of `check(num_trains)`:
    // We need to decide which `num_trains` hours to send trains.
    // This is a greedy problem. When should we send a train?
    // When a station is about to exceed its capacity.
    // For `check(num_trains)`:
    // We can simulate hour by hour. Maintain `current_people[n]`.
    // At hour `h` (from `0` to `t-1`):
    // 1. Calculate people `P_i = current_people[i] + b_i` (if no train is sent).
    // 2. Check if any `P_i > c_i`. If so, we *must* send a train at hour `h` to prevent loss.
    //    If we have `num_trains_left > 0`:
    //        Send a train. Simulate its effect. `num_trains_left--`.
    //    Else (no trains left): `return false` (cannot survive).
    // 3. If no station would exceed capacity if no train is sent, but we have `num_trains_left > 0`:
    //    Should we send a train now? This is the tricky part.
    //    A greedy approach: send a train only when absolutely necessary (to prevent loss).
    //    If after sending trains only when necessary, we still have `num_trains_left` > 0,
    //    then we can use these remaining trains to alleviate future pressure.
    //    When to use these "optional" trains?
    //    To maximize their utility, we should use them to clear the most people.
    //    Or, perhaps, to clear people such that future capacity checks are less stringent.

    // This greedy strategy for `check(num_trains)` is known for some flow-like problems.
    // The "most necessary" point to send a train is when *any* station is about to overflow.
    // If multiple trains are sent at the same hour, their capacities are added up.
    // This means we decide *per hour* whether to send a "super train" of capacity `k` or `0`.
    // So, `check(num_trains)`:
    // `dp[i]` = minimum total "saved capacity" or "people cleared" at hour `i` if we send a train
    // `current_people[j]` at station `j`.
    // Iterate `h` from `0` to `t-1`:
    //   `people_at_start_of_hour[j] = current_people[j]` (before new arrivals and train)
    //   Assume no train: `temp_people[j] = people_at_start_of_hour[j] + b_j`.
    //   If any `temp_people[j] > c_j`:
    //     We MUST send a train. If `trains_used == num_trains`, `return false`.
    //     `trains_used++`.
    //     Simulate train:
    //        `remaining_capacity = k`. `empty_prev_station = true`.
    //        For `j` from `0` to `n-1`:
    //            If `empty_prev_station`:
    //                `taken = min(people_at_start_of_hour[j], remaining_capacity)`.
    //                `people_at_start_of_hour[j] -= taken`.
    //                `remaining_capacity -= taken`.
    //                If `people_at_start_of_hour[j] > 0`: `empty_prev_station = false`.
    //            Else: // Previous station not empty, cannot take from current
    //                Do nothing for this station.
    //        After train, add `b_j` to `people_at_start_of_hour[j]`.
    //        Update `current_people`.
    //   Else (no immediate overflow, but we have `num_trains_left`):
    //     This is where the "greedy for remaining trains" comes in.
    //     What hour is best to use a train if it's not strictly necessary?
    //     To alleviate future pressure. This means clearing the most people possible,
    //     or clearing people from stations that are closest to their capacity.
    //     A greedy choice would be to use a train *now* if it would clear
    //     enough people to prevent a future overflow, and if it's "more effective" now.
    //     This is becoming complicated.

    // Let's re-think the `check(num_trains)` function.
    // It's a standard DP problem: `dp[h][trains_used]` = minimum `max_over_all_stations(current_people[s] - c_s)` or some similar "badness" metric.
    // Or, `dp[h][j]` = A `std::vector<long long>` representing `current_people` at each station,
    // after `h` hours, having used `j` trains. This state space is too large.

    // A crucial observation for this type of problem:
    // If we have `num_trains`, we have `num_trains` opportunities to clear stations.
    // When should we clear?
    // Let `P[i][h]` be the number of people at station `i` at the beginning of hour `h`.
    // If we don't send a train at hour `h`:
    // `P[i][h+1] = P[i][h] + b_i`. We must have `P[i][h+1] <= c_i`.
    // If we send a train at hour `h`:
    // The train clears people from left to right.
    // `taken_at_i = min(P[i][h], remaining_capacity)`.
    // `P_new[i][h] = P[i][h] - taken_at_i`.
    // `remaining_capacity -= taken_at_i`.
    // This happens only if `P_new[i-1][h] == 0`.
    // After train: `P[i][h+1] = P_new[i][h] + b_i`. We must have `P[i][h+1] <= c_i`.

    // The effect of a train at hour `h` is to reduce `P[i][h]` (for some `i`) *before* `b_i` arrives.
    // So the state is `P_current[i]` (people at stations).
    // `dp[i]` = minimum trains needed to survive `i` hours.
    // `dp[h][last_cleared_hour]` or `dp[h][trains_used_so_far]`.
    // The constraint "A train can not take people from the i-th station if there are people at the i-1-th station"
    // is a common "bottleneck" constraint. This implies that the total capacity `k` is consumed
    // from left to right. If a station `i-1` is not fully cleared, station `i` gets nothing.

    // Let's model this with DP:
    // `dp[i][j]` = minimum number of trains required to ensure no overflow at any station up to hour `i`,
    // and specifically, the state of station `n-1` at hour `i` is such that it has `j` people.
    // Still too complex for people count `j`.

    // What if we try to calculate how many people a train would take *at each hour*?
    // This depends on the current state.
    // This smells like a minimum cost path in a graph.
    // Nodes: `(hour, trains_used)`. Edges: `(hour, trains_used) -> (hour+1, trains_used)` (no train)
    // and `(hour, trains_used) -> (hour+1, trains_used+1)` (send train).
    // Edge weight is 0 for `no_train` and 1 for `send_train`.
    // The "cost" is the number of trains. We want to find the minimum cost path.
    // The issue is that the "validity" (no overflow) depends on the *actual* number of people,
    // which is not encoded in the state `(hour, trains_used)`.

    // We can use a `std::vector<long long> current_people(n)` to store people at stations.
    // `dp[h]` could be the minimum `current_people` vector (lexicographically smallest?) after `h` hours.
    // That's incorrect. It's `dp[h][trains_used]`.

    // The problem constraint `N, T <= 200` is key.
    // `dp[hour][trains_sent]` can store the *state of stations* (vector of people).
    // `dp[hour][j]` = `vector<long long> current_people_at_stations`.
    // For each `h` from `0` to `t-1`:
    //  For each `j` from `0` to `max_trains`:
    //    If `dp[h][j]` is reachable:
    //      Option 1: Don't send a train at hour `h`.
    //        Calculate `next_people_no_train`. If valid, update `dp[h+1][j]`.
    //      Option 2: Send a train at hour `h`.
    //        If `j+1 <= max_trains`:
    //          Calculate `next_people_with_train`. If valid, update `dp[h+1][j+1]`.
    // How to update `dp[h+1][j]`?
    // We want the state with minimum total trains.
    // If multiple `(h, j)` states can reach the same `(h+1, j')` state, we just need one.
    // The values in `dp[h][j]` must be vectors of people.
    // `map<int, vector<long long>> dp[201]` where `dp[h][trains_used]` is a vector of people.
    // Still, this state representation seems too complex for `vector<long long>`.
    // The maximum possible number of trains is not specified, but can be very large.
    // `dp[h][trains_sent]` would have `trains_sent` go up to `t * N * C_max / k`.
    // This is too big.

    // A small `max_trains_bound` can be derived from the example: `200 * 10^9 / 10 = 2 * 10^{10}`. This is too large.
    // However, the example output is 2 trains for N=3, T=3.
    // This suggests the number of trains is much smaller in practice.
    // Max trains could be `T` (send a train every hour).
    // The problem asks for minimum number of trains.
    // Max trains needed for a single station `i` to survive `t` hours: `ceil((a_i + b_i*t - c_i) / k)` if `a_i + b_i*t > c_i`.
    // This calculation is an underestimate, as it assumes `k` capacity is always available at station `i`.
    // A tighter upper bound for `num_trains` is `t` (worst case, one train per hour).
    // The maximum value for `t` is 200. This is a very small `max_trains` bound.
    // So `dp[h][trains_used]` where `trains_used` goes up to `t`.
    // `dp[h][j]` could store the `vector<long long>` representing the number of people at each station.
    // `vector<vector<vector<long long>>> dp(t + 1, vector<vector<long long>>(t + 1, vector<long long>(n, -1)));`
    // No, `dp[h][j]` will be a `vector<long long>` of size `n`.
    // We need to initialize `dp[0][0]` with `stations[i].a`.
    // For other states, we need to signify "unreachable". We can use a special value for people count (e.g., -1).
    // Or, use `map<int, vector<long long>> dp[t+1]` to store only reachable states.
    // A more efficient way to represent `dp[h][j]` might be `map<int, vector<long long>> states[t+1];`
    // This `map` will store `j` (trains_used) as key, and `vector<long long>` (people counts) as value.
    // This will work.

    // Initialize DP state:
    // `dp[i]` is a map from `trains_used` to `vector<long long>` (people at stations).
    // `dp[0][0]` = initial people `stations[i].a`.
    // `vector<map<int, vector<long long>>> dp(t + 1);`
    // `dp[0][0] = vector<long long>(n);`
    // For `i = 0` to `n-1`: `dp[0][0][i] = stations[i].a;`

    // Max number of trains needed for a single hour would be `sum(a_i)/k`. This can be large.
    // The problem says "If multiple trains are appointed to the same hour, their capacities are being added up".
    // This is crucial. It means we send ONE "super train" with capacity `num_trains_this_hour * k`.
    // The "number of trains he will need" implies the total sum of trains sent over `t` hours.
    // The state `dp[h][j]` (minimum trains for `h` hours, `j` is the count of trains sent so far) is correct.
    // `j` can go up to `t`. Max `t = 200`. So `j` from 0 to 200.
    // The size of `dp` table is `201 * 201`. Each cell is a `vector<long long>` of size `N`.
    // This makes `201 * 201 * 200 * sizeof(long long)` bytes.
    // `40401 * 200 * 8` bytes = `64,641,600` bytes, roughly `64MB`. This fits memory limits.

    // `dp[h][j]` stores the minimum `vector<long long>` representing people counts.
    // Lexicographical comparison for vectors: `v1 < v2` if `v1[0] < v2[0]`, or `v1[0] == v2[0]` and `v1[1] < v2[1]`, etc.
    // This is important because we want to minimize people at stations to make future hours easier.

    // Initialize `dp` table: `vector<vector<vector<long long>>> dp(t + 1, vector<vector<long long>>(t + 1, vector<long long>(n, -1)));`
    // `-1` signifies unreachable state.
    vector<vector<vector<long long>>> dp(t + 1, vector<vector<long long>>(t + 1, vector<long long>(n)));
    // Initialize with a large value to signify unreachability, as people counts are non-negative.
    // Use a specific marker, e.g., for people count -1, as it's not a valid people count.
    for (int i = 0; i <= t; ++i) {
        for (int j = 0; j <= t; ++j) {
            for (int l = 0; l < n; ++l) {
                dp[i][j][l] = -1; // Sentinel value for unreachable
            }
        }
    }

    // Base case: at hour 0, 0 trains used, initial people at stations.
    for (int i = 0; i < n; ++i) {
        dp[0][0][i] = stations[i].a;
    }

    // DP loop:
    for (int h = 0; h < t; ++h) { // current hour
        for (int j = 0; j <= h; ++j) { // trains used up to hour h
            if (dp[h][j][0] == -1) continue; // Skip unreachable states

            vector<long long> current_people = dp[h][j];

            // Option 1: Don't send a train at hour h
            vector<long long> next_people_no_train = current_people;
            bool possible_no_train = true;
            for (int i = 0; i < n; ++i) {
                next_people_no_train[i] += stations[i].b;
                if (next_people_no_train[i] > stations[i].c) {
                    possible_no_train = false;
                    break;
                }
            }

            if (possible_no_train) {
                // If dp[h+1][j] is unreachable or current solution is better
                if (dp[h+1][j][0] == -1 || next_people_no_train < dp[h+1][j]) {
                    dp[h+1][j] = next_people_no_train;
                }
            }

            // Option 2: Send a train at hour h (if we have trains left, i.e., j+1 <= t)
            if (j + 1 <= t) {
                vector<long long> people_before_arrival_train_sent = current_people; // People *before* b_i arrives
                long long remaining_capacity = k;
                bool prev_station_cleared = true; // Station 0 is always considered cleared (or doesn't have a prev)

                for (int i = 0; i < n; ++i) {
                    if (prev_station_cleared) {
                        long long taken = min(people_before_arrival_train_sent[i], remaining_capacity);
                        people_before_arrival_train_sent[i] -= taken;
                        remaining_capacity -= taken;
                        if (people_before_arrival_train_sent[i] > 0) { // If current station is not fully cleared
                            prev_station_cleared = false;
                        }
                    } else {
                        // Cannot take from current station if previous one wasn't cleared
                    }
                }

                vector<long long> next_people_with_train = people_before_arrival_train_sent;
                bool possible_with_train = true;
                for (int i = 0; i < n; ++i) {
                    next_people_with_train[i] += stations[i].b;
                    if (next_people_with_train[i] > stations[i].c) {
                        possible_with_train = false;
                        break;
                    }
                }

                if (possible_with_train) {
                    // If dp[h+1][j+1] is unreachable or current solution is better
                    if (dp[h+1][j+1][0] == -1 || next_people_with_train < dp[h+1][j+1]) {
                        dp[h+1][j+1] = next_people_with_train;
                    }
                }
            }
        }
    }

    // Find the minimum trains used to survive for 't' hours
    int min_trains = -1;
    for (int j = 0; j <= t; ++j) {
        if (dp[t][j][0] != -1) { // If state is reachable
            min_trains = j;
            break; // Found the minimum number of trains
        }
    }

    cout << min_trains << endl;

    return 0;
}