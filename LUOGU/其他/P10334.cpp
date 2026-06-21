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
    vector<long long> t(n), a(n);
    for (int i = 0; i < n; i++) cin >> t[i];
    for (int i = 0; i < n; i++) cin >> a[i];
    priority_queue<long long> available;
    long long total_volume = 0;
    int person_idx = 0;
    available.push(a[0]);
    total_volume += a[0];
    person_idx = 1;
    long long cur_time = t[0] + 1;
    while (person_idx < n) {
        long long gap = t[person_idx] - cur_time;
        for (long long i = 0; i < gap && i < n; i++) {
            available.push(1);
            total_volume += 1;
        }
        cur_time = t[person_idx];
        if (available.empty()) {
            available.push(a[person_idx]);
            total_volume += a[person_idx];
        } else {
            long long max_cup = available.top();
            available.pop();
            if (max_cup >= a[person_idx]) {
                available.push(1);
                total_volume += 1;
            } else {
                available.push(max_cup);
                available.push(a[person_idx]);
                total_volume += a[person_idx];
            }
        }
        person_idx++;
    }
    cout << total_volume << "\n";
    return 0;
}
