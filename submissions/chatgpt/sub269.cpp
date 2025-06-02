#include <iostream>
#include <vector>
using namespace std;

// Function to calculate the new score after a hand in euchre
vector<int> calculateScore(
    vector<int> currentScore, // current scores: {team1, team2}
    int callingTeam,          // team that called trump: 1 or 2
    int tricksTeam1,          // number of tricks won by team 1
    int tricksTeam2,          // number of tricks won by team 2
    bool wentAlone            // true if calling team went alone, false otherwise
) {
    // Determine tricks won by the calling team and the other team
    int callingTeamTricks = (callingTeam == 1) ? tricksTeam1 : tricksTeam2;
    int otherTeam = (callingTeam == 1) ? 2 : 1;

    // Case 1: Calling team wins 2 or fewer tricks, other team gets 2 points
    if (callingTeamTricks <= 2) {
        currentScore[otherTeam - 1] += 2;
    }
    // Case 2: Calling team wins 3 or 4 tricks, calling team gets 1 point
    else if (callingTeamTricks == 3 || callingTeamTricks == 4) {
        currentScore[callingTeam - 1] += 1;
    }
    // Case 3: Calling team wins all 5 tricks
    else if (callingTeamTricks == 5) {
        // If went alone, calling team gets 4 points
        if (wentAlone) {
            currentScore[callingTeam - 1] += 4;
        }
        // If not alone, calling team gets 2 points
        else {
            currentScore[callingTeam - 1] += 2;
        }
    }
    // Return the updated scores
    return currentScore;
}

int main() {
    // Read input: current scores, calling team, tricks won, and went alone flag
    vector<int> currentScore(2);
    int callingTeam, tricksTeam1, tricksTeam2;
    bool wentAlone;
    cin >> currentScore[0] >> currentScore[1];
    cin >> callingTeam >> tricksTeam1 >> tricksTeam2 >> wentAlone;

    // Calculate new score
    vector<int> newScore = calculateScore(currentScore, callingTeam, tricksTeam1, tricksTeam2, wentAlone);

    // Output the new scores
    cout << newScore[0] << " " << newScore[1] << endl;
    return 0;
}