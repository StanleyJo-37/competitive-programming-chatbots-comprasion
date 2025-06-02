#include <iostream> // For standard input/output operations (not strictly needed for the function, but common in competitive programming)
#include <vector>   // For std::vector
#include <string>   // For std::string
#include <map>      // For std::map (used for input and output)
#include <algorithm> // For std::sort
#include <variant>   // For std::variant (to handle mixed types in input map values, requires C++17)

// Helper function to count the number of 'X' characters in a given string.
// 'X' represents an unsuccessful attempt.
int countXs(const std::string& s) {
    int count = 0;
    for (char c : s) {
        if (c == 'X') {
            count++;
        }
    }
    return count;
}

// Helper function to check if a result string indicates a successful attempt.
// A successful attempt is marked by an 'O' character.
bool hasO(const std::string& s) {
    return s.find('O') != std::string::npos;
}

// Structure to hold processed competitor data.
// This simplifies sorting and tie-breaking logic by pre-calculating necessary metrics.
struct Competitor {
    std::string name;
    int best_height_idx; // The highest index (representing height) at which the vaulter successfully cleared the bar.
                         // Initialized to -1 if no height was cleared.
    int total_attempts;  // The total number of unsuccessful attempts ('X's) across all heights.
    std::vector<std::string> original_results; // Stores the vaulter's raw results for tie-breaking rule 1.
};

// Custom comparison function for sorting Competitor objects.
// This function defines the ranking rules: 'a' is "better" than 'b' if it should come before 'b' in the sorted list.
bool compareCompetitors(const Competitor& a, const Competitor& b) {
    // Rule 1: Primary Ranking - Greatest Height Cleared Successfully.
    // Vaulters who clear a higher bar (represented by a higher index) are ranked higher.
    if (a.best_height_idx != b.best_height_idx) {
        return a.best_height_idx > b.best_height_idx; // 'a' is better if its best cleared height is higher than 'b's.
    }

    // If best_height_idx is the same for both competitors (a tie on the primary rule),
    // apply the tie-breaking rules.
    // This block is only relevant if competitors actually cleared at least one height (best_height_idx >= 0).
    if (a.best_height_idx >= 0) {
        // Rule 2: Tie-break 1 - Fewest Unsuccessful Attempts at the Greatest *Common* Cleared Height.
        // We need to find the highest height (largest index) that *both* vaulters successfully cleared.
        int common_cleared_height_idx = -1;
        for (int i = a.best_height_idx; i >= 0; --i) {
            // Check if both vaulters successfully cleared the bar at this height 'i'.
            if (hasO(a.original_results[i]) && hasO(b.original_results[i])) {
                common_cleared_height_idx = i;
                break; // Found the greatest common cleared height, no need to search further down.
            }
        }

        // If a common cleared height was found, compare their 'X' counts at that specific height.
        if (common_cleared_height_idx != -1) {
            int xs_a_at_common = countXs(a.original_results[common_cleared_height_idx]);
            int xs_b_at_common = countXs(b.original_results[common_cleared_height_idx]);
            if (xs_a_at_common != xs_b_at_common) {
                return xs_a_at_common < xs_b_at_common; // 'a' is better if it has fewer 'X's at this common height.
            }
        }
    }
    // If best_height_idx is -1 for both (meaning neither cleared any height),
    // or if 'X' counts at the common cleared height are equal,
    // or if no common cleared height was found (e.g., one cleared height 5, other cleared height 4, but both have best_height_idx 5 because of some complex scenario, though this shouldn't happen if best_height_idx is truly the highest cleared height for both),
    // proceed to the next tie-break rule.

    // Rule 3: Tie-break 2 - Fewest Total Unsuccessful Attempts.
    // If still tied after Rule 2, compare the total number of unsuccessful attempts across all heights.
    if (a.total_attempts != b.total_attempts) {
        return a.total_attempts < b.total_attempts; // 'a' is better if it has fewer total 'X's.
    }

    // Rule 4: Still tied after all rules.
    // If all criteria are equal, the competitors are considered equivalent for sorting purposes.
    // Returning false indicates that 'a' is not strictly "less" (better) than 'b'.
    return false;
}

// Helper function to determine if two competitors are truly tied based on all ranking rules.
// This is true if neither competitor is strictly better than the other according to `compareCompetitors`.
bool areTrulyTied(const Competitor& a, const Competitor& b) {
    return !compareCompetitors(a, b) && !compareCompetitors(b, a);
}

// Main function to solve the pole vault competition ranking problem.
// It takes a vector of competitor data and returns a map of place finishes.
std::map<std::string, std::string> score_pole_vault(
    const std::vector<std::map<std::string, std::variant<std::string, std::vector<std::string>>>>& competitors_data) {

    std::vector<Competitor> processed_competitors;
    processed_competitors.reserve(competitors_data.size()); // Optimize by pre-allocating memory.

    // Step 1: Pre-process the raw input data into the `Competitor` struct.
    // This involves extracting name, results, and calculating `best_height_idx` and `total_attempts`.
    for (const auto& competitor_map : competitors_data) {
        Competitor comp;
        // Extract competitor's name from the map.
        comp.name = std::get<std::string>(competitor_map.at("name"));

        // Extract the vector of result strings and store it.
        comp.original_results = std::get<std::vector<std::string>>(competitor_map.at("results"));

        // Initialize metrics.
        comp.best_height_idx = -1; // Assume no height cleared initially.
        comp.total_attempts = 0;

        // Iterate through the results from the highest height (rightmost index) downwards.
        // This helps in finding `best_height_idx` efficiently and calculating `total_attempts`.
        for (int i = comp.original_results.size() - 1; i >= 0; --i) {
            const std::string& result_str = comp.original_results[i];

            // Accumulate total unsuccessful attempts ('X's).
            comp.total_attempts += countXs(result_str);

            // If this is the first 'O' found while iterating backwards, it's the best cleared height.
            if (comp.best_height_idx == -1 && hasO(result_str)) {
                comp.best_height_idx = i;
            }
        }
        processed_competitors.push_back(comp); // Add the processed competitor to the list.
    }

    // Step 2: Sort the processed competitors using the custom comparison function.
    // This arranges them from 1st place to last place according to the rules.
    std::sort(processed_competitors.begin(), processed_competitors.end(), compareCompetitors);

    std::map<std::string, std::string> result_map; // The final map to store the top 3 finishes.
    if (processed_competitors.empty()) {
        return result_map; // If no competitors, return an empty map.
    }

    // Step 3: Determine and format the top 3 place finishes based on the sorted list.
    int current_competitor_idx = 0; // Index in the sorted `processed_competitors` vector.
    int current_place_rank = 1;     // The actual rank being awarded (1 for 1st, 2 for 2nd, 3 for 3rd).

    // Loop to determine 1st, 2nd, and 3rd places.
    // It stops if all competitors have been processed or if 3rd place has been determined.
    while (current_competitor_idx < processed_competitors.size() && current_place_rank <= 3) {
        std::vector<std::string> tied_names;
        tied_names.push_back(processed_competitors[current_competitor_idx].name);

        // Collect all competitors who are truly tied for the current place.
        int next_idx = current_competitor_idx + 1;
        while (next_idx < processed_competitors.size() &&
               areTrulyTied(processed_competitors[current_competitor_idx], processed_competitors[next_idx])) {
            tied_names.push_back(processed_competitors[next_idx].name);
            next_idx++;
        }

        // Sort the names of tied competitors alphabetically as required.
        std::sort(tied_names.begin(), tied_names.end());

        // Build the string for the current place (e.g., "Jan" or "Madi, Emily (tie)").
        std::string place_string = tied_names[0];
        for (size_t i = 1; i < tied_names.size(); ++i) {
            place_string += ", " + tied_names[i];
        }

        // Add the appropriate tie notation if there are multiple names.
        if (tied_names.size() > 1) {
            if (current_place_rank == 1) {
                place_string += " (jump-off)"; // Special notation for 1st place ties.
            } else {
                place_string += " (tie)"; // Notation for 2nd or 3rd place ties.
            }
        }

        // Add the formatted place string to the result map.
        if (current_place_rank == 1) {
            result_map["1st"] = place_string;
        } else if (current_place_rank == 2) {
            result_map["2nd"] = place_string;
        } else if (current_place_rank == 3) {
            result_map["3rd"] = place_string;
        }

        // Move to the next distinct rank in the sorted list.
        // The `current_place_rank` is incremented by the number of tied competitors.
        // This correctly handles the "bumping" of lower places (e.g., if 1st place is tied by 2 people,
        // the next awarded place is 3rd, skipping 2nd).
        current_competitor_idx = next_idx;
        current_place_rank += tied_names.size();
    }

    return result_map; // Return the final map of place finishes.
}