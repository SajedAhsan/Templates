#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

// Fast input/output:
// ios::sync_with_stdio(false);
// cin.tie(nullptr);

// Custom sort:
bool compareBySecondThenFirst(const pii& a, const pii& b) {
    if (a.second != b.second) return a.second < b.second;
    return a.first < b.first;
}

int gcdValue(int a, int b) {
    while (b != 0) {
        int remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------- Input ----------
    int n;
    cin >> n;

    vi a(n);
    for (int& x : a) cin >> x;

    // Read test cases:
    // int t;
    // cin >> t;
    // while (t--) solve();

    // Read until EOF:
    // int x;
    // while (cin >> x) { ... }

    // Read a complete line:
    // string line;
    // getline(cin >> ws, line);

    // ---------- vector ----------
    vector<int> v = {3, 1, 2};
    v.push_back(4);
    v.emplace_back(5);
    v.insert(v.begin() + 1, 10);
    v.erase(v.begin());                 // One element
    v.erase(v.begin(), v.begin() + 2);  // Range
    v.pop_back();
    v.front(), v.back(), v[0];
    v.size(), v.empty();
    v.clear();

    sort(v.begin(), v.end());
    sort(v.rbegin(), v.rend());
    reverse(v.begin(), v.end());
    for (int x : v) cout << x << ' ';
    cout << '\n';

    // Remove duplicates from a sorted vector:
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    // ---------- pair ----------
    pair<int, string> p = {1, "one"};
    p.first = 2;
    p.second = "two";
    vector<pii> pairs = {{1, 5}, {2, 3}};
    sort(pairs.begin(), pairs.end(), compareBySecondThenFirst);
    for (const pii& current : pairs) {
        cout << current.first << ' ' << current.second << '\n';
    }

    // ---------- stack, queue, deque ----------
    stack<int> st;
    st.push(1);
    st.emplace(2);
    cout << st.top() << '\n';
    st.pop();
    while (!st.empty()) st.pop();

    queue<int> q;
    q.push(1);
    q.emplace(2);
    cout << q.front() << ' ' << q.back() << '\n';
    q.pop();

    deque<int> dq;
    dq.push_front(1);
    dq.push_back(2);
    dq.pop_front();
    dq.pop_back();

    // ---------- priority_queue ----------
    priority_queue<int> maxHeap;
    maxHeap.push(3);
    maxHeap.emplace(1);
    cout << maxHeap.top() << '\n';
    maxHeap.pop();

    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(3);
    minHeap.push(1);

    // Useful for Dijkstra:
    priority_queue<pii, vector<pii>, greater<pii>> minPairHeap;

    // ---------- set / multiset ----------
    set<int> s = {3, 1, 2};
    s.insert(4);
    s.erase(2);                          // By value
    if (s.find(3) != s.end()) { /* found */ }
    auto it = s.lower_bound(2);          // First element >= 2
    auto jt = s.upper_bound(2);          // First element > 2
    if (it != s.end()) cout << *it << '\n';
    if (!s.empty()) cout << *s.begin() << ' ' << *s.rbegin() << '\n';
    if (jt != s.end()) cout << *jt << '\n';

    multiset<int> ms = {1, 1, 2};
    ms.erase(ms.find(1));                // Erase one occurrence
    ms.erase(1);                         // Erase all occurrences

    // ---------- map / unordered_map ----------
    map<string, int> mp;
    mp["Alice"] = 90;
    mp.emplace("Bob", 80);
    if (mp.find("Alice") != mp.end()) cout << mp["Alice"] << '\n';
    mp.erase("Bob");
    for (const auto& entry : mp) {
        cout << entry.first << ' ' << entry.second << '\n';
    }

    unordered_map<int, int> frequency;
    for (int x : a) ++frequency[x];
    unordered_set<int> distinct(a.begin(), a.end());

    // ---------- string ----------
    string str = "competitive";
    str += " programming";
    str.push_back('!');
    str.pop_back();
    if (str.find("program") != string::npos) { /* found */ }
    string part = str.substr(0, 4);
    sort(str.begin(), str.end());
    reverse(str.begin(), str.end());
    cout << str.size() << ' ' << part << '\n';

    // ---------- fixed arrays ----------
    array<int, 5> fixed = {5, 4, 3, 2, 1};
    sort(fixed.begin(), fixed.end());

    int raw[5] = {5, 4, 3, 2, 1};
    sort(raw, raw + 5);

    // ---------- 2D array ----------
    int rows, cols;
    cin >> rows >> cols;
    vector<vector<int>> grid(rows, vector<int>(cols));
    for (auto& row : grid) {
        for (int& cell : row) cin >> cell;
    }

    // ---------- Graphs ----------
    int vertices, edges;
    cin >> vertices >> edges;

    // Unweighted graph; use vertices + 1 for 1-based vertices.
    vector<vector<int>> graph(vertices + 1);
    for (int i = 0; i < edges; ++i) {
        int u, w;
        cin >> u >> w;
        graph[u].push_back(w);
        graph[w].push_back(u);            // Remove for a directed graph
    }

    // Weighted graph:
    vector<vector<pii>> weightedGraph(vertices + 1);
    // weightedGraph[u].push_back({v, weight});

    // ---------- Common algorithms ----------
    if (!a.empty()) {
        ll sum = accumulate(a.begin(), a.end(), 0LL);
        int minimum = *min_element(a.begin(), a.end());
        int maximum = *max_element(a.begin(), a.end());
        int countOfX = count(a.begin(), a.end(), 1);
        bool exists = find(a.begin(), a.end(), 1) != a.end();
        (void)sum;
        (void)minimum;
        (void)maximum;
        (void)countOfX;
        (void)exists;
    }

    sort(a.begin(), a.end());
    bool present = binary_search(a.begin(), a.end(), 1);
    auto firstAtLeast = lower_bound(a.begin(), a.end(), 1);
    auto firstGreater = upper_bound(a.begin(), a.end(), 1);
    (void)present;
    (void)firstAtLeast;
    (void)firstGreater;

    next_permutation(a.begin(), a.end());
    prev_permutation(a.begin(), a.end());

    int g = gcdValue(12, 18);
    int l = 12 / g * 18;
    (void)g;
    (void)l;

    // Iterator syntax:
    for (auto iter = a.begin(); iter != a.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << '\n';

    return 0;
}

// string s = "10 20 30";

// stringstream ss(s);

// int a, b, c;
// ss >> a >> b >> c;

// cout << a << ' ' << b << ' ' << c << '\n';