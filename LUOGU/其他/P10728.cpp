#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int,int>> swords(n);
    for (int i = 0; i < n; i++) cin >> swords[i].first >> swords[i].second;
    sort(swords.begin(), swords.end());
    int max_b = -1;
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (swords[i].second > max_b) {
            ans++;
            max_b = swords[i].second;
        }
    }
    cout << ans << "\n";
    return 0;
}
