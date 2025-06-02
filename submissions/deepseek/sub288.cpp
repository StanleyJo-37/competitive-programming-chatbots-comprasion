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

    vector<int> left(N + 1, 0); // Stores Left(i)
    vector<int> right(N + 1, 0); // Stores Right(i)
    stack<int> s; // Monotonic stack to find nearest greater elements

    // Compute Left(i) using a monotonic stack (left to right pass)
    for (int i = 1; i <= N; ++i) {
        while (!s.empty() && a[s.top()] <= a[i]) {
            s.pop(); // Remove elements <= current element
        }
        if (!s.empty()) {
            left[i] = s.top(); // The remaining top is the nearest greater to the left
        }
        s.push(i); // Push current index to stack
    }

    // Clear the stack for the next pass
    while (!s.empty()) s.pop();

    // Compute Right(i) using a monotonic stack (right to left pass)
    for (int i = N; i >= 1; --i) {
        while (!s.empty() && a[s.top()] <= a[i]) {
            s.pop(); // Remove elements <= current element
        }
        if (!s.empty()) {
            right[i] = s.top(); // The remaining top is the nearest greater to the right
        }
        s.push(i); // Push current index to stack
    }

    // Compute the maximum IndexProduct
    int maxProduct = 0;
    for (int i = 1; i <= N; ++i) {
        int product = left[i] * right[i];
        if (product > maxProduct) {
            maxProduct = product;
        }
    }

    cout << maxProduct << endl;
    return 0;
}