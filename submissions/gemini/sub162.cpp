#include <iostream> // Required for standard input/output operations (cin, cout)
#include <vector>   // Required for std::vector, a dynamic array
#include <string>   // Required for std::string
#include <complex>  // Required for std::complex, used in FFT for complex numbers
#include <algorithm> // Required for std::swap and std::reverse
#include <cmath>    // Required for mathematical functions like cos, sin, acos, round

// Define PI for complex number calculations. acos(-1.0) is a common way to get PI.
const double PI = acos(-1.0);

// Alias for std::complex<double> for convenience
using Complex = std::complex<double>;

/**
 * @brief Performs Fast Fourier Transform (FFT) or Inverse FFT (IFFT) on a vector of complex numbers.
 *
 * @param a The input vector of complex numbers (polynomial coefficients). Modified in-place.
 * @param invert If true, performs IFFT; otherwise, performs FFT.
 */
void fft(std::vector<Complex>& a, bool invert) {
    int n = a.size(); // Get the size of the input vector

    // Bit-reversal permutation: Rearranges the input array such that elements are in bit-reversed order.
    // This is crucial for the iterative Cooley-Tukey FFT algorithm.
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1; // Start with the most significant bit
        // Find the first bit in j that is 0, starting from MSB.
        // Flip all 1s to 0s until a 0 is found, then flip that 0 to 1.
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit; // j now holds the bit-reversed index for i
        if (i < j) // Swap elements only if i is less than j to avoid redundant swaps
            std::swap(a[i], a[j]);
    }

    // Cooley-Tukey algorithm: Iteratively combines smaller DFTs into larger ones.
    // `len` is the current length of the sub-problems (DFT size). It doubles in each iteration.
    for (int len = 2; len <= n; len <<= 1) {
        // Calculate the principal root of unity for the current length.
        // `ang` is the angle for the complex exponential.
        // If `invert` is true, we use a negative angle for IFFT.
        double ang = 2 * PI / len * (invert ? -1 : 1);
        Complex wlen(cos(ang), sin(ang)); // wlen is e^(i * ang)

        // Iterate through the array in blocks of size `len`.
        for (int i = 0; i < n; i += len) {
            Complex w(1); // `w` is the current power of the root of unity, starts at 1
            // Iterate through the first half of the current block.
            for (int j = 0; j < len / 2; j++) {
                // Butterfly operation:
                // u = a[i + j]
                // v = a[i + j + len / 2] * w
                // a[i + j] = u + v
                // a[i + j + len / 2] = u - v
                Complex u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen; // Update w for the next butterfly operation
            }
        }
    }

    // Scaling for inverse FFT: Divide by n (the total size)
    if (invert) {
        for (Complex& x : a)
            x /= n;
    }
}

/**
 * @brief Multiplies two polynomials represented by vectors of their coefficients using FFT.
 * This function computes the convolution of two sequences.
 *
 * @param a Coefficients of the first polynomial.
 * @param b Coefficients of the second polynomial.
 * @return A vector of long long representing the coefficients of the product polynomial.
 */
std::vector<long long> multiply(const std::vector<long long>& a, const std::vector<long long>& b) {
    // Convert input long long vectors to complex vectors for FFT
    std::vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    // Determine the smallest power of 2 that is greater than or equal to the sum of lengths - 1.
    // This is the required size for FFT to avoid aliasing.
    while (n < a.size() + b.size())
        n <<= 1;
    // Resize complex vectors to the determined FFT size, padding with zeros
    fa.resize(n);
    fb.resize(n);

    // Perform forward FFT on both polynomials
    fft(fa, false);
    fft(fb, false);

    // Multiply the transformed polynomials point-wise in the frequency domain.
    // This corresponds to convolution in the time domain.
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];

    // Perform inverse FFT to transform the product back to the time domain (coefficients)
    fft(fa, true);

    // Convert complex results back to long long.
    // Round to the nearest integer to mitigate floating-point precision errors.
    std::vector<long long> result(n);
    for (int i = 0; i < n; i++)
        result[i] = static_cast<long long>(round(fa[i].real()));
    return result;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents cin from flushing cout before each input operation.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Read permutation p.
    // The input p is 1-indexed (1 to 26). Convert it to 0-indexed (0 to 25) for easier use.
    std::vector<int> p(26);
    for (int i = 0; i < 26; ++i) {
        std::cin >> p[i];
        p[i]--; // Convert to 0-indexed character value (e.g., 1 becomes 0 for 'a')
    }

    // Read strings s (pattern) and t (text).
    std::string s, t;
    std::cin >> s >> t;

    int N = s.length(); // Length of pattern string s
    int M = t.length(); // Length of text string t

    // Convert characters of s and t to 0-indexed integer values ('a'=0, 'b'=1, ..., 'z'=25)
    std::vector<int> s_val(N);
    for (int i = 0; i < N; ++i) {
        s_val[i] = s[i] - 'a';
    }
    std::vector<int> t_val(M);
    for (int i = 0; i < M; ++i) {
        t_val[i] = t[i] - 'a';
    }

    // The core idea is to transform the matching condition into a sum that can be computed via FFT.
    // For each position k in s and j in t, we want to check if t[j+k] matches s[k].
    // The condition is: (val(t[j+k]) == val(s[k])) OR (val(t[j+k]) == p[val(s[k])]).
    // Let x_k = val(s[k]) and y_k = p[val(s[k])].
    // The condition can be rewritten as: (val(t[j+k]) - x_k) * (val(t[j+k]) - y_k) = 0.
    // Expanding this product: val(t[j+k])^2 - (x_k + y_k) * val(t[j+k]) + x_k * y_k = 0.
    // For a substring t[j...j+N-1] to be an occurrence of s, this condition must hold for all k from 0 to N-1.
    // This means the sum of these terms over k must be 0:
    // Sum_k (val(t[j+k])^2 - (x_k + y_k) * val(t[j+k]) + x_k * y_k) = 0.
    // This sum can be broken into three separate convolutions:
    // 1. Sum_k (val(t[j+k])^2)
    // 2. Sum_k (-(x_k + y_k) * val(t[j+k]))
    // 3. Sum_k (x_k * y_k) (This is a constant sum, not a convolution per se)

    // Term 1: Sum_k (val(t[j+k])^2)
    // This is a convolution of a pattern polynomial P_D where P_D[k]=1, and a text polynomial T_sq where T_sq[m]=val(t_m)^2.
    std::vector<long long> poly_PD(N);
    for (int i = 0; i < N; ++i) {
        poly_PD[i] = 1; // All coefficients are 1
    }
    std::vector<long long> poly_T_sq(M);
    for (int i = 0; i < M; ++i) {
        poly_T_sq[i] = static_cast<long long>(t_val[i]) * t_val[i]; // Square of character value
    }
    // For convolution Sum_k A_k B_{j+k}, we need to reverse the pattern polynomial A.
    std::reverse(poly_PD.begin(), poly_PD.end());
    std::vector<long long> conv1 = multiply(poly_PD, poly_T_sq);

    // Term 2: Sum_k (-(x_k + y_k) * val(t[j+k]))
    // This is a convolution of a pattern polynomial P_B where P_B[k]=-(x_k+y_k), and a text polynomial T_val where T_val[m]=val(t_m).
    std::vector<long long> poly_PB(N);
    for (int i = 0; i < N; ++i) {
        long long x_k = s_val[i];
        long long y_k = p[s_val[i]]; // p[val(s_k)] is the 0-indexed mapped character value
        poly_PB[i] = -(x_k + y_k); // Coefficient is -(x_k + y_k)
    }
    std::vector<long long> poly_T_val(M);
    for (int i = 0; i < M; ++i) {
        poly_T_val[i] = t_val[i]; // Character value
    }
    // Reverse poly_PB for convolution
    std::reverse(poly_PB.begin(), poly_PB.end());
    std::vector<long long> conv2 = multiply(poly_PB, poly_T_val);

    // Term 3: Sum_k (x_k * y_k)
    // This is a constant sum over all k in s.
    long long S_xy = 0;
    for (int i = 0; i < N; ++i) {
        long long x_k = s_val[i];
        long long y_k = p[s_val[i]];
        S_xy += x_k * y_k;
    }

    // Construct the result string by checking the total sum for each starting position j in t.
    // The convolution result for a match starting at index j in t (i.e., for substring t[j...j+N-1])
    // is found at index (N-1+j) in the convolution array. This is due to the reversal of the pattern polynomial.
    std::string result_str = "";
    for (int j = 0; j <= M - N; ++j) {
        // Calculate the total sum for the current window starting at t[j]
        long long current_sum = conv1[N - 1 + j] + conv2[N - 1 + j] + S_xy;
        // If the sum is 0, it means all individual terms were 0, indicating a perfect match.
        if (current_sum == 0) {
            result_str += '1';
        } else {
            result_str += '0';
        }
    }

    // Print the final result string
    std::cout << result_str << std::endl;

    return 0; // Indicate successful execution
}
