#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long A, B;
    cin >> N >> A >> B;

    vector<pair<long long, long long>> items(N);
    for (int i = 0; i < N; i++) {
        cin >> items[i].second >> items[i].first;
    }
    sort(items.begin(), items.end());

    vector<long long> cnt(N);
    vector<long long> id(N);
    for (int i = 0; i < N; i++) {
        id[i] = items[i].first;
        cnt[i] = items[i].second;
    }

    long long ans = 0;

    auto solve = [&](long long target) {
        if (target == 0) return;
        vector<bool> used(N, false);
        vector<pair<long long, int>> order;
        for (int i = 0; i < N; i++) order.push_back({id[i], i});
        sort(order.begin(), order.end());

        for (int i = 0; i < N; i++) {
            if (used[i]) continue;
            long long need = target - id[i];
            if (need < 0) continue;
            auto it = lower_bound(order.begin(), order.end(), make_pair(need, -1));
            if (it != order.end() && it->first == need) {
                int j = it->second;
                if (j == i) {
                    auto it2 = upper_bound(order.begin(), order.end(), make_pair(need, N));
                    if (it2 != order.end() && it2->first == need) j = it2->second;
                    else continue;
                }
                if (used[j]) continue;
                long long pairs = min(cnt[i], cnt[j]);
                if (i == j) pairs = cnt[i] / 2;
                ans += pairs;
                used[i] = true;
                used[j] = true;
            }
        }
    };

    if (A == B) {
        solve(A);
    } else {
        vector<int> order2(N);
        for (int i = 0; i < N; i++) order2[i] = i;
        sort(order2.begin(), order2.end(), [&](int x, int y) { return id[x] < id[y]; });

        vector<long long> rem = cnt;
        vector<bool> used(N, false);

        for (int i = 0; i < N; i++) {
            int idx = order2[i];
            if (used[idx]) continue;
            long long needA = A - id[idx];
            long long needB = B - id[idx];

            for (long long need : {needA, needB}) {
                if (need < 0 || need == id[idx]) continue;
                auto it = lower_bound(order2.begin() + i + 1, order2.end(), need,
                    [&](int x, long long v) { return id[x] < v; });
                if (it != order2.end() && id[*it] == need && !used[*it]) {
                    long long pairs = min(rem[idx], rem[*it]);
                    ans += pairs;
                    used[idx] = true;
                    used[*it] = true;
                    break;
                }
            }
        }

        for (int i = 0; i < N; i++) {
            if (used[i]) continue;
            for (long long target : {A, B}) {
                long long need = target - id[i];
                if (need < 0 || need == id[i]) continue;
                auto it = lower_bound(order2.begin(), order2.end(), need,
                    [&](int x, long long v) { return id[x] < v; });
                if (it != order2.end() && id[*it] == need && !used[*it]) {
                    long long pairs = min(rem[i], rem[*it]);
                    ans += pairs;
                    used[i] = true;
                    used[*it] = true;
                    break;
                }
            }
        }

        for (int i = 0; i < N; i++) {
            if (used[i]) continue;
            for (long long target : {A, B}) {
                if (target % 2 == 0 && id[i] == target / 2) {
                    ans += rem[i] / 2;
                    used[i] = true;
                    break;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
