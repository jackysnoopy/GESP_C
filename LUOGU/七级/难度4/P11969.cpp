#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long t;
    int n;
    cin >> t >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> sorted = a;
    sort(sorted.begin(), sorted.end());

    if (t >= n) {
        for (int i = 0; i < n; i++) {
            if (i) cout << " ";
            cout << sorted[i];
        }
        cout << "\n";
        return 0;
    }

    long long first_moves = (t + 1) / 2;
    long long second_moves = t / 2;

    vector<bool> used(n, false);
    vector<int> result(n, -1);

    for (int pos = 0; pos < n; pos++) {
        if (pos % 2 == 0) {
            for (int j = 0; j < n; j++) {
                if (!used[j] && sorted[j] <= a[pos]) {
                    bool ok = true;
                    int rem = n - pos - 1;
                    long long avail = 0;
                    for (int k = 0; k < n; k++) if (!used[k] && k != j) avail++;
                    if (avail < rem) ok = false;
                    if (ok) {
                        result[pos] = sorted[j];
                        used[j] = true;
                        break;
                    }
                }
            }
            if (result[pos] == -1) {
                for (int j = 0; j < n; j++) {
                    if (!used[j]) {
                        result[pos] = sorted[j];
                        used[j] = true;
                        break;
                    }
                }
            }
        } else {
            for (int j = n - 1; j >= 0; j--) {
                if (!used[j]) {
                    result[pos] = sorted[j];
                    used[j] = true;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << result[i];
    }
    cout << "\n";
    return 0;
}
