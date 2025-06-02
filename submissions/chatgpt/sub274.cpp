#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N);
        int cnt_even = 0, cnt_odd = 0;
        // Count number of even and odd elements in A
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
            if (A[i] % 2 == 0) cnt_even++;
            else cnt_odd++;
        }
        int cnt_pos_even = N / 2; // Number of even positions (1-based): positions 2,4,6,...
        int cnt_pos_odd = N - cnt_pos_even; // Number of odd positions (1-based): positions 1,3,5,...

        // To maximize sum, assign as many as possible:
        // - odd A[i] to even positions (since (odd+even)%2==1)
        // - even A[i] to odd positions (since (even+odd)%2==1)
        int use_odd_in_even_pos = min(cnt_odd, cnt_pos_even);
        int use_even_in_odd_pos = min(cnt_even, cnt_pos_odd);
        int max_sum = use_odd_in_even_pos + use_even_in_odd_pos;
        cout << max_sum << '\n';
    }
    return 0;
}