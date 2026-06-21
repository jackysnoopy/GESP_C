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
    vector<pair<int,int>> items(n);
    for (int i = 0; i < n; i++) cin >> items[i].first >> items[i].second;
    // Sort by value/weight ratio
    sort(items.begin(), items.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return (double)a.first / a.second > (double)b.first / b.second;
    });
    double ans = 0;
    int rem = t;
    for (int i = 0; i < n && rem > 0; i++) {
        if (items[i].second <= rem) {
            ans += items[i].first;
            rem -= items[i].second;
        } else {
            ans += (double)items[i].first / items[i].second * rem;
            rem = 0;
        }
    }
    printf("%.2f\n", ans);
    return 0;
}
