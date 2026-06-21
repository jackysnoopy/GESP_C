#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> a, target;
int maxd;

int h() {
    int cnt = 0;
    for (int i = 0; i + 1 < n; ++i)
        if (a[i + 1] != a[i] + 1) cnt++;
    return (cnt + 1) / 2;
}

void reverse_seg(int l, int r) {
    while (l < r) swap(a[l++], a[r--]);
}

bool dfs(int depth) {
    if (h() == 0) return true;
    if (depth + h() > maxd) return false;
    vector<int> orig = a;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            reverse_seg(i, j);
            for (int k = 0; k < n; ++k) {
                if (k == i || k == j) continue;
                // 把 [i,j] 插入到位置 k
                vector<int> tmp;
                if (k < i) {
                    for (int p = 0; p < k; ++p) tmp.push_back(orig[p]);
                    for (int p = i; p <= j; ++p) tmp.push_back(orig[p]);
                    for (int p = k; p < i; ++p) tmp.push_back(orig[p]);
                    for (int p = j + 1; p < n; ++p) tmp.push_back(orig[p]);
                } else {
                    for (int p = 0; p < i; ++p) tmp.push_back(orig[p]);
                    for (int p = j + 1; p <= k; ++p) tmp.push_back(orig[p]);
                    for (int p = i; p <= j; ++p) tmp.push_back(orig[p]);
                    for (int p = k + 1; p < n; ++p) tmp.push_back(orig[p]);
                }
                a = tmp;
                if (dfs(depth + 1)) return true;
                a = orig;
            }
            a = orig;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        target.resize(n);
        for (int i = 0; i < n; ++i) { cin >> a[i]; target[i] = i + 1; }
        if (a == target) { cout << "0\n"; continue; }
        for (maxd = 1; maxd <= 4; ++maxd) {
            if (dfs(0)) { cout << maxd << '\n'; break; }
        }
        if (maxd > 4) cout << "5 or more\n";
    }
    return 0;
}
