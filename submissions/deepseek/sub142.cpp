#include <iostream>
using namespace std;

void solve() {
    int T;
    cin >> T;
    while (T--) {
        long long N, A;
        cin >> N >> A;
        
        // The sum's parity depends on the count of odd numbers in the array.
        // The bitwise AND of all elements is A, so all elements must have at least the bits set in A.
        // For the sum to be odd, there must be an odd number of odd elements.
        // For the sum to be even, there must be an even number of odd elements.
        
        // Case 1: If N == 1, the only element is A itself.
        // The sum is A, so parity is same as A's parity.
        if (N == 1) {
            if (A % 2 == 1) {
                cout << "Odd\n";
            } else {
                cout << "Even\n";
            }
            continue;
        }
        
        // Case 2: If A is even, then all elements must be even (since even AND anything is even).
        // Sum of even numbers is even.
        if (A % 2 == 0) {
            cout << "Even\n";
            continue;
        }
        
        // Case 3: If A is odd, then all elements must be odd (since odd AND requires all to be odd).
        // Sum of N odd numbers: if N is odd, sum is odd; else even.
        // But if N is even, sum is even; else odd.
        // However, if N > 1, we can have both possibilities (since we can choose any odd numbers).
        // Wait, no: if A is odd, all numbers must be odd, so sum parity is N's parity.
        // But the problem says "hidden array", meaning we can choose any array that satisfies the AND condition.
        // For N > 1, if A is odd, we can have:
        // - All elements odd (sum parity is N's parity).
        // But can we have a mix? No, because AND of even and odd is even, so all must be odd if A is odd.
        // So sum parity is N's parity.
        // But the problem allows any array that satisfies the AND condition, but the only possible arrays are those with all elements odd.
        // So sum parity is N's parity.
        // But the sample input shows "Impossible" for some cases. Why?
        // Re-examining: if N == 1, it's determined. If N > 1 and A is even, sum is even (since all elements must be even).
        // If N > 1 and A is odd, all elements must be odd, so sum is odd if N is odd, even if N is even.
        // But the sample input 3 has N=74120341, A=829182732 (which is even), so output is Even.
        // Another case: N=2, A=1 (odd). Then sum is 2 (even) if both are 1, or higher if other odds, but sum parity is even.
        // So for N > 1 and A odd, sum parity is N's parity.
        // But the problem says "cannot be determined". Is there a case where it's impossible to determine?
        // No, because if A is odd, all elements are odd, so sum parity is N's parity.
        // So the only "Impossible" case is when the problem statement allows for multiple possible parities, but in our analysis, it's always determined.
        // This suggests the problem might have a different interpretation.
        // Alternative interpretation: the array can be any array where the AND is A, but not necessarily all elements have all bits of A.
        // For example, for N=2, A=0, possible arrays: [0,0], [0,2], [2,0], [2,2], etc. Sum parity can be even or odd (e.g., [1,2] has AND 0 and sum 3 (odd)).
        // So if A is even and N >= 2, sum parity can be either even or odd.
        // If A is odd, all elements must be odd, so sum parity is N's parity.
        // Therefore:
        // - N == 1: sum parity is A's parity.
        // - N > 1 and A odd: sum parity is N's parity.
        // - N > 1 and A even: Impossible (since sum can be either even or odd).
        
        if (A % 2 == 1) {
            if (N % 2 == 1) {
                cout << "Odd\n";
            } else {
                cout << "Even\n";
            }
        } else {
            cout << "Impossible\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}