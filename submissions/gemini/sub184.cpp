#include <iostream>
#include <vector>
#include <stack>
#include <algorithm> // For std::swap

// Define a constant for maximum log N, used for binary lifting.
// For N = 10^5, log2(10^5) is approximately 16.6. So 18 is a safe upper bound.
const int MAX_LOGN = 18;

// Global vectors to store precomputed data. These are declared globally
// to allow efficient memory management across multiple test cases by
// resizing and reusing the same memory, rather than reallocating.
std::vector<int> H;          // Stores heights of stones (0-indexed).
std::vector<int> next_stone; // next_stone[i] stores the index of the next visible stone from i.
                             // If no such stone exists, it stores N (a sentinel value).
std::vector<int> len;        // len[i] stores the number of stones visible from stone i.
                             // This is equivalent to the length of the chain starting from next_stone[i].
                             // len[N] (for the sentinel) is 0.
std::vector<std::vector<int>> up; // up[i][k] stores the (2^k)-th visible stone from i.
                                 // up[i][0] is next_stone[i].
                                 // If a stone is N (sentinel), its ancestors are also N.

void solve() {
    int N, M;
    std::cin >> N >> M;

    // Resize H vector and read input heights.
    H.resize(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> H[i];
    }

    // Resize and initialize next_stone, len, and up tables for the current test case.
    // N is used as a sentinel value to indicate no next visible stone.
    // The size N+1 is used to accommodate the sentinel node N.
    next_stone.assign(N + 1, N); // Initialize all with N
    len.assign(N + 1, 0);        // len[N] = 0, others will be computed
    up.assign(N + 1, std::vector<int>(MAX_LOGN, N)); // Initialize all with N

    // Step 1: Compute next_stone[i] for all i using a monotonic stack.
    // We iterate from right to left (N-1 down to 0) to find the next greater element.
    std::stack<int> st;
    for (int i = N - 1; i >= 0; --i) {
        // Pop elements from the stack that are not strictly greater than H[i].
        // If H[st.top()] <= H[i], then st.top() cannot be the next greater element for i,
        // and it also cannot be the next greater element for any element to the left of i
        // that is smaller than H[i] (because H[i] would block it).
        while (!st.empty() && H[st.top()] <= H[i]) {
            st.pop();
        }
        // If the stack is empty, no next greater element exists to the right.
        // Otherwise, st.top() is the next greater element.
        next_stone[i] = st.empty() ? N : st.top();
        // Push the current index onto the stack.
        st.push(i);
    }

    // Step 2: Compute len[i] and up[i][0] for all i.
    // len[i] is the count of visible stones from i. This is the length of the chain
    // starting from next_stone[i] (including next_stone[i] itself).
    // up[i][0] is simply next_stone[i].
    for (int i = N - 1; i >= 0; --i) {
        len[i] = 1 + len[next_stone[i]]; // len[N] is 0, so the base case for chain end is handled.
        up[i][0] = next_stone[i];
    }

    // Step 3: Precompute up[i][k] for k > 0 using binary lifting.
    // up[i][k] represents the (2^k)-th visible stone from i.
    // It's found by taking the (2^(k-1))-th visible stone from i, and then
    // taking another (2^(k-1))-th visible stone from that intermediate stone.
    for (int k = 1; k < MAX_LOGN; ++k) {
        for (int i = 0; i < N; ++i) {
            // If up[i][k-1] is N (meaning no (2^(k-1))-th visible stone exists),
            // then up[i][k] will also be N. Otherwise, compute it.
            if (up[i][k-1] == N) {
                up[i][k] = N;
            } else {
                up[i][k] = up[up[i][k-1]][k-1];
            }
        }
    }

    // Process M queries.
    for (int q = 0; q < M; ++q) {
        int A, B;
        std::cin >> A >> B;
        // Convert 1-based indices from problem statement to 0-based indices for array access.
        int u = A - 1;
        int v = B - 1;

        // Get the first visible stone from A and B. These are the starting points
        // of the visibility chains whose intersection we need to find.
        int u_prime = next_stone[u];
        int v_prime = next_stone[v];

        // If either u_prime or v_prime is N (the sentinel value), it means
        // there are no visible stones from A or B respectively.
        // In this case, their intersection is empty.
        if (u_prime == N || v_prime == N) {
            std::cout << 0 << "\n";
            continue;
        }

        // To simplify the lifting process, ensure u_prime is the deeper node
        // (or at the same depth) in the functional graph.
        if (len[u_prime] < len[v_prime]) {
            std::swap(u_prime, v_prime);
        }

        // Lift u_prime up to the same depth as v_prime using binary lifting.
        // We iterate from the largest power of 2 down to 0.
        int diff = len[u_prime] - len[v_prime];
        for (int k = MAX_LOGN - 1; k >= 0; --k) {
            // If the k-th bit of 'diff' is set, it means we need to jump by 2^k steps.
            if ((diff >> k) & 1) {
                u_prime = up[u_prime][k];
            }
        }

        // After lifting, if u_prime and v_prime are the same node,
        // then this node is the first common visible stone.
        // The number of common visible stones is the length of the chain starting from this node.
        if (u_prime == v_prime) {
            std::cout << len[u_prime] << "\n";
            continue;
        }

        // If they are not the same node, lift them simultaneously until their parents are the same.
        // This finds the Lowest Common Ancestor (LCA) in terms of the functional graph.
        // The LCA itself is the first common visible stone.
        for (int k = MAX_LOGN - 1; k >= 0; --k) {
            // If their (2^k)-th ancestors are different, move both nodes up.
            // This ensures we don't jump past the actual LCA.
            if (up[u_prime][k] != up[v_prime][k]) {
                u_prime = up[u_prime][k];
                v_prime = up[v_prime][k];
            }
        }
        // After the loop, u_prime and v_prime are children of the first common node.
        // The first common node is up[u_prime][0] (or up[v_prime][0]).
        // The number of common visible stones is the length of the chain starting from this common node.
        std::cout << len[up[u_prime][0]] << "\n";
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T; // Read the number of test cases.
    while (T--) {
        solve(); // Solve each test case.
    }

    return 0;
}
