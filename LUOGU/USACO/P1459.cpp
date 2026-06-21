#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int cnt[4] = {0, 0, 0, 0};
    for (int i = 0; i < n; i++) cnt[a[i]]++;
    int sorted[4] = {0, cnt[1], cnt[1] + cnt[2], cnt[1] + cnt[2] + cnt[3]};
    int pos1 = 1, pos2 = sorted[1] + 1, pos3 = sorted[2] + 1;
    int swaps = 0;
    for (int i = pos1; i <= sorted[1]; i++) {
        if (a[i - 1] == 2) {
            int j;
            for (j = pos2; j <= sorted[2]; j++) {
                if (a[j - 1] == 1) break;
            }
            swap(a[i - 1], a[j - 1]);
            swaps++;
            pos2 = j + 1;
        } else if (a[i - 1] == 3) {
            int j;
            for (j = pos3; j <= sorted[3]; j++) {
                if (a[j - 1] == 1) break;
            }
            swap(a[i - 1], a[j - 1]);
            swaps++;
            pos3 = j + 1;
        }
    }
    for (int i = pos2; i <= sorted[2]; i++) {
        if (a[i - 1] == 3) {
            int j;
            for (j = pos3; j <= sorted[3]; j++) {
                if (a[j - 1] == 2) break;
            }
            swap(a[i - 1], a[j - 1]);
            swaps++;
            pos3 = j + 1;
        }
    }
    cout << swaps << "\n";
    return 0;
}
