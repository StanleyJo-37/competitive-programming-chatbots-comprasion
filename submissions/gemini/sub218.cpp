#include <iostream> // Required for standard input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector, a dynamic array to store posts
#include <string>   // Required for std::string, to store the content of posts
#include <algorithm> // Required for std::sort, to sort the vector of posts
#include <unordered_set> // Required for std::unordered_set, to efficiently store and check special friend IDs

// Define a structure to represent a single post.
// This bundles all relevant information about a post together.
struct Post {
    int friend_id;          // The unique identifier of the friend who created this post.
    int popularity;         // The popularity score of the post, pre-calculated by ChefBook.
    std::string content;    // The actual text content of the post.
    bool is_special_friend; // A flag indicating if the friend who made this post is special.
                            // This is determined during input processing for efficiency.
};

// Custom comparison function for sorting `Post` objects.
// This function defines the strict weak ordering required by `std::sort`.
// It returns `true` if `p1` should come before `p2` in the sorted order, `false` otherwise.
bool comparePosts(const Post& p1, const Post& p2) {
    // Rule 1: Posts of special friends should be shown first, irrespective of popularity.
    // If p1 is from a special friend AND p2 is NOT from a special friend,
    // then p1 has higher priority and should come before p2.
    if (p1.is_special_friend && !p2.is_special_friend) {
        return true;
    }
    // If p1 is NOT from a special friend AND p2 IS from a special friend,
    // then p2 has higher priority, so p1 should NOT come before p2.
    // (This means p2 comes before p1).
    if (!p1.is_special_friend && p2.is_special_friend) {
        return false;
    }

    // If we reach this point, it means both posts are either:
    // A) Both from special friends.
    // B) Both from non-special friends.
    // In either of these cases, the popularity determines the order.
    // Rule 2 & 3: Among posts of the same category (both special or both non-special),
    // more popular posts should be shown earlier. Higher popularity value means earlier.
    // So, if p1's popularity is greater than p2's, p1 should come before p2.
    return p1.popularity > p2.popularity;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // `std::ios_base::sync_with_stdio(false)` unties C++ streams from C standard I/O,
    // potentially speeding up I/O operations.
    // `std::cin.tie(NULL)` prevents `std::cout` from flushing before each `std::cin` operation,
    // which can also speed up I/O, especially when mixing `cin` and `cout`.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, M; // N: number of special friends, M: number of posts
    std::cin >> N >> M;

    // Use an `std::unordered_set` to store the identifiers of special friends.
    // `unordered_set` provides average O(1) time complexity for insertion and lookup,
    // which is efficient for checking if a friend is special.
    std::unordered_set<int> special_friends_set;
    special_friends_set.reserve(N); // Pre-allocate memory for the set to potentially improve performance.
    for (int i = 0; i < N; ++i) {
        int friend_id;
        std::cin >> friend_id;
        special_friends_set.insert(friend_id);
    }

    // Use an `std::vector` to store all the `Post` objects.
    // `std::vector` is suitable for dynamic collections and can be efficiently sorted.
    std::vector<Post> posts;
    posts.reserve(M); // Pre-allocate memory for the vector to avoid reallocations
                      // during `push_back`, which can improve performance.

    // Read M posts and populate the `posts` vector.
    for (int i = 0; i < M; ++i) {
        int f, p;
        std::string s;
        std::cin >> f >> p >> s; // Read friend ID, popularity, and post content string.

        Post current_post;
        current_post.friend_id = f;
        current_post.popularity = p;
        current_post.content = s;
        // Determine if the friend is special by checking if their ID exists in the set.
        current_post.is_special_friend = special_friends_set.count(f) > 0;

        posts.push_back(current_post); // Add the constructed post to the vector.
    }

    // Sort the `posts` vector using `std::sort` and our custom `comparePosts` function.
    // `std::sort` typically uses an Introsort algorithm, providing O(M log M) time complexity
    // on average and in the worst case, which is efficient for M up to 10^3.
    std::sort(posts.begin(), posts.end(), comparePosts);

    // Iterate through the sorted posts and print the content of each post.
    for (const auto& post : posts) {
        std::cout << post.content << "\n"; // Print content followed by a newline.
    }

    return 0; // Indicate successful execution.
}