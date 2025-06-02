#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> a(N + 1); // 1-based indexing
    for (int i = 1; i <= N; ++i) {
        cin >> a[i];
    }

    vector<int> Left(N + 1, 0);  // Left(i) for each i
    vector<int> Right(N + 1, 0); // Right(i) for each i

    // Find Left(i) for all i using a stack
    stack<int> st_left;
    for (int i = 1; i <= N; ++i) {
        // Pop elements from stack while they are less than or equal to a[i]
        while (!st_left.empty() && a[st_left.top()] <= a[i]) {
            st_left.pop();
        }
        // If stack is not empty, top is the closest index to the left with a greater value
        if (!st_left.empty()) {
            Left[i] = st_left.top();
        }
        // Push current index onto stack
        st_left.push(i);
    }

    // Find Right(i) for all i using a stack
    stack<int> st_right;
    for (int i = N; i >= 1; --i) {
        // Pop elements from stack while they are less than or equal to a[i]
        while (!st_right.empty() && a[st_right.top()] <= a[i]) {
            st_right.pop();
        }
        // If stack is not empty, top is the closest index to the right with a greater value
        if (!st_right.empty()) {
            Right[i] = st_right.top();
        }
        // Push current index onto stack
        st_right.push(i);
    }

    // Compute the maximum IndexProduct(i)
    long long maxProduct = 0;
    for (int i = 1; i <= N; ++i) {
        long long prod = 1LL * Left[i] * Right[i];
        if (prod > maxProduct) {
            maxProduct = prod;
        }
    }

    cout << maxProduct << endl;
    return 0;
}