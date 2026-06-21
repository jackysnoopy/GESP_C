#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long k; cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Simulation: for each operation, find movable elements and add k.
    // Movable: if only this element +k (others unchanged), rank doesn't change.
    // Rank = count of strictly greater elements + 1.
    // Element a[i] is movable if: rank(a[i] + k) == rank(a[i]) (with others unchanged).
    // rank(a[i]) = count of a[j] > a[i], j != i, plus count of a[j] == a[i], j != i (for ties?).
    // Actually, rank = count of strictly greater + 1.
    // After adding k to a[i]: new rank = count of a[j] > a[i]+k (j!=i) + 1.
    // Same rank means: count of a[j] > a[i]+k == count of a[j] > a[i] (j!=i).
    // This means no a[j] satisfies a[i] < a[j] <= a[i]+k.
    
    vector<long long> counts(n, 0);
    for (int iter = 0; iter < 1000000; iter++) {
        vector<int> movable;
        for (int i = 0; i < n; i++) {
            int cnt_greater = 0;
            for (int j = 0; j < n; j++) {
                if (j != i && a[j] > a[i]) cnt_greater++;
            }
            int cnt_greater_new = 0;
            for (int j = 0; j < n; j++) {
                if (j != i && a[j] > a[i] + k) cnt_greater_new++;
            }
            if (cnt_greater == cnt_greater_new) movable.push_back(i);
        }
        if (movable.empty()) break;
        for (int i : movable) {
            a[i] += k;
            counts[i]++;
        }
    }
    for (int i = 0; i < n; i++) cout << counts[i] << " ";
    cout << "\n";
    return 0;
}
