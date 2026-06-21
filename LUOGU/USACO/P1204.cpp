#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    int max_t = 0;
    vector<pair<int,int>> seg(N);
    for (int i = 0; i < N; i++) {
        cin >> seg[i].first >> seg[i].second;
        max_t = max(max_t, seg[i].second);
    }
    vector<int> d(max_t + 2, 0);
    for (auto &s : seg) { d[s.first]++; d[s.second]--; }
    int cur = 0, milk_max = 0, idle_max = 0, milk_s = -1, idle_s = -1;
    for (int i = 0; i <= max_t; i++) {
        cur += d[i];
        if (cur > 0) {
            if (milk_s == -1) milk_s = i;
            if (idle_s != -1) { idle_max = max(idle_max, i - idle_s); idle_s = -1; }
        } else {
            if (idle_s == -1) idle_s = i;
            if (milk_s != -1) { milk_max = max(milk_max, i - milk_s); milk_s = -1; }
        }
    }
    if (milk_s != -1) milk_max = max(milk_max, max_t - milk_s);
    cout << milk_max << " " << idle_max << "\n";
    return 0;
}
