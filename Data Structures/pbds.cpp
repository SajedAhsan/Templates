
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// Ordered set: unique elements, sorted automatically
template <typename T>
using ordered_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

// Ordered set with duplicates using (value, unique_id)
template <typename T>
using ordered_multiset = tree<
    pair<T, int>,
    null_type,
    less<pair<T, int>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ordered_set<int> s;

    // Insert
    s.insert(10);
    s.insert(20);
    s.insert(30);
    s.insert(20);  // Ignored: duplicate

    // Size and empty
    cout << s.size() << '\n';
    cout << s.empty() << '\n';

    // Print all elements in ascending order
    for (int x : s) {
        cout << x << ' ';
    }
    cout << '\n';

    // Find
    if (s.find(20) != s.end()) {
        cout << "Found\n";
    }

    cout << (s.find(20) != s.end()) << '\n';    

    // Erase by value
    s.erase(20);

    // Order statistics
    s.insert(20);
    cout << *s.find_by_order(0) << '\n'; // Smallest element
    cout << *s.find_by_order(1) << '\n'; // Second smallest

    // Number of elements strictly smaller than x
    cout << s.order_of_key(25) << '\n';

    // Lower bound: first element >= x
    auto it1 = s.lower_bound(25);
    if (it1 != s.end()) {
        cout << *it1 << '\n';
    }

    // Upper bound: first element > x
    auto it2 = s.upper_bound(20);
    if (it2 != s.end()) {
        cout << *it2 << '\n';
    }

    // Erase smallest / largest
    if (!s.empty()) {
        s.erase(s.begin());
        s.erase(prev(s.end()));
    }

    // Clear
    s.clear();

    return 0;
}
