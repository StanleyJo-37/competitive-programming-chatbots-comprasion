#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Node {
    int id;
    ll weight;
    Node* parent;
    vector<Node*> children;
    vector<pair<ll, ll>> dp; // {sum, max_len}
};

Node* nodes[400005];
int cnt = 1;
ll last = 0;

void add_node(ll R, ll W) {
    R ^= last;
    W ^= last;
    Node* parent = nodes[R];
    Node* new_node = new Node{cnt + 1, W, parent, {}, {}};
    nodes[++cnt] = new_node;
    parent->children.push_back(new_node);
    
    // Initialize DP for the new node
    new_node->dp.emplace_back(W, 1);
    Node* current = parent;
    ll sum = W;
    int len = 1;
    
    while (current != nullptr) {
        if (current->weight >= W) {
            sum += current->weight;
            len++;
            new_node->dp.emplace_back(sum, len);
            current = current->parent;
        } else {
            break;
        }
    }
}

ll query(ll R, ll X) {
    R ^= last;
    X ^= last;
    Node* node = nodes[R];
    ll res = 0;
    
    // Binary search on the DP array to find the maximum len where sum <= X
    int left = 0, right = node->dp.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (node->dp[mid].first <= X) {
            res = node->dp[mid].second;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    last = res;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int Q;
    cin >> Q;
    
    nodes[1] = new Node{1, 0, nullptr, {}, {}};
    nodes[1]->dp.emplace_back(0, 1);
    
    while (Q--) {
        int type;
        ll p, q;
        cin >> type >> p >> q;
        
        if (type == 1) {
            add_node(p, q);
        } else {
            cout << query(p, q) << '\n';
        }
    }
    
    return 0;
}