#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int,int>> cows(n);
    for (int i = 0; i < n; i++) cin >> cows[i].first >> cows[i].second;
    sort(cows.begin(), cows.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second < b.second;
    });
    long long ans = 0;
    multiset<int> chosen;
    for (int i = 0; i < n; i++) {
        int g = cows[i].first, d = cows[i].second;
        if ((int)chosen.size() < d) {
            chosen.insert(g);
            ans += g;
        } else if (!chosen.empty() && *chosen.begin() < g) {
            ans -= *chosen.begin();
            chosen.erase(chosen.begin());
            chosen.insert(g);
            ans += g;
        }
    }
    cout << ans << "\n";
    return 0;
}
