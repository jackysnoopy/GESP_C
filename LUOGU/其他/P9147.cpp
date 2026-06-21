#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    int ans = 1;
    int cur = 1;
    for (int i = 1; i < n; ++i) {
        if (a[i] > a[i - 1]) ++cur;
        else cur = 1;
        if (cur > ans) ans = cur;
    }
    int best = ans + 1;
    for (int i = 0; i < n; ++i) {
        int left = 1;
        if (i > 0) {
            if (i + 1 < n && a[i - 1] + 1 < a[i + 1]) {
                int j = i - 1;
                while (j - 1 >= 0 && a[j - 1] < a[j]) --j;
                left = i - j + 1;
            } else {
                int j = i - 1;
                while (j - 1 >= 0 && a[j - 1] < a[j]) --j;
                left = i - j;
            }
        }
        int right = 1;
        if (i < n - 1) {
            if (i > 0 && a[i - 1] + 1 < a[i + 1]) {
                int j = i + 1;
                while (j + 1 < n && a[j] < a[j + 1]) ++j;
                right = j - i;
            } else {
                int j = i + 1;
                while (j + 1 < n && a[j] < a[j + 1]) ++j;
                right = j - i - 1;
            }
        }
        best = max(best, left + right);
    }
    cout << best << '\n';
    return 0;
}
