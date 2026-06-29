#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        // Dividing Sequence问题
        // 将序列分成两个子序列B和C，使得B<=C（字典序）
        // 且C的字典序最小
        
        // 简单贪心：选择最小的元素作为C
        vector<int> C;
        int min_val = *min_element(a.begin(), a.end());
        
        for (int i = 0; i < n; i++) {
            if (a[i] == min_val) {
                C.push_back(a[i]);
                break;
            }
        }
        
        cout << C.size() << "\n";
        for (int i = 0; i < C.size(); i++) {
            if (i > 0) cout << " ";
            cout << C[i];
        }
        cout << "\n";
    }
    
    return 0;
}
