#include <string>
#include <vector>
#include <utility> // For std::pair
#include <map>     // For std::map

// Constants for game field dimensions
const int FIELD_WIDTH = 9;
const int FIELD_HEIGHT = 30;

// Function to simulate Tetris gameplay and count cleared lines
int tetris(const std::vector<std::string>& gamelog) {
    // Initialize the game field with all empty cells (false).
    // The field is a 2D vector where field[y][x] represents the cell at row 'y' and column 'x'.
    // Row 0 is the bottom of the field, row FIELD_HEIGHT-1 is the top.
    std::vector<std::vector<bool>> field(FIELD_HEIGHT, std::vector<bool>(FIELD_WIDTH, false));
    int cleared_lines_count = 0; // Counter for the total number of cleared lines.

    // Define block shapes. Each block is represented by a vector of (dx, dy) pairs
    // relative to its bottom-most cell (anchor point).
    // Block types are 1-indexed in the problem description (1 to 4).
    // Block 1: 1x1 square
    // Block 2: 1x2 vertical stack
    // Block 3: 1x3 vertical stack
    // Block 4: 1x4 vertical stack
    std::map<int, std::vector<std::pair<int, int>>> block_shapes;
    block_shapes[1] = {{0, 0}};
    block_shapes[2] = {{0, 0}, {0, 1}};
    block_shapes[3] = {{0, 0}, {0, 1}, {0, 2}};
    block_shapes[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};

    // Define block heights, used for calculating the initial spawn row.
    std::map<int, int> block_heights;
    block_heights[1] = 1;
    block_heights[2] = 2;
    block_heights[3] = 3;
    block_heights[4] = 4;

    // Process each command in the provided game log.
    for (const std::string& command : gamelog) {
        // Parse the command string:
        // The first character is the block type (e.g., '1' for block 1).
        // The second character is the direction ('L' for left, 'R' for right).
        // The third character is the offset (e.g., '0' for no offset, '4' for max offset).
        int block_type = command[0] - '0'; // Convert char to int
        char direction = command[1];
        int offset = command[2] - '0';     // Convert char to int

        // Retrieve the shape and height for the current block type.
        const auto& current_block_shape = block_shapes[block_type];
        int current_block_height = block_heights[block_type];

        // Calculate the initial horizontal (x) position (spawn column) for the block's anchor.
        // The field width is 9 units (columns 0-8). The center column is 4.
        int spawn_col = 4;
        if (direction == 'L') {
            spawn_col -= offset;
        } else { // 'R'
            spawn_col += offset;
        }

        // Calculate the initial vertical (y) position (spawn row) for the block's anchor.
        // Blocks spawn such that their top-most cell is at row FIELD_HEIGHT - 1 (the highest row).
        // So, the anchor (bottom-most cell) will be at FIELD_HEIGHT - current_block_height.
        int current_x = spawn_col;
        int current_y = FIELD_HEIGHT - current_block_height;

        // --- Game Over Check at Spawn ---
        // Before the block starts falling, check if its initial spawn position
        // overlaps with any already occupied cells on the field.
        // If it does, the game ends immediately, as per Tetris rules for "topping out".
        for (const auto& cell_offset : current_block_shape) {
            int cell_x = current_x + cell_offset.first;
            int cell_y = current_y + cell_offset.second;

            // Check if the calculated spawn cell is within the field bounds (horizontally)
            // and if it's already occupied. Vertically, cell_y will always be >= 0 and < FIELD_HEIGHT
            // due to the spawn_y calculation (FIELD_HEIGHT - current_block_height) and cell_offset.second.
            if (cell_x >= 0 && cell_x < FIELD_WIDTH && field[cell_y][cell_x]) {
                return cleared_lines_count; // Game over: return the current cleared lines count.
            }
        }

        // --- Block Falling Simulation ---
        // Simulate the block falling one row at a time until it lands.
        while (true) {
            bool can_move_down = true;
            // Check if the block can move one step down without colliding.
            for (const auto& cell_offset : current_block_shape) {
                int next_cell_x = current_x + cell_offset.first;
                int next_cell_y = current_y + cell_offset.second - 1; // Check the cell one row below

                // Collision conditions:
                // 1. The block's next position would be below the bottom of the field (next_cell_y < 0).
                // 2. The block's next position would overlap with an already occupied cell on the field.
                if (next_cell_y < 0 || field[next_cell_y][next_cell_x]) {
                    can_move_down = false;
                    break; // Cannot move down, so the block will land.
                }
            }

            if (can_move_down) {
                current_y--; // Move the block down by one row.
            } else {
                // The block has landed. Place its cells permanently on the game field.
                for (const auto& cell_offset : current_block_shape) {
                    int cell_x = current_x + cell_offset.first;
                    int cell_y = current_y + cell_offset.second;
                    field[cell_y][cell_x] = true; // Mark the cell as occupied.
                }
                break; // Exit the falling loop as the block has landed.
            }
        }

        // --- Line Clearing ---
        // After a block lands, check for any full horizontal lines from bottom to top.
        for (int r = 0; r < FIELD_HEIGHT; ++r) {
            bool is_full_line = true;
            // Check if the current row 'r' is completely filled.
            for (int c = 0; c < FIELD_WIDTH; ++c) {
                if (!field[r][c]) {
                    is_full_line = false; // Found an empty cell, so this line is not full.
                    break;
                }
            }

            if (is_full_line) {
                cleared_lines_count++; // Increment the count of cleared lines.

                // Shift all rows above the cleared line down by one row.
                // Start from the cleared row 'r' and move up to FIELD_HEIGHT - 2.
                // The row at y_shift will take the contents of the row at y_shift + 1.
                for (int y_shift = r; y_shift < FIELD_HEIGHT - 1; ++y_shift) {
                    field[y_shift] = field[y_shift + 1];
                }
                // The top-most row (FIELD_HEIGHT - 1) is now empty after the shift.
                // Clear it explicitly to ensure it's all 'false'.
                field[FIELD_HEIGHT - 1].assign(FIELD_WIDTH, false);

                // Decrement 'r' by 1. This is crucial because after shifting,
                // the current row 'r' now contains what was previously row 'r+1'.
                // We need to re-check this new content of row 'r' in the next iteration
                // to see if it also forms a full line (e.g., in case of multiple line clears).
                r--;
            }
        }
    }

    // All commands from the game log have been processed without a game over.
    // Return the total number of lines cleared during the game.
    return cleared_lines_count;
}
