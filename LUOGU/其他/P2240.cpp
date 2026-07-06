#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;
    vector<pair<int, int>> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].first >> items[i].second;
    }

    sort(items.begin(), items.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return (double)a.second / a.first > (double)b.second / b.first;
    });

    double ans = 0;
    int rem = t;
    for (int i = 0; i < n && rem > 0; i++) {
        int w = items[i].first, v = items[i].second;
        if (w <= rem) {
            ans += v;
            rem -= w;
        } else {
            ans += (double)v / w * rem;
            rem = 0;
        }
    }

    printf("%.2f\n", ans);
    return 0;
}
