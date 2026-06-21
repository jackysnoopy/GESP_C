#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int,int>> jobs(n);
    for (int i = 0; i < n; i++) cin >> jobs[i].second >> jobs[i].first;
    sort(jobs.begin(), jobs.end());
    int cur = 0;
    for (int i = 0; i < (int)jobs.size(); i++) {
        cur += jobs[i].first;
        if (cur > jobs[i].second) { cout << -1 << "\n"; return 0; }
    }
    cout << cur << "\n";
    return 0;
}
