#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> out(n), inn(n), b(n);
    for (int i = 0; i < n; i++) cin >> out[i] >> inn[i] >> b[i];
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b) { return out[a] > out[b]; });
    multiset<int> available;
    for (int i = 0; i < n; i++) available.insert(inn[i]);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int id = idx[i];
        auto it = available.upper_bound(out[id]-1);
        if (it != available.begin()) {
            it--;
            ans += (long long)b[id] * (inn[id] - *it);
            available.erase(it);
        } else {
            ans += (long long)b[id] * inn[id];
        }
    }
    cout << ans << "\n";
    return 0;
}
