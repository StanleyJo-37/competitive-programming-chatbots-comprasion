#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to simulate the Tetris game and return the number of cleared lines
int tetris(vector<string> gamelog) {
    // The game field is 9 units wide (indices -4 to 4) and 30 units high.
    // We represent the field as a 2D vector where each row is a line (height) and columns are positions (-4 to 4).
    // To simplify, we'll map positions -4 to 4 to indices 0 to 8 (L4 is 0, R4 is 8).
    vector<vector<bool>> field(30, vector<bool>(9, false));
    int clearedLines = 0;

    for (const string& cmd : gamelog) {
        int blockType = cmd[0] - '0';
        char direction = cmd[1];
        int offset = cmd[2] - '0';

        // Calculate the leftmost position of the block based on direction and offset.
        int leftPos;
        if (direction == 'L') {
            leftPos = 4 - offset; // 4 is center (R0/L0), L4 is 0 (leftmost), L0 is 4.
        } else { // 'R'
            leftPos = 4 + offset; // R4 is 8 (rightmost), R0 is 4.
        }

        // Determine the shape of the block (width and occupied positions).
        int blockWidth = blockType;
        vector<bool> blockShape(9, false);
        for (int i = 0; i < blockWidth; ++i) {
            if (leftPos + i >= 0 && leftPos + i < 9) {
                blockShape[leftPos + i] = true;
            }
        }

        // Find the lowest row where the block can be placed without collision.
        int lowestRow = -1;
        for (int row = 0; row < 30; ++row) {
            bool canPlace = true;
            for (int col = 0; col < 9; ++col) {
                if (blockShape[col] && field[row][col]) {
                    canPlace = false;
                    break;
                }
            }
            if (canPlace) {
                lowestRow = row;
            } else {
                break;
            }
        }

        // If lowestRow is -1, the block cannot be placed (game over, but according to the problem, we stop if height is exceeded).
        if (lowestRow == -1) {
            break;
        }

        // Place the block in the field.
        for (int col = 0; col < 9; ++col) {
            if (blockShape[col]) {
                field[lowestRow][col] = true;
            }
        }

        // Check for completed lines (all cells in a row are true).
        for (int row = 0; row < 30; ) {
            bool lineComplete = true;
            for (int col = 0; col < 9; ++col) {
                if (!field[row][col]) {
                    lineComplete = false;
                    break;
                }
            }
            if (lineComplete) {
                // Remove the line and shift all above lines down.
                field.erase(field.begin() + row);
                field.insert(field.begin(), vector<bool>(9, false));
                clearedLines++;
            } else {
                row++;
            }
        }

        // Check if the highest block reaches the top (row 29 is the bottom, 0 is the top).
        bool exceededHeight = false;
        for (int row = 0; row < 30; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (field[row][col]) {
                    exceededHeight = true;
                    break;
                }
            }
            if (exceededHeight) {
                break;
            }
        }
        if (exceededHeight && field[0][0]) { // If any block is in the top row.
            break;
        }
    }

    return clearedLines;
}