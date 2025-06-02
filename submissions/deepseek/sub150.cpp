#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Function to find the minimum possible score of a permutation
int findMinScore(vector<int>& a) {
    int n = a.size();
    if (n == 2) {
        return a[0] ^ a[1];
    }
    
    // The idea is to find the minimal maximum XOR between adjacent elements in any permutation.
    // This can be approached by finding the minimal spanning tree (MST) where edges are XORs.
    // The answer is the maximum edge in the MST.
    
    // Prim's algorithm for MST with XOR as edge weights
    vector<bool> inMST(n, false);
    vector<int> minEdge(n, INT_MAX);
    minEdge[0] = 0;
    int maxInMST = 0;
    
    for (int i = 0; i < n; ++i) {
        int u = -1;
        // Find the vertex with the smallest minEdge not yet in MST
        for (int j = 0; j < n; ++j) {
            if (!inMST[j] && (u == -1 || minEdge[j] < minEdge[u])) {
                u = j;
            }
        }
        
        inMST[u] = true;
        maxInMST = max(maxInMST, minEdge[u]);
        
        // Update minEdge for adjacent vertices (all other vertices in this case)
        for (int v = 0; v < n; ++v) {
            if (!inMST[v]) {
                int xorVal = a[u] ^ a[v];
                if (xorVal < minEdge[v]) {
                    minEdge[v] = xorVal;
                }
            }
        }
    }
    
    return maxInMST;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cout << findMinScore(a) << endl;
    return 0;
}