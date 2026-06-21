#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> count(2 * n + 1, 0);
    int ops = 0;

    for (int i = 0; i < n; i++) {
        count[a[i]]++;
        if (count[a[i]] > k) {
            ops++;
            count[a[i]]--;
            count[a[i] + 1]++;
        }
    }

    cout << ops << "\n";
    return 0;
}
