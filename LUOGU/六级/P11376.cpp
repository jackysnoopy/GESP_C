#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Station {
    ll p, c;
};

struct Truck {
    ll a, b;
    ll diff;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    ll x;
    cin >> n >> m >> x;

    vector<Station> stations(n);
    for (int i = 0; i < n; ++i) {
        cin >> stations[i].p >> stations[i].c;
    }

    vector<Truck> pos, neg, zero;
    for (int i = 0; i < m; ++i) {
        ll a, b;
        cin >> a >> b;
        if (a > b) pos.push_back({a, b, a - b});
        else if (a < b) neg.push_back({a, b, a - b});
        else zero.push_back({a, b, 0});
    }

    // 正差值：从大到小排序，分配到最小的p
    sort(pos.begin(), pos.end(), [](const Truck& t1, const Truck& t2) {
        return t1.diff > t2.diff;
    });
    
    // 负差值：从小到大排序（即b-a从大到小），分配到最大的p
    sort(neg.begin(), neg.end(), [](const Truck& t1, const Truck& t2) {
        return t1.diff < t2.diff; // 更负的优先（b-a更大）
    });

    sort(stations.begin(), stations.end(), [](const Station& s1, const Station& s2) {
        return s1.p < s2.p;
    });

    ll ans = 0;
    int l = 0, r = n - 1;
    
    // 分配正差值到小p
    int pi = 0;
    while (pi < pos.size()) {
        while (l <= r && stations[l].c == 0) l++;
        if (l > r) break;
        ll cost = 2 * pos[pi].a * stations[l].p + 
                  2 * pos[pi].b * (x - stations[l].p);
        ans += cost;
        stations[l].c--;
        pi++;
    }

    // 分配负差值到大p
    int ni = 0;
    while (ni < neg.size()) {
        while (l <= r && stations[r].c == 0) r--;
        if (l > r) break;
        ll cost = 2 * neg[ni].a * stations[r].p + 
                  2 * neg[ni].b * (x - stations[r].p);
        ans += cost;
        stations[r].c--;
        ni++;
    }

    // diff == 0 的货车
    for (auto& t : zero) {
        ans += 2 * t.a * x;
    }

    cout << ans << endl;
    return 0;
}