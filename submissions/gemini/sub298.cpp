#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <limits>

// Define a large enough value for infinity for long long
const long long INF_LL = std::numeric_limits<long long>::max();

// Structure to represent an interval [start, end]
struct Interval {
    long long start;
    long long end;

    // Custom comparison for sorting intervals, primarily by start, then by end
    bool operator<(const Interval& other) const {
        if (start != other.start) {
            return start < other.start;
        }
        return end < other.end;
    }
};

// Function to merge overlapping intervals in a sorted list
std::vector<Interval> merge_intervals(std::vector<Interval> intervals) {
    if (intervals.empty()) {
        return {};
    }
    // Sort intervals by their start points
    std::sort(intervals.begin(), intervals.end());
    
    std::vector<Interval> merged;
    merged.push_back(intervals[0]); // Start with the first interval
    
    // Iterate through the rest of the intervals
    for (size_t i = 1; i < intervals.size(); ++i) {
        // If the current interval overlaps with or touches the last merged interval
        if (intervals[i].start <= merged.back().end + 1) { // +1 to handle adjacent intervals like [1,2] and [3,4]
            // Extend the end of the last merged interval
            merged.back().end = std::max(merged.back().end, intervals[i].end);
        } else {
            // No overlap, add the current interval as a new merged interval
            merged.push_back(intervals[i]);
        }
    }
    return merged;
}

// Function to compute the complement of a set of intervals within a given range [min_val, max_val]
std::vector<Interval> complement_intervals(const std::vector<Interval>& cursed_intervals, long long min_val, long long max_val) {
    std::vector<Interval> safe_intervals;
    long long current_pos = min_val; // Start from the beginning of the overall range
    
    for (const auto& interval : cursed_intervals) {
        // If there's a gap between current_pos and the start of the cursed interval
        if (current_pos <= interval.start - 1) { // Use <= and -1 to handle integer boundaries
            safe_intervals.push_back({current_pos, interval.start - 1});
        }
        // Move current_pos past the end of the current cursed interval
        current_pos = std::max(current_pos, interval.end + 1);
    }
    // If there's a remaining safe region at the end
    if (current_pos <= max_val) {
        safe_intervals.push_back({current_pos, max_val});
    }
    return safe_intervals;
}

// Function to compute the intersection of two sets of disjoint intervals
std::vector<Interval> intersect_intervals(const std::vector<Interval>& intervals1, const std::vector<Interval>& intervals2) {
    std::vector<Interval> result;
    size_t i = 0, j = 0;
    // Use two pointers to iterate through both lists of intervals
    while (i < intervals1.size() && j < intervals2.size()) {
        // Calculate the intersection of the current intervals from both lists
        long long intersect_start = std::max(intervals1[i].start, intervals2[j].start);
        long long intersect_end = std::min(intervals1[i].end, intervals2[j].end);
        
        // If an intersection exists (start <= end)
        if (intersect_start <= intersect_end) {
            result.push_back({intersect_start, intersect_end});
        }
        
        // Advance the pointer for the interval that ends earlier
        // This ensures we always consider the "earliest ending" interval to move forward
        if (intervals1[i].end < intervals2[j].end) {
            i++;
        } else {
            j++;
        }
    }
    return result;
}

// Function to shift all intervals in a list by a given delta
std::vector<Interval> shift_intervals(const std::vector<Interval>& intervals, long long delta) {
    std::vector<Interval> shifted;
    for (const auto& interval : intervals) {
        shifted.push_back({interval.start + delta, interval.end + delta});
    }
    return shifted;
}

int main() {
    // Optimize C++ standard streams for competitive programming
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    long long initial_x;
    std::cin >> initial_x;

    // Structure to store curse information
    struct Curse {
        long long tl, tr, l, r;
    };
    std::vector<Curse> curses(n);

    // Collect all unique time points that define elementary time intervals
    std::set<long long> time_points_set;
    time_points_set.insert(0); // The simulation starts at time 0
    long long max_coord_val = 0; // To determine the upper bound for coordinate ranges
    long long max_time_val = 0; // To determine the upper bound for time ranges

    for (int i = 0; i < n; ++i) {
        std::cin >> curses[i].tl >> curses[i].tr >> curses[i].l >> curses[i].r;
        time_points_set.insert(curses[i].tl);
        time_points_set.insert(curses[i].tr + 1); // End of curse interval + 1
        max_coord_val = std::max(max_coord_val, curses[i].r);
        max_time_val = std::max(max_time_val, curses[i].tr);
    }

    // Add a time point beyond max_time_val to ensure all time intervals are properly handled
    time_points_set.insert(max_time_val + 2); 
    // Determine a sufficiently large maximum coordinate value for interval bounds
    max_coord_val = std::max(max_coord_val, initial_x + max_time_val) + 5; // Add a buffer

    // Convert set of unique time points to a sorted vector
    std::vector<long long> E(time_points_set.begin(), time_points_set.end());
    int K = E.size(); // Number of elementary time points

    // S[j]: Safe intervals at time E[j] (or rather, for t in [E[j], E[j+1]))
    // F[j]: Future safe ranges if person is at y at time E[j]
    std::vector<std::vector<Interval>> S(K);
    std::vector<std::vector<Interval>> F(K + 1);

    // Step 1: Compute S[j] for each elementary time interval [E[j], E[j+1])
    // The set of active curses is constant for t in [E[j], E[j+1]).
    // A curse 'i' is considered active if E[j] falls within its [tl_i, tr_i] time range.
    for (int j = 0; j < K; ++j) {
        std::vector<Interval> current_cursed_intervals;
        for (const auto& curse : curses) {
            // Check if curse is active at time E[j]
            if (E[j] >= curse.tl && E[j] <= curse.tr) {
                current_cursed_intervals.push_back({curse.l, curse.r});
            }
        }
        // Merge overlapping cursed intervals
        current_cursed_intervals = merge_intervals(current_cursed_intervals);
        // Compute the complement (safe intervals) within the full coordinate range
        S[j] = complement_intervals(current_cursed_intervals, 0, max_coord_val);
    }

    // Step 2: Compute F[j] (future safe ranges) using dynamic programming from K down to 0
    // F[K] represents the state after the last event point, which is considered fully safe.
    F[K].push_back({0, max_coord_val}); 

    for (int j = K - 1; j >= 0; --j) {
        long long delta_t = E[j+1] - E[j]; // Time elapsed between E[j] and E[j+1]
        
        // Shift F[j+1] back by delta_t to align coordinates with E[j]'s time frame
        std::vector<Interval> shifted_F_next = shift_intervals(F[j+1], -delta_t);
        
        // Intersect with S[j] (safe intervals at E[j]) to get F[j]
        F[j] = intersect_intervals(S[j], shifted_F_next);
    }

    // Step 3: Compute min_safe_t (the earliest time the person enters a cursed region on their natural path)
    long long min_safe_t = INF_LL; // Initialize with a very large value
    for (const auto& curse : curses) {
        // The person is at initial_x + t. A curse is active if t is in [tl_i, tr_i] and initial_x + t is in [l_i, r_i].
        // This implies: l_i <= initial_x + t <= r_i  =>  l_i - initial_x <= t <= r_i - initial_x
        long long t_start_danger_coord = curse.l - initial_x;
        long long t_end_danger_coord = curse.r - initial_x;

        // The actual time interval when the person is in danger from this curse
        long long t_start_danger = std::max(curse.tl, t_start_danger_coord);
        long long t_end_danger = std::min(curse.tr, t_end_danger_coord);
        
        // If there's an actual overlap in time
        if (t_start_danger <= t_end_danger) {
            min_safe_t = std::min(min_safe_t, t_start_danger);
        }
    }
    // If min_safe_t remains INF_LL, it means the person is never naturally in danger.
    // Set it to a value larger than any possible E[j] to allow all E[j] as t_stop candidates.
    if (min_safe_t == INF_LL) {
        min_safe_t = max_time_val + 2; 
    }

    // Step 4: Iterate through all possible t_stop values (E[j]) and find the minimum cost
    double min_total_cost = std::numeric_limits<double>::max();

    for (int j = 0; j < K; ++j) {
        // Check if the natural path is safe up to E[j].
        // If E[j] is greater than or equal to min_safe_t, it means the person would have already
        // entered a cursed region before or at E[j]. So, E[j] is not a valid t_stop.
        // The only exception is if min_safe_t is 0, meaning danger starts immediately after t=0.
        // In that case, t_stop must be 0.
        if (E[j] > min_safe_t) {
            continue; 
        }

        long long current_person_coord = initial_x + E[j];
        
        // Find the maximal safe interval [A, B] at time E[j] that contains current_person_coord.
        // This is crucial for the "continuous movement" constraint.
        std::vector<Interval> current_safe_intervals_at_Ej;
        bool current_coord_safe = false;
        for (const auto& interval : S[j]) {
            if (current_person_coord >= interval.start && current_person_coord <= interval.end) {
                current_safe_intervals_at_Ej.push_back(interval);
                current_coord_safe = true;
                break; // Found the interval containing current_person_coord
            }
        }

        // If the person's current coordinate is in a cursed region at E[j], this E[j] is not a valid t_stop.
        if (!current_coord_safe) {
            continue;
        }

        // ValidYRange: The intersection of the safe interval containing current_person_coord
        // and the future safe range F[j]. This is where 'y' can be chosen.
        std::vector<Interval> valid_y_range = intersect_intervals(current_safe_intervals_at_Ej, F[j]);

        // If there's no valid 'y' coordinate for this t_stop, continue to the next E[j].
        if (valid_y_range.empty()) {
            continue;
        }

        // Find 'y' in valid_y_range that minimizes |current_person_coord - y|.
        // Since current_person_coord is an integer and interval boundaries are integers,
        // the optimal 'y' will also be an integer.
        double current_min_cost_for_Ej = std::numeric_limits<double>::max();
        for (const auto& interval : valid_y_range) {
            double y_candidate;
            if (current_person_coord < interval.start) {
                // If current_person_coord is to the left of the interval, closest point is interval.start
                y_candidate = interval.start;
            } else if (current_person_coord > interval.end) {
                // If current_person_coord is to the right of the interval, closest point is interval.end
                y_candidate = interval.end;
            } else {
                // If current_person_coord is within the interval, the closest point is itself (cost 0)
                y_candidate = current_person_coord; 
            }
            current_min_cost_for_Ej = std::min(current_min_cost_for_Ej, std::abs(static_cast<double>(current_person_coord) - y_candidate));
        }
        min_total_cost = std::min(min_total_cost, current_min_cost_for_Ej);
    }

    // Output the result, rounded up to the nearest integer.
    // std::ceil handles rounding up correctly for positive numbers.
    std::cout << static_cast<long long>(std::ceil(min_total_cost)) << std::endl;

    return 0;
}
