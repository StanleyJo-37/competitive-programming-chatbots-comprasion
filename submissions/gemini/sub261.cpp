#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long inv(long long n) {
    return power(n, MOD - 2);
}

const int MAXN = 300005;
long long fact[MAXN];
long long invFact[MAXN];

void precompute_factorials(int n) {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = inv(fact[i]);
    }
}

long long nCr_mod_p(int n, int r) {
    if (r < 0 || r > n) {
        return 0;
    }
    return (((fact[n] * invFact[r]) % MOD) * invFact[n - r]) % MOD;
}

struct Mercenary {
    int id;
    int l, r;
};

bool compareMercenaries(const Mercenary& a, const Mercenary& b) {
    return a.l < b.l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    precompute_factorials(n);

    vector<Mercenary> mercenaries(n);
    for (int i = 0; i < n; ++i) {
        mercenaries[i].id = i;
        cin >> mercenaries[i].l >> mercenaries[i].r;
    }

    vector<pair<int, int>> hated_pairs(m);
    for (int i = 0; i < m; ++i) {
        cin >> hated_pairs[i].first >> hated_pairs[i].second;
        hated_pairs[i].first--; 
        hated_pairs[i].second--; 
    }

    sort(mercenaries.begin(), mercenaries.end(), compareMercenaries);

    vector<int> original_id_to_sorted_idx(n);
    for(int i = 0; i < n; ++i) {
        original_id_to_sorted_idx[mercenaries[i].id] = i;
    }

    for(int i = 0; i < m; ++i) {
        hated_pairs[i].first = original_id_to_sorted_idx[hated_pairs[i].first];
        hated_pairs[i].second = original_id_to_sorted_idx[hated_pairs[i].second];
        if (hated_pairs[i].first > hated_pairs[i].second) {
            swap(hated_pairs[i].first, hated_pairs[i].second);
        }
    }

    long long total_ans = 0;

    for (int L = 1; L <= n; ++L) {
        long long current_L_ans = 0;
        
        int R_min_overall = n;
        for(int i = 0; i < n; ++i) {
            if (mercenaries[i].l <= L) {
                R_min_overall = min(R_min_overall, mercenaries[i].r);
            }
        }
        
        vector<int> valid_mercs_at_L_indices;
        for (int i = 0; i < n; ++i) {
            if (mercenaries[i].l <= L) {
                valid_mercs_at_L_indices.push_back(i);
            }
        }
        int k = valid_mercs_at_L_indices.size();

        if (k == 0) continue;

        for (int i = 0; i < (1 << m); ++i) {
            bool possible_subset = true;
            int min_r_in_subset = n + 1;
            
            vector<int> current_forbidden_mercs_indices;
            for (int j = 0; j < m; ++j) {
                if ((i >> j) & 1) {
                    current_forbidden_mercs_indices.push_back(hated_pairs[j].first);
                    current_forbidden_mercs_indices.push_back(hated_pairs[j].second);
                }
            }
            sort(current_forbidden_mercs_indices.begin(), current_forbidden_mercs_indices.end());
            current_forbidden_mercs_indices.erase(unique(current_forbidden_mercs_indices.begin(), current_forbidden_mercs_indices.end()), current_forbidden_mercs_indices.end());

            for (int merc_idx : current_forbidden_mercs_indices) {
                bool found_in_valid = false;
                for (int valid_idx : valid_mercs_at_L_indices) {
                    if (valid_idx == merc_idx) {
                        found_in_valid = true;
                        break;
                    }
                }
                if (found_in_valid) {
                    min_r_in_subset = min(min_r_in_subset, mercenaries[merc_idx].r);
                } else {
                    possible_subset = false;
                    break;
                }
            }

            if (!possible_subset) {
                continue;
            }

            int current_effective_k = k - current_forbidden_mercs_indices.size();
            long long combinations = nCr_mod_p(current_effective_k, L);

            if (__builtin_popcount(i) % 2 == 1) {
                current_L_ans = (current_L_ans - combinations + MOD) % MOD;
            } else {
                current_L_ans = (current_L_ans + combinations) % MOD;
            }
            current_L_ans = (current_L_ans + MOD) % MOD; 
        }

        total_ans = (total_ans + current_L_ans) % MOD;
    }
    
    cout << total_ans << endl;

    return 0;
}