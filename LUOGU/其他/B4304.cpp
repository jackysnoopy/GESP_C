#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<pair<int,int>> tasks(n);
    for (int i = 0; i < n; i++) cin >> tasks[i].first >> tasks[i].second;
    // x = start energy needed, y = consume energy
    // x >= y (given)
    // Binary search on initial energy E.
    // Sort by x+y descending (or x descending for same x+y).
    sort(tasks.begin(), tasks.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        if (a.first + a.second != b.first + b.second) return a.first + a.second > b.first + b.second;
        return a.first > b.first;
    });
    long long lo = 0, hi = 0;
    for (auto& t : tasks) hi = max(hi, (long long)(t.first + t.second));
    hi += 1;
    auto check = [&](long long E) -> bool {
        for (auto& t : tasks) {
            if (E < t.first) return false;
            E -= t.second;
            if (E < 0) return false;
        }
        return true;
    };
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
    return 0;
}
