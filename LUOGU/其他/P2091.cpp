#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> vol(n), mass(n);
    for (int i = 0; i < n; i++) cin >> vol[i];
    for (int i = 0; i < n; i++) cin >> mass[i];
    vector<int> pos(n+1);
    for (int i = 0; i < n; i++) pos[vol[i]] = i;
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int cur = pos[i];
        int target = i - 1;
        if (cur != target) {
            int maxMassIdx = cur;
            for (int j = cur; j >= target; j--) {
                if (mass[pos[j+1]] > mass[pos[maxMassIdx]]) maxMassIdx = j+1;
            }
            int swapIdx = maxMassIdx;
            ans += mass[cur] + mass[swapIdx];
            swap(vol[cur], vol[swapIdx]);
            swap(mass[cur], mass[swapIdx]);
            pos[vol[cur]] = cur;
            pos[vol[swapIdx]] = swapIdx;
        }
    }
    cout << ans << endl;
    return 0;
}