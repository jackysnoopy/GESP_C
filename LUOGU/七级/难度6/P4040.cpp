#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll m, f; int n;
    cin >> m >> f >> n;
    vector<pair<ll,ll>> food(n);
    for (int i = 0; i < n; i++) cin >> food[i].first >> food[i].second;
    sort(food.begin(), food.end());
    ll ans = 0;
    ll money = m;
    int last = 0;
    for (int i = 0; i < n; i++) {
        if (money < food[i].first + f) break;
        money -= food[i].first + f;
        ans += food[i].second + 1;
        last = i;
    }
    cout << ans << endl;
    return 0;
}