#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN = 3e5 + 5;
vector<pair<int, char>> adj[MAXN];
int sz[MAXN];
int depth[MAXN];
long long h[MAXN];
long long p_pow[MAXN];
const long long P1 = 31;
const long long M1 = 1e9 + 7;

map<long long, int> cnt[MAXN];
int ans_p = 1;
int min_size = MAXN;

void dfs_size(int u, int p) {
    sz[u] = 1;
    for (auto& edge : adj[u]) {
        int v = edge.first;
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        dfs_size(v, u);
        sz[u] += sz[v];
    }
}

void dfs_hash(int u, int p) {
    cnt[u][h[u]] = 1;
    for (auto& edge : adj[u]) {
        int v = edge.first;
        char c = edge.second;
        if (v == p) continue;
        h[v] = (h[u] * P1 + (c - 'a' + 1)) % M1;
        dfs_hash(v, u);
        if (cnt[u].size() < cnt[v].size()) {
            swap(cnt[u], cnt[v]);
        }
        for (auto& it : cnt[v]) {
            cnt[u][it.first] += it.second;
        }
        cnt[v].clear(); 
    }

    if (depth[u] > 0) {
        if (cnt[u].count(h[u])) {
            cnt[u][h[u]]--;
            if (cnt[u][h[u]] == 0) {
                cnt[u].erase(h[u]);
            }
        }
        
        long long current_hash = (h[u] - ((h[u] / p_pow[depth[u] - ans_p + 1]) * p_pow[depth[u] - ans_p + 1]) % M1 + M1) % M1;
        
        current_hash = (current_hash + (h[u] / p_pow[depth[u] - ans_p + 1]) % M1 * p_pow[depth[u] - ans_p] % M1) % M1;

        if (cnt[u].find(current_hash) != cnt[u].end()) {
            cnt[u][current_hash]++;
        } else {
            cnt[u][current_hash] = 1;
        }
    }

    if (depth[u] >= 1 && cnt[u].size() + 1 < min_size) { 
        min_size = cnt[u].size() + 1;
        ans_p = depth[u];
    } else if (depth[u] >= 1 && cnt[u].size() + 1 == min_size) {
        ans_p = min(ans_p, depth[u]);
    }
}

void dfs_recalculate_hash(int u, int p, int target_p, long long current_prefix_hash) {
    if (depth[u] == target_p - 1) {
        current_prefix_hash = 0; 
    }

    if (depth[u] >= target_p) {
        h[u] = (current_prefix_hash * p_pow[1] + (h[u] / p_pow[depth[u] - target_p] % P1)) % M1; // this is wrong
    } else {
        h[u] = current_prefix_hash;
    }

    for (auto& edge : adj[u]) {
        int v = edge.first;
        char c = edge.second;
        if (v == p) continue;

        if (depth[v] == target_p) {
            dfs_recalculate_hash(v, u, target_p, current_prefix_hash);
        } else {
            dfs_recalculate_hash(v, u, target_p, (current_prefix_hash * P1 + (c - 'a' + 1)) % M1);
        }
    }
}


void dfs_collect_hashes(int u, int p, set<long long>& hashes) {
    hashes.insert(h[u]);
    for (auto& edge : adj[u]) {
        int v = edge.first;
        if (v == p) continue;
        dfs_collect_hashes(v, u, hashes);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    depth[1] = 0;
    dfs_size(1, 0);

    p_pow[0] = 1;
    for (int i = 1; i <= n; ++i) {
        p_pow[i] = (p_pow[i - 1] * P1) % M1;
    }

    min_size = n;
    ans_p = 1; 

    for (int p_val = 1; p_val <= n; ++p_val) {
        set<long long> current_language_hashes;
        
        vector<long long> original_h(n + 1);
        for(int i = 1; i <= n; ++i) {
            original_h[i] = h[i];
        }

        vector<pair<int,char>> q_bfs;
        q_bfs.push_back({1,'\0'});
        vector<long long> new_h(n + 1);

        int head = 0;
        vector<bool> visited(n + 1, false);
        visited[1] = true;
        new_h[1] = 0;

        while(head < q_bfs.size()){
            pair<int,char> current = q_bfs[head++];
            int u = current.first;
            char char_u = current.second;

            if (depth[u] == p_val) {
                 // Skip this character, effectively removing the p_val-th char
            } else {
                current_language_hashes.insert(new_h[u]);
            }

            for (auto& edge : adj[u]) {
                int v = edge.first;
                char c = edge.second;
                if (!visited[v]) {
                    visited[v] = true;
                    if (depth[v] == p_val) {
                        new_h[v] = new_h[u]; 
                    } else {
                        new_h[v] = (new_h[u] * P1 + (c - 'a' + 1)) % M1;
                    }
                    q_bfs.push_back({v,c});
                }
            }
        }

        bool changed = false;
        if(p_val <= depth[1]){
            changed = false; 
        } else {
            for(int i = 1; i <= n; ++i){
                if(depth[i] >= p_val){
                    changed = true;
                    break;
                }
            }
        }
        

        if (changed && current_language_hashes.size() < min_size) {
            min_size = current_language_hashes.size();
            ans_p = p_val;
        } else if (changed && current_language_hashes.size() == min_size) {
            ans_p = min(ans_p, p_val);
        }
    }


    cout << min_size << endl;
    cout << ans_p << endl;

    return 0;
}