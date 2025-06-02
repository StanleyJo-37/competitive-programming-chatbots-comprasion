#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Function to check if it's possible to achieve max candy <= mid with M balloons
bool isPossible(const vector<ll>& A, const vector<ll>& B, ll mid, ll M) {
    ll totalBalloons = 0;
    for (int i = 0; i < A.size(); ++i) {
        if (B[i] == 0) {
            // If B[i] is 0, no candies are needed, so we can give all A[i] balloons
            totalBalloons += A[i];
            continue;
        }
        // Calculate the minimal balloons needed to keep C_i <= mid
        ll maxPossibleCandies = mid;
        ll minBalloonsNeeded = max(0LL, A[i] - (maxPossibleCandies / B[i]));
        totalBalloons += minBalloonsNeeded;
        if (totalBalloons > M) {
            return false;
        }
    }
    return totalBalloons <= M;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll M;
    cin >> N >> M;
    vector<ll> A(N), B(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> B[i];
    }

    // Binary search boundaries
    ll left = 0;
    ll right = 0;
    for (int i = 0; i < N; ++i) {
        if (B[i] != 0) {
            right = max(right, A[i] * B[i]);
        }
    }

    ll answer = right;
    while (left <= right) {
        ll mid = left + (right - left) / 2;
        if (isPossible(A, B, mid, M)) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << answer << endl;
    return 0;
}