#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    long long total = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        total += a[i];
    }

    long long max_sum = a[0], cur_max = a[0];
    long long min_sum = a[0], cur_min = a[0];
    for (int i = 1; i < n; i++) {
        cur_max = max(cur_max + a[i], a[i]);
        max_sum = max(max_sum, cur_max);

        cur_min = min(cur_min + a[i], a[i]);
        min_sum = min(min_sum, cur_min);
    }

    if (total == min_sum) {
        cout << max_sum << endl;
    } else {
        cout << max(max_sum, total - min_sum) << endl;
    }

    return 0;
}
