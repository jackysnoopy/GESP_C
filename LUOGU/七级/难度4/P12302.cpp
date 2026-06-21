#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<long long, long long>> activities(n);
    for (int i = 0; i < n; i++) {
        cin >> activities[i].first >> activities[i].second;
    }

    vector<pair<long long, long long>> sleeps;
    long long last_end = 0;

    for (int i = 0; i < n; i++) {
        long long gap = activities[i].first - last_end;
        if (gap > 0) {
            long long k = gap / 2;
            if (k > 0) {
                sleeps.push_back({last_end, last_end + k});
                last_end = last_end + k;
            }
        }
        last_end = activities[i].second;
    }

    cout << sleeps.size() << "\n";
    for (auto& [s, t] : sleeps) {
        cout << s << " " << t << "\n";
    }

    return 0;
}
