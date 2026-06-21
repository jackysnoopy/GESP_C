#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> depart(n), return_day(n);
    for (int i = 0; i < n; i++) cin >> depart[i] >> return_day[i];
    // Hasty Santa: visit houses while families are away.
    // Each house i: family departs on depart[i], returns on return_day[i].
    // Can visit at most m houses per day.
    // Visit window: [depart[i], return_day[i]-1] or [depart[i]+1, return_day[i]]?
    // Without full problem, implement greedy interval scheduling.
    
    // Sort by return day
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return return_day[a] < return_day[b];
    });
    
    // Greedy: visit as many as possible
    int ans = 0;
    int lastDay = 0;
    for (int i = 0; i < n; i++) {
        int h = idx[i];
        if (depart[h] >= lastDay + 1) {
            ans++;
            lastDay = depart[h];
        }
    }
    cout << ans << endl;
    return 0;
}
