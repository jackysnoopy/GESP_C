#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> passengers(N);
    for (int i = 0; i < N; i++) {
        cin >> passengers[i].first >> passengers[i].second;
    }

    sort(passengers.begin(), passengers.end());

    long long total = M;
    int cur = 0;

    for (auto& [from, to] : passengers) {
        if (from > cur) {
            total += from - cur;
            cur = from;
        }
        if (to > cur) {
            cur = to;
        } else {
            total += cur - to;
            cur = to;
        }
    }

    total += M - cur;

    cout << total << "\n";
    return 0;
}
