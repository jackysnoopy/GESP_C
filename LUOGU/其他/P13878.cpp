#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int target = n / 10;
    vector<vector<int>> buckets(10);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        buckets[a].push_back(b);
    }
    // For each digit, we have some count. We want each to have exactly target.
    // Excess digits: need to change some of their values to deficit digits.
    // Minimize cost = sum of b_i for changed values.
    // For excess digits: sort by b ascending, change cheapest ones.
    // For deficit digits: need to receive changes.
    
    vector<pair<int,int>> excess; // (cost, from_digit)
    vector<int> deficit(10, 0);
    for (int d = 0; d < 10; d++) {
        sort(buckets[d].begin(), buckets[d].end());
        if ((int)buckets[d].size() > target) {
            for (int j = 0; j < (int)buckets[d].size() - target; j++) {
                excess.push_back(make_pair(buckets[d][j], d));
            }
        } else {
            deficit[d] = target - buckets[d].size();
        }
    }
    sort(excess.begin(), excess.end());
    long long ans = 0;
    int idx = 0;
    for (int d = 0; d < 10; d++) {
        for (int j = 0; j < deficit[d]; j++) {
            ans += excess[idx].first;
            idx++;
        }
    }
    cout << ans << endl;
    return 0;
}
