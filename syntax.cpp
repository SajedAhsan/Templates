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

ll modPower(ll base, ll exponent, ll mod) {
    ll result = 1 % mod;
    base %= mod;
    while (exponent > 0) {
        if (exponent & 1) result = result * base % mod;
        base = base * base % mod;
        exponent >>= 1;
    }
    return result;
}

ll floorDiv(ll numerator, ll denominator) {
    assert(denominator != 0);
    ll quotient = numerator / denominator;
    ll remainder = numerator % denominator;
    if (remainder != 0 && ((remainder < 0) != (denominator < 0))) --quotient;
    return quotient;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------- Input ----------
    int n;
    cin >> n;

    vi a(n);
    for (int& x : a) cin >> x;

    // ---------- bit manipulation ----------
    int bits = 29;                         // Binary: 11101
    int setBit = bits | (1 << 2);          // Set bit 2
    int clearedBit = bits & ~(1 << 2);     // Clear bit 2
    int toggledBit = bits ^ (1 << 2);      // Toggle bit 2
    bool bitIsSet = (bits & (1 << 2)) != 0;
    int lowestSetBit = bits & -bits;

    // GCC/Clang built-ins:
    int numberOfBits = __builtin_popcount(static_cast<unsigned int>(bits));
    int longLongBits = __builtin_popcountll(1LL << 40);
    int leadingZeros = __builtin_clz(static_cast<unsigned int>(bits)); // bits != 0
    int trailingZeros = __builtin_ctz(static_cast<unsigned int>(bits)); // bits != 0
    int oddParity = __builtin_parity(static_cast<unsigned int>(bits));
    // C++20 alternatives: std::popcount(bits), std::countl_zero(bits),
    // std::countr_zero(bits), and std::has_single_bit(bits).
    (void)setBit;
    (void)clearedBit;
    (void)toggledBit;
    (void)bitIsSet;
    (void)lowestSetBit;
    (void)numberOfBits;
    (void)longLongBits;
    (void)leadingZeros;
    (void)trailingZeros;
    (void)oddParity;

    // ---------- mathematics ----------
    const double PI = acos(-1.0);
    double absoluteValue = abs(-12.5);
    double squareRoot = sqrt(16.0);
    double power = pow(2.0, 10.0);
    double logarithm = log(100.0);
    double roundedUp = ceil(2.3);
    double roundedDown = floor(2.7);
    double rounded = round(2.5);
    int smaller = min(3, 5);
    int larger = max(3, 5);
    int greatestCommonDivisor = gcdValue(12, 18);
    int leastCommonMultiple = 12 / greatestCommonDivisor * 18;
    (void)PI;
    (void)absoluteValue;
    (void)squareRoot;
    (void)power;
    (void)logarithm;
    (void)roundedUp;
    (void)roundedDown;
    (void)rounded;
    (void)smaller;
    (void)larger;
    (void)greatestCommonDivisor;
    (void)leastCommonMultiple;

    // ---------- functions, lambdas, tuples ----------
    auto square = [](ll x) { return x * x; };
    auto byAbsoluteValue = [](int x, int y) {
        if (abs(x) != abs(y)) return abs(x) < abs(y);
        return x < y;
    };
    vector<int> lambdaValues = {-3, 1, -2};
    sort(lambdaValues.begin(), lambdaValues.end(), byAbsoluteValue);
    function<int(int)> factorial = [&](int x) {
        return x <= 1 ? 1 : x * factorial(x - 1);
    };
    tuple<int, string, double> record = {7, "team", 9.5};
    int id = get<0>(record);
    string name = get<1>(record);
    double score = get<2>(record);
    // C++17 shorthand: auto [id, name, score] = record;
    (void)square(4);
    (void)factorial(5);
    (void)id;
    (void)name;
    (void)score;

    // ---------- useful standard algorithms ----------
    vector<int> values = {1, 2, 2, 4, 5};
    vector<int> prefix(values.size() + 1);
    partial_sum(values.begin(), values.end(), prefix.begin() + 1);
    vector<int> differences(values.size());
    adjacent_difference(values.begin(), values.end(), differences.begin());
    iota(values.begin(), values.end(), 1);
    rotate(values.begin(), values.begin() + 2, values.end());
    nth_element(values.begin(), values.begin() + 2, values.end());
    bool allPositive = all_of(values.begin(), values.end(), [](int x) {
        return x > 0;
    });
    bool hasEven = any_of(values.begin(), values.end(), [](int x) {
        return x % 2 == 0;
    });
    bool noneNegative = none_of(values.begin(), values.end(), [](int x) {
        return x < 0;
    });
    values.erase(remove_if(values.begin(), values.end(), [](int x) {
        return x % 2 == 0;
    }), values.end());
    vector<int> transformed(values.size());
    transform(values.begin(), values.end(), transformed.begin(),
              [](int x) { return x * 2; });
    (void)allPositive;
    (void)hasEven;
    (void)noneNegative;

    // Merge/intersection require sorted ranges.
    vector<int> first = {1, 2, 4};
    vector<int> second = {2, 3, 4};
    vector<int> merged, intersection, unionValues;
    set_union(first.begin(), first.end(), second.begin(), second.end(),
              back_inserter(unionValues));
    set_intersection(first.begin(), first.end(), second.begin(), second.end(),
                     back_inserter(intersection));
    merge(first.begin(), first.end(), second.begin(), second.end(),
          back_inserter(merged));

    // ---------- bitset ----------
    bitset<8> mask(string("10110010"));
    mask.set(0);
    mask.reset(1);
    mask.flip(2);
    bool bitsetValue = mask.test(3);
    size_t setBits = mask.count();
    string binary = mask.to_string();
    (void)bitsetValue;
    (void)setBits;
    (void)binary;

    // ---------- randomization ----------
    mt19937 rng(static_cast<unsigned int>(
        chrono::steady_clock::now().time_since_epoch().count()));
    shuffle(values.begin(), values.end(), rng);
    uniform_int_distribution<int> randomInt(1, 100);
    int randomValue = randomInt(rng);
    (void)randomValue;

    // ---------- modular arithmetic ----------
    const ll MOD = 1'000'000'007LL;
    ll modularPower = modPower(2, 10, MOD);
    ll modularInverse = modPower(5, MOD - 2, MOD); // MOD must be prime.
    ll modularDivision = 10 * modularInverse % MOD;
    (void)modularPower;
    (void)modularDivision;

    // For products beyond 64-bit, use __int128 where supported:
    // __int128 wideProduct = static_cast<__int128>(1'000'000'000LL)
    //                      * 1'000'000'000LL;
    (void)floorDiv(-7, 3);

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

    // 2D prefix sums (use rows + 1 and cols + 1 to simplify boundaries).
    vector<vector<ll>> prefixGrid(rows + 1, vector<ll>(cols + 1));
    for (int row = 1; row <= rows; ++row) {
        for (int col = 1; col <= cols; ++col) {
            prefixGrid[row][col] = grid[row - 1][col - 1]
                + prefixGrid[row - 1][col]
                + prefixGrid[row][col - 1]
                - prefixGrid[row - 1][col - 1];
        }
    }
    auto rectangleSum = [&](int top, int left, int bottom, int right) {
        return prefixGrid[bottom][right] - prefixGrid[top - 1][right]
             - prefixGrid[bottom][left - 1] + prefixGrid[top - 1][left - 1];
    };
    if (rows > 0 && cols > 0) {
        ll oneCell = rectangleSum(1, 1, 1, 1);
        (void)oneCell;
    }

    // Coordinate compression.
    vector<int> compressed = a;
    sort(compressed.begin(), compressed.end());
    compressed.erase(unique(compressed.begin(), compressed.end()),
                     compressed.end());
    auto compressedIndex = [&](int value) {
        return lower_bound(compressed.begin(), compressed.end(), value)
             - compressed.begin();
    };
    if (!a.empty()) {
        int index = compressedIndex(a[0]);
        (void)index;
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

    // ---------- graph traversal ----------
    vector<int> distance(vertices + 1, -1);
    queue<int> bfsQueue;
    int source = 1;
    if (source <= vertices) {
        distance[source] = 0;
        bfsQueue.push(source);
    }
    while (!bfsQueue.empty()) {
        int node = bfsQueue.front();
        bfsQueue.pop();
        for (int next : graph[node]) {
            if (distance[next] == -1) {
                distance[next] = distance[node] + 1;
                bfsQueue.push(next);
            }
        }
    }

    vector<bool> visited(vertices + 1, false);
    function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        for (int next : graph[node]) {
            if (!visited[next]) dfs(next);
        }
    };
    if (source <= vertices) dfs(source);

    // Grid directions: four-neighbor traversal.
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};
    for (int direction = 0; direction < 4; ++direction) {
        int nextRow = 0 + dr[direction];
        int nextCol = 0 + dc[direction];
        (void)nextRow;
        (void)nextCol;
    }

    // ---------- disjoint set union ----------
    vector<int> parent(vertices + 1), componentSize(vertices + 1, 1);
    iota(parent.begin(), parent.end(), 0);
    function<int(int)> findRoot = [&](int node) {
        return parent[node] == node ? node : parent[node] = findRoot(parent[node]);
    };
    auto unite = [&](int left, int right) {
        left = findRoot(left);
        right = findRoot(right);
        if (left == right) return;
        if (componentSize[left] < componentSize[right]) swap(left, right);
        parent[right] = left;
        componentSize[left] += componentSize[right];
    };
    if (vertices >= 2) unite(1, 2);

    // ---------- Fenwick tree / Binary Indexed Tree ----------
    vector<ll> fenwick(n + 1);
    auto add = [&](int index, ll value) {
        for (; index <= n; index += index & -index) fenwick[index] += value;
    };
    auto prefixSum = [&](int index) {
        ll result = 0;
        for (; index > 0; index -= index & -index) result += fenwick[index];
        return result;
    };
    if (n > 0) {
        add(1, a[0]);
        ll rangeSum = prefixSum(n) - prefixSum(0);
        (void)rangeSum;
    }

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