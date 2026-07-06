#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> farmers(m);
    for (int i = 0; i < m; i++) {
        cin >> farmers[i].first >> farmers[i].second;
    }
    sort(farmers.begin(), farmers.end());
    long long cost = 0;
    int need = n;
    for (int i = 0; i < m && need > 0; i++) {
        int take = min(need, farmers[i].second);
        cost += (long long)take * farmers[i].first;
        need -= take;
    }
    cout << cost << endl;
    return 0;
}
