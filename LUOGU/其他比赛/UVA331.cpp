#include <iostream>
#include <algorithm>
using namespace std;

int a[20], n;

int countSwaps(int left, int right) {
    if (left >= right) return 0;
    int mid = (left + right) / 2;
    int cnt = countSwaps(left, mid) + countSwaps(mid + 1, right);
    int temp[20];
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
            cnt += (mid - i + 1);
        }
    }
    while (i <= mid) temp[k++] = a[i++];
    while (j <= right) temp[k++] = a[j++];
    for (i = left, k = 0; i <= right; i++, k++) a[i] = temp[k];
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cas = 0;
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) cin >> a[i];
        int original[20];
        for (int i = 0; i < n; i++) original[i] = a[i];

        int ans = 0;
        for (int mask = 1; mask < (1 << n); mask++) {
            int b[20], m = 0;
            for (int i = 0; i < n; i++)
                if (mask & (1 << i)) b[m++] = original[i];
            int cnt = 0;
            for (int i = 0; i < m; i++)
                for (int j = i + 1; j < m; j++)
                    if (b[i] > b[j]) cnt++;
            for (int i = 0; i < m; i++)
                for (int j = 0; j < m; j++)
                    if (b[i] == b[j] && i != j) { cnt = -1; break; }
            if (cnt < 0) continue;
            ans = max(ans, cnt);
        }

        cout << "There are " << ans << " swap(s).\n";
    }
    return 0;
}
