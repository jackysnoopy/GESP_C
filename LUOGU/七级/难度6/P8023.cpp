#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; i++) cin >> b[i];
    
    // 贪心：每次选剩余串中字典序较小的第一个元素
    int i = 0, j = 0;
    vector<int> result;
    
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            result.push_back(a[i++]);
        } else if (a[i] > b[j]) {
            result.push_back(b[j++]);
        } else {
            // 相等时，比较剩余部分
            bool takeA = false;
            for (int x = i, y = j; x < n && y < m; x++, y++) {
                if (a[x] < b[y]) { takeA = true; break; }
                if (a[x] > b[y]) { takeA = false; break; }
            }
            if (takeA) result.push_back(a[i++]);
            else result.push_back(b[j++]);
        }
    }
    while (i < n) result.push_back(a[i++]);
    while (j < m) result.push_back(b[j++]);
    
    for (int k = 0; k < (int)result.size(); k++) {
        if (k) cout << " ";
        cout << result[k];
    }
    cout << "\n";
    return 0;
}
