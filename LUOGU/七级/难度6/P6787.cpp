#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n), x(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> x[i];

    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return a[i] < a[j];
    });

    vector<pair<int,int>> pairs(n / 2);
    for (int i = 0; i < n / 2; i++) {
        pairs[i] = {idx[i], idx[n - 1 - i]};
    }

    for (int i = 0; i < n / 2; i++) {
        int u = pairs[i].first;
        int v = pairs[i].second;
        if (x[u] == v + 1 || x[v] == u + 1) {
            bool fixed = false;
            for (int j = i + 1; j < n / 2; j++) {
                int u2 = pairs[j].first;
                int v2 = pairs[j].second;
                if (x[u] != v2 + 1 && x[v2] != u + 1 &&
                    x[u2] != v + 1 && x[v] != u2 + 1) {
                    pairs[i] = {u, v2};
                    pairs[j] = {u2, v};
                    fixed = true;
                    break;
                }
                if (x[u] != u2 + 1 && x[u2] != u + 1 &&
                    x[v] != v2 + 1 && x[v2] != v + 1) {
                    pairs[i] = {u, u2};
                    pairs[j] = {v, v2};
                    fixed = true;
                    break;
                }
            }
            if (!fixed) {
                cout << -1 << "\n";
                return 0;
            }
        }
    }

    vector<int> pairMin(n / 2);
    for (int i = 0; i < n / 2; i++) {
        pairMin[i] = min(a[pairs[i].first], a[pairs[i].second]);
    }

    vector<int> order(n / 2);
    for (int i = 0; i < n / 2; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int i, int j) {
        return pairMin[i] > pairMin[j];
    });

    long long total = 0;
    for (int i = 0; i < n / 2; i++) {
        total += (long long)pairMin[order[i]] * (i + 1);
    }

    cout << total << "\n";
    for (int i = 0; i < n / 2; i++) {
        cout << pairs[order[i]].first + 1 << " " << pairs[order[i]].second + 1 << "\n";
    }
    return 0;
}
