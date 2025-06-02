#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct Post {
    int f;
    int p;
    string s;
};

int main() {
    int N, M;
    cin >> N >> M;
    
    unordered_set<int> specialFriends;
    for (int i = 0; i < N; ++i) {
        int id;
        cin >> id;
        specialFriends.insert(id);
    }
    
    vector<Post> specialPosts, regularPosts;
    for (int i = 0; i < M; ++i) {
        int f, p;
        string s;
        cin >> f >> p >> s;
        Post post = {f, p, s};
        if (specialFriends.find(f) != specialFriends.end()) {
            specialPosts.push_back(post);
        } else {
            regularPosts.push_back(post);
        }
    }
    
    // Sort special posts by descending popularity
    sort(specialPosts.begin(), specialPosts.end(), [](const Post &a, const Post &b) {
        return a.p > b.p;
    });
    
    // Sort regular posts by descending popularity
    sort(regularPosts.begin(), regularPosts.end(), [](const Post &a, const Post &b) {
        return a.p > b.p;
    });
    
    // Output special posts first, then regular posts
    for (const auto &post : specialPosts) {
        cout << post.s << endl;
    }
    for (const auto &post : regularPosts) {
        cout << post.s << endl;
    }
    
    return 0;
}