#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
typedef long long ll;

const int MAXN = 200010;

ll BIT_qty[MAXN];
ll BIT_cost[MAXN];
int numCoords;

void update(ll BIT[], int idx, ll val) {
    for (; idx < MAXN; idx += idx & (-idx))
        BIT[idx] += val;
}

ll query(ll BIT[], int idx) {
    ll sum = 0;
    for (; idx > 0; idx -= idx & (-idx))
        sum += BIT[idx];
    return sum;
}

int findKth(ll BIT[], ll target) {
    int pos = 0;
    ll sum = 0;
    int pw = 1;
    while (pw < MAXN) pw <<= 1;
    for (; pw > 0; pw >>= 1) {
        if (pos + pw < MAXN && sum + BIT[pos + pw] < target) {
            pos += pw;
            sum += BIT[pos];
        }
    }
    return pos + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n, m, o;
    cin >> n >> m >> o;
    
    vector<tuple<ll, ll, ll>> suppliers(n);
    vector<ll> prices;
    for (int i = 0; i < n; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        suppliers[i] = {a, b, c};
        prices.push_back(a);
    }
    
    sort(prices.begin(), prices.end());
    prices.erase(unique(prices.begin(), prices.end()), prices.end());
    numCoords = prices.size();
    
    auto priceToIdx = [&](ll p) -> int {
        return lower_bound(prices.begin(), prices.end(), p) - prices.begin() + 1;
    };
    
    ll ans = LLONG_MAX;
    ll totalStock = 0;
    
    for (int i = 0; i < n; i++) {
        auto [a, b, c] = suppliers[i];
        int idx = priceToIdx(a);
        
        update(BIT_qty, idx, b);
        update(BIT_cost, idx, a * b);
        totalStock += b;
        
        if (totalStock >= m) {
            int pos = findKth(BIT_qty, m);
            ll qtyBefore = query(BIT_qty, pos - 1);
            ll costBefore = query(BIT_cost, pos - 1);
            ll needed = m - qtyBefore;
            ll cost = costBefore + needed * prices[pos - 1];
            ll total = cost + c * o;
            if (total < ans) ans = total;
        }
    }
    
    if (ans == LLONG_MAX) ans = -1;
    cout << ans << endl;
    return 0;
}
