#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        // Check if the first element is equal to the sum of the rest (sum is 0 initially)
        // But since the array is sorted, if all elements are same, then any reordering won't help
        bool allSame = true;
        for (int i = 1; i < n; ++i) {
            if (a[i] != a[0]) {
                allSame = false;
                break;
            }
        }
        
        if (allSame) {
            // If all elements are same, then any element (except first) will be sum of previous
            cout << "NO\n";
        } else {
            // Otherwise, we can rearrange to avoid any element being sum of previous
            // Strategy: Place the smallest element first, then largest, then second smallest, etc.
            // This ensures that the sum grows faster than any single element
            vector<int> res;
            int left = 0, right = n - 1;
            while (left <= right) {
                if (left == right) {
                    res.push_back(a[left]);
                } else {
                    res.push_back(a[left]);
                    res.push_back(a[right]);
                }
                left++;
                right--;
            }
            
            // Verify if the constructed array is beautiful
            bool beautiful = true;
            int sum = res[0];
            for (int i = 1; i < n; ++i) {
                if (res[i] == sum) {
                    beautiful = false;
                    break;
                }
                sum += res[i];
            }
            
            if (beautiful) {
                cout << "YES\n";
                for (int num : res) {
                    cout << num << " ";
                }
                cout << "\n";
            } else {
                // If not, try reversing the array (another common pattern)
                reverse(res.begin(), res.end());
                sum = res[0];
                beautiful = true;
                for (int i = 1; i < n; ++i) {
                    if (res[i] == sum) {
                        beautiful = false;
                        break;
                    }
                    sum += res[i];
                }
                if (beautiful) {
                    cout << "YES\n";
                    for (int num : res) {
                        cout << num << " ";
                    }
                    cout << "\n";
                } else {
                    // If still not, try sorting in descending order
                    sort(a.rbegin(), a.rend());
                    sum = a[0];
                    beautiful = true;
                    for (int i = 1; i < n; ++i) {
                        if (a[i] == sum) {
                            beautiful = false;
                            break;
                        }
                        sum += a[i];
                    }
                    if (beautiful) {
                        cout << "YES\n";
                        for (int num : a) {
                            cout << num << " ";
                        }
                        cout << "\n";
                    } else {
                        // If all else fails, try swapping first two elements (if possible)
                        if (n >= 2 && a[0] != a[1]) {
                            swap(a[0], a[1]);
                            sum = a[0];
                            beautiful = true;
                            for (int i = 1; i < n; ++i) {
                                if (a[i] == sum) {
                                    beautiful = false;
                                    break;
                                }
                                sum += a[i];
                            }
                            if (beautiful) {
                                cout << "YES\n";
                                for (int num : a) {
                                    cout << num << " ";
                                }
                                cout << "\n";
                            } else {
                                cout << "NO\n";
                            }
                        } else {
                            cout << "NO\n";
                        }
                    }
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}