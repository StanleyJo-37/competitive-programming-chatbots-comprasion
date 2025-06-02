#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string s;
    cin >> s;
    int plus = count(s.begin(), s.end(), '+');
    int minus = n - plus;
    
    int q;
    cin >> q;
    while (q--) {
        long long a, b;
        cin >> a >> b;
        
        // The equation to solve is: (a*x_plus + b*x_minus) - (a*y_plus + b*y_minus) = 0
        // Where x_plus is count of '+' rounds where we choose a, y_plus is count of '+' rounds where we choose b, etc.
        // Let x_plus + y_plus = plus, x_minus + y_minus = minus
        // The equation simplifies to: a*(x_plus - y_plus) + b*(x_minus - y_minus) = 0
        // Let x_plus - y_plus = k, x_minus - y_minus = m
        // Then a*k + b*m = 0 => m = - (a*k)/b
        // Also, x_plus + y_plus = plus => x_plus = (plus + k)/2, y_plus = (plus - k)/2
        // Similarly, x_minus = (minus + m)/2, y_minus = (minus - m)/2
        // All these must be non-negative integers.
        // So, (plus + k) must be even and >=0, (plus - k) must be even and >=0, etc.
        // Similarly for minus and m.
        
        // The key observation is that m must be an integer, so (a*k) must be divisible by b.
        // Let d = gcd(a, b), then a = d*a', b = d*b' where gcd(a', b') = 1.
        // Then m = - (a*k)/b = - (a'*k)/b'
        // For m to be integer, b' must divide (a'*k), but since gcd(a', b')=1, b' must divide k.
        // So k = t*b' where t is integer.
        // Then m = - (a' * t * b') / b' = -a' * t
        // Now, we need to find t such that:
        // (plus + t*b') is even and >=0, (plus - t*b') is even and >=0
        // (minus - a'*t) is even and >=0, (minus + a'*t) is even and >=0
        
        long long d = __gcd(a, b);
        long long a_prime = a / d;
        long long b_prime = b / d;
        
        bool possible = false;
        
        // We can iterate t in a small range around zero, since t cannot be too large or too small.
        // The constraints are:
        // plus >= t*b' and plus >= -t*b' => |t| <= plus / b'
        // minus >= a'*t and minus >= -a'*t => |t| <= minus / a'
        // So |t| <= min(plus / b', minus / a')
        // Also, (plus + t*b') must be even, (minus - a'*t) must be even.
        
        // To find t, we can check t in the range [-2, 2] to cover possible cases.
        // This is because the parity constraints limit the possible t values.
        for (long long t = -2; t <= 2; ++t) {
            long long k = t * b_prime;
            long long m = -t * a_prime;
            
            if ((plus + k) % 2 != 0 || (plus - k) % 2 != 0) continue;
            if ((minus + m) % 2 != 0 || (minus - m) % 2 != 0) continue;
            
            long long x_plus = (plus + k) / 2;
            long long y_plus = (plus - k) / 2;
            long long x_minus = (minus + m) / 2;
            long long y_minus = (minus - m) / 2;
            
            if (x_plus >= 0 && y_plus >= 0 && x_minus >= 0 && y_minus >= 0) {
                possible = true;
                break;
            }
        }
        
        if (possible) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}