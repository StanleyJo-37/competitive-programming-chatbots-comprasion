#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to simulate the Tetris game and count cleared lines
int tetris(const vector<string>& gamelog) {
    // Field dimensions
    const int WIDTH = 9;
    const int HEIGHT = 30;

    // Initialize the field: 0 = empty, 1 = filled
    vector<vector<int>> field;

    // Block shapes, each as a vector of (row, col) offsets from the top-left of the block
    // All blocks are 1 row high, but different widths
    // Block 1: [1]
    // Block 2: [1,1]
    // Block 3: [1,1,1]
    // Block 4: [1,1,1,1]
    vector<vector<pair<int, int>>> blocks = {
        {{0,0}},                 // Block 1
        {{0,0},{0,1}},           // Block 2
        {{0,0},{0,1},{0,2}},     // Block 3
        {{0,0},{0,1},{0,2},{0,3}}// Block 4
    };

    // Center index is 4 (0-based, so L0/R0 is index 4)
    const int CENTER = 4;

    int cleared_lines = 0;

    for (const string& cmd : gamelog) {
        // Parse block type (1-based in input, 0-based in our array)
        int block_type = cmd[0] - '1';
        char dir = cmd[1];
        int offset = cmd[2] - '0';

        // Calculate starting column
        int start_col;
        if (dir == 'L') {
            start_col = CENTER - offset;
        } else { // dir == 'R'
            start_col = CENTER + offset;
        }

        // Get block shape
        const vector<pair<int, int>>& shape = blocks[block_type];

        // Find the lowest row where the block can be placed
        int place_row = 0;
        while (true) {
            bool collision = false;
            // Check for collision at the next row
            for (const auto& cell : shape) {
                int r = place_row + cell.first;
                int c = start_col + cell.second;
                // If out of bounds horizontally, invalid move (should not happen with valid input)
                if (c < 0 || c >= WIDTH) {
                    collision = true;
                    break;
                }
                // If row exists and cell is filled, collision
                if (r < (int)field.size() && field[r][c] == 1) {
                    collision = true;
                    break;
                }
            }
            if (collision) break;
            place_row++;
        }
        place_row--; // The last non-colliding row

        // If place_row < 0, the block cannot be placed (should not happen with valid input)
        if (place_row < 0) return cleared_lines;

        // Ensure the field has enough rows
        int needed_rows = place_row + 1;
        while ((int)field.size() < needed_rows) {
            field.push_back(vector<int>(WIDTH, 0));
        }

        // Place the block
        for (const auto& cell : shape) {
            int r = place_row + cell.first;
            int c = start_col + cell.second;
            field[r][c] = 1;
        }

        // Check for full lines and clear them
        for (int row = (int)field.size() - 1; row >= 0; --row) {
            bool full = true;
            for (int col = 0; col < WIDTH; ++col) {
                if (field[row][col] == 0) {
                    full = false;
                    break;
                }
            }
            if (full) {
                // Remove the full line
                field.erase(field.begin() + row);
                // Add an empty row at the top
                field.insert(field.begin(), vector<int>(WIDTH, 0));
                cleared_lines++;
                // After erasing, stay at the same row index
                row++;
            }
        }

        // If field height exceeds HEIGHT, game ends
        if ((int)field.size() > HEIGHT) {
            return cleared_lines;
        }
    }
    return cleared_lines;
}

// For testing
/*
int main() {
    vector<string> gamelog1 = {"1R4", "2L3", "3L2", "4L1", "1L0", "2R1", "3R2", "4R3", "1L4"};
    cout << tetris(gamelog1) << endl; // Should output 1

    vector<string> gamelog2 = {"1L2", "4R2", "3L3", "3L1", "1L4", "1R4"};
    cout << tetris(gamelog2) << endl; // Should output 0

    vector<string> gamelog3 = {"4L2", "3R4", "4L3", "3L4", "4R0", "1L2"};
    cout << tetris(gamelog3) << endl; // Example from the prompt
}
*/