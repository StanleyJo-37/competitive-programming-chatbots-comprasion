#include <vector> // Required for std::vector

// Function to calculate the new score after a Euchre hand.
// current_score: A vector of two integers {team1_score, team2_score} representing the current scores.
// calling_team: An integer (1 or 2) indicating which team called trump.
// tricks_team1: An integer representing the number of tricks won by team 1.
// tricks_team2: An integer representing the number of tricks won by team 2.
// alone: A boolean indicating if anyone went alone.
// Returns: A vector of two integers {new_team1_score, new_team2_score} representing the updated scores.
std::vector<int> calculateNewScore(std::vector<int> current_score, int calling_team, int tricks_team1, int tricks_team2, bool alone) {
    // Initialize points awarded for the current hand to zero.
    int points_for_calling_team = 0;
    int points_for_other_team = 0;

    // Determine the number of tricks won by the team that called trump
    // and the number of tricks won by the opposing team.
    int calling_team_tricks;
    int other_team_tricks;

    if (calling_team == 1) {
        // If Team 1 called trump, their tricks are tricks_team1, and Team 2's are other_team_tricks.
        calling_team_tricks = tricks_team1;
        other_team_tricks = tricks_team2;
    } else { // calling_team == 2
        // If Team 2 called trump, their tricks are tricks_team2, and Team 1's are other_team_tricks.
        calling_team_tricks = tricks_team2;
        other_team_tricks = tricks_team1;
    }

    // Apply the scoring rules based on the number of tricks won by the calling team.
    if (calling_team_tricks <= 2) {
        // Rule: If the team that called trump wins 2 or fewer tricks, they are "euchred".
        // The other team (non-calling team) wins 2 points.
        points_for_other_team = 2;
    } else if (calling_team_tricks == 3 || calling_team_tricks == 4) {
        // Rule: If the team that called trump wins 3 or 4 tricks, they win 1 point.
        points_for_calling_team = 1;
    } else if (calling_team_tricks == 5) {
        // Rule: If the team that called trump wins all 5 tricks.
        if (alone) {
            // Rule: If they went alone and won all 5 tricks, they win 4 points.
            points_for_calling_team = 4;
        } else {
            // Rule: If they did not go alone and won all 5 tricks, they win 2 points.
            points_for_calling_team = 2;
        }
    }

    // Create a mutable copy of the current scores to update.
    std::vector<int> new_score = current_score;

    // Add the calculated points to the respective teams' scores.
    if (calling_team == 1) {
        // If Team 1 called trump, add points_for_calling_team to Team 1's score
        // and points_for_other_team to Team 2's score.
        new_score[0] += points_for_calling_team;
        new_score[1] += points_for_other_team;
    } else { // calling_team == 2
        // If Team 2 called trump, add points_for_calling_team to Team 2's score
        // and points_for_other_team to Team 1's score.
        new_score[0] += points_for_other_team;
        new_score[1] += points_for_calling_team;
    }

    // Return the updated scores for both teams.
    return new_score;
}