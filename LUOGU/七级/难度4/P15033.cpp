#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> count(n + 1, 0);
    for (int x : a) count[x]++;

    int max_count = *max_element(count.begin(), count.end());
    if (max_count > (n + 1) / 2) {
        cout << -1 << "\n";
        return 0;
    }

    priority_queue<pair<int, int>> pq;
    for (int i = 1; i <= n; i++) {
        if (count[i] > 0) pq.push({count[i], i});
    }

    vector<int> result;
    int prev = -1;

    while (!pq.empty()) {
        auto [cnt1, val1] = pq.top();
        pq.pop();

        if (val1 != prev) {
            result.push_back(val1);
            prev = val1;
            if (cnt1 > 1) pq.push({cnt1 - 1, val1});
        } else {
            if (pq.empty()) {
                cout << -1 << "\n";
                return 0;
            }
            auto [cnt2, val2] = pq.top();
            pq.pop();
            result.push_back(val2);
            prev = val2;
            if (cnt1 > 0) pq.push({cnt1, val1});
            if (cnt2 > 1) pq.push({cnt2 - 1, val2});
        }
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << result[i];
    }
    cout << "\n";

    return 0;
}
