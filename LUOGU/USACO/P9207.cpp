#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    long long low = -(1LL << (k - 1));
    long long high = (1LL << (k - 1)) - 1;
    vector<int> pos, neg;
    for (int x : a) {
        if (x >= 0) pos.push_back(x);
        else neg.push_back(x);
    }
    sort(pos.begin(), pos.end());
    sort(neg.begin(), neg.end(), greater<int>());
    multiset<int> have;
    int ans = 0;
    for (int x : a) have.insert(x);
    for (int first = 0; first < n; ++first) {
        if (have.find(a[first]) == have.end()) continue;
        have.erase(have.find(a[first]));
        long long sum = a[first];
        int used = 1;
        multiset<int> rem = have;
        while (true) {
            if (sum >= 0) {
                auto it = rem.upper_bound((int)(high - sum));
                if (it == rem.begin()) break;
                --it;
                sum += *it;
                rem.erase(it);
            } else {
                auto it = rem.lower_bound((int)(low - sum));
                if (it == rem.end()) break;
                sum += *it;
                rem.erase(it);
            }
            ++used;
        }
        ans = max(ans, used);
    }
    cout << ans << '\n';
    return 0;
}
