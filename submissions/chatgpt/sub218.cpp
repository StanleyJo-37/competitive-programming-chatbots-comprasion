#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

// Structure to store each post's data
struct Post {
    int friend_id;      // Identifier of the friend who created the post
    int popularity;     // Popularity of the post
    string content;     // Content of the post
    bool is_special;    // Whether the friend is special
};

int main() {
    int N, M;
    cin >> N >> M;

    unordered_set<int> special_friends; // To quickly check if a friend is special

    // Read special friends' identifiers
    for (int i = 0; i < N; ++i) {
        int id;
        cin >> id;
        special_friends.insert(id);
    }

    vector<Post> posts;

    // Read all posts
    for (int i = 0; i < M; ++i) {
        int f, p;
        string s;
        cin >> f >> p >> s;
        // Check if the friend is special
        bool is_special = (special_friends.find(f) != special_friends.end());
        posts.push_back({f, p, s, is_special});
    }

    // Custom sort:
    // 1. Special friends' posts first (is_special true before false)
    // 2. Within each group, sort by popularity descending
    sort(posts.begin(), posts.end(), [](const Post &a, const Post &b) {
        if (a.is_special != b.is_special)
            return a.is_special > b.is_special; // Special first
        return a.popularity > b.popularity;     // Higher popularity first
    });

    // Output the content of posts in the required order
    for (const auto &post : posts) {
        cout << post.content << endl;
    }

    return 0;
}