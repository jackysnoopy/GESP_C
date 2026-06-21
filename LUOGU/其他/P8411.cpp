#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned int uint;

inline uint get_next(uint &seed) {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    uint seed;
    cin >> n >> seed;
    vector<uint> a(n + 1);
    vector<int> fa(n + 1, 0);
    for (int i = 1; i <= n; i++) a[i] = get_next(seed);
    for (int i = 2; i <= n; i++) fa[i] = get_next(seed) % (i - 1) + 1;
    long long ans = 0;
    vector<int> order;
    order.push_back(1);
    for (int i = 2; i <= n; i++) {
        order.push_back(i);
    }
    sort(order.begin(), order.end(), [&](int x, int y) { return a[x] < a[y]; });
    long long curMin = a[1];
    ans += curMin;
    for (int i = 0; i < (int)order.size(); i++) {
        int node = order[i];
        if (a[node] < curMin) curMin = a[node];
        ans += curMin;
    }
    cout << ans << "\n";
    return 0;
}
