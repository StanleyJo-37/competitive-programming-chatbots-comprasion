#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Read input: n = number of segments, m = maximal coordinate
    int n, m;
    cin >> n >> m;

    // Initialize lmax and rmin to find the intersection of all segments
    int lmax = 1; // maximum of all left ends
    int rmin = m; // minimum of all right ends

    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        // Update lmax and rmin
        lmax = max(lmax, l);
        rmin = min(rmin, r);
    }

    // Since it's guaranteed that there is no integer point that belongs to all segments,
    // we have lmax > rmin (otherwise, there would be an intersection).
    // The largest set of points Sasha can ask about, without being sure Teodor isn't lying,
    // is all points except at least one point in [lmax, rmin].
    // So, the answer is m - (rmin - lmax + 1) if lmax <= rmin, else m (no intersection).
    // But since lmax > rmin, the intersection is empty, so Sasha can ask about all m points.

    // But the problem wants the largest set such that Sasha can't be sure Teodor isn't lying.
    // If Sasha asks about all points except at least one in [lmax, rmin], he can't be sure.
    // So, the answer is m - (rmin - lmax + 1) (if rmin - lmax + 1 > 0), else m.

    int overlap = rmin - lmax + 1;
    int answer = (overlap > 0) ? m - overlap : m;

    cout << answer << endl;
    return 0;
}