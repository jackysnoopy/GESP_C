#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> zombies(n);
    for (int i = 0; i < n; i++) {
        cin >> zombies[i].first >> zombies[i].second;
    }
    sort(zombies.begin(), zombies.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second < b.second;
    });
    int ans = 0;
    int j = 0;
    vector<int> available;
    for (int i = 0; i < n; i++) {
        while (j < n && zombies[j].first < zombies[i].second) {
            available.push_back(zombies[j].first);
            j++;
        }
        if (available.empty()) {
            ans++;
        } else {
            available.pop_back();
        }
    }
    cout << ans << "\n";
    return 0;
}
