#include <vector>

using namespace std;

vector<int> calculateScore(int callingTeam, int team1Tricks, int team2Tricks, bool wentAlone) {
    vector<int> score = {0, 0};
    int trumpTeamTricks = (callingTeam == 1) ? team1Tricks : team2Tricks;
    int otherTeamTricks = (callingTeam == 1) ? team2Tricks : team1Tricks;

    // Determine points based on the rules
    if (trumpTeamTricks <= 2) {
        // Other team gets 2 points
        score[callingTeam % 2] += 2; // If callingTeam is 1, other is 2 (1%2=1, 2%2=0)
    } else if (trumpTeamTricks == 3 || trumpTeamTricks == 4) {
        // Trump team gets 1 point
        score[callingTeam - 1] += 1;
    } else if (trumpTeamTricks == 5) {
        if (wentAlone) {
            // Trump team gets 4 points
            score[callingTeam - 1] += 4;
        } else {
            // Trump team gets 2 points
            score[callingTeam - 1] += 2;
        }
    }

    return score;
}