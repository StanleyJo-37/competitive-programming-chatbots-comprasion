#include <iostream>
#include <vector>

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This is a common competitive programming optimization.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long n; // Total number of items
    int m;       // Number of special items to discard
    long long k; // Number of positions per page

    // Read n, m, k from input
    std::cin >> n >> m >> k;

    // Create a vector to store the indices of special items.
    // Use long long for item indices as they can be up to n (10^18).
    std::vector<long long> p(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> p[i];
    }

    long long operations = 0;       // Counter for the total number of operations
    long long discarded_count = 0;  // Total number of items discarded so far.
                                    // This value is crucial because it affects the current
                                    // positions of remaining items. If 'x' items before
                                    // a certain item have been discarded, that item's
                                    // effective position shifts 'x' positions earlier.
    int current_special_item_idx = 0; // Pointer to the first special item not yet discarded.
                                      // This acts as the 'i' in the two-pointer approach.

    // Loop until all 'm' special items have been discarded.
    while (current_special_item_idx < m) {
        operations++; // Each iteration of this outer loop represents one operation.

        // Calculate the target page for the current operation.
        // This is determined by the first special item that needs to be discarded.
        // Its current position is p[current_special_item_idx] minus the items
        // already discarded (discarded_count).
        // The page number (0-indexed) is (current_position - 1) / k.
        long long current_pos_of_first_special_item = p[current_special_item_idx] - discarded_count;
        long long target_page_idx = (current_pos_of_first_special_item - 1) / k;

        // Now, discard all special items that are on this target page.
        // We use a 'j' pointer (items_in_this_op_idx) to iterate through
        // the special items starting from current_special_item_idx.
        int items_in_this_op_idx = current_special_item_idx;
        long long items_discarded_in_this_op = 0; // Count of items discarded in the current operation.

        // Iterate through the remaining special items.
        while (items_in_this_op_idx < m) {
            // Calculate the current position of the item p[items_in_this_op_idx].
            long long current_pos_of_pj = p[items_in_this_op_idx] - discarded_count;
            // Determine the page this item is currently on.
            long long page_of_pj = (current_pos_of_pj - 1) / k;

            // If this item is on the target page, it gets discarded in this operation.
            if (page_of_pj == target_page_idx) {
                items_discarded_in_this_op++;
                items_in_this_op_idx++; // Move to the next special item.
            } else {
                // If the item is on a different page (must be a later page,
                // since p is sorted and we process items in order),
                // then we stop discarding items for this operation.
                break;
            }
        }

        // Update the total count of discarded items.
        discarded_count += items_discarded_in_this_op;
        // Advance the main pointer to the first special item that was NOT discarded
        // in this operation. This ensures we continue from where we left off.
        current_special_item_idx = items_in_this_op_idx;
    }

    // Print the total number of operations.
    std::cout << operations << std::endl;

    return 0;
}
