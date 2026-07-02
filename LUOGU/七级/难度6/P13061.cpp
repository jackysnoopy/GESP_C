#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, D;
        cin >> N >> D;
        
        vector<long long> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        
        // 排序
        sort(A.begin(), A.end());
        
        int ans = 0;
        
        if (D == 2) {
            // 检查是否有两片相同大小
            bool found = false;
            for (int i = 0; i + 1 < N; i++) {
                if (A[i] == A[i + 1]) {
                    found = true;
                    break;
                }
            }
            if (!found) ans = 1;
        } else if (D == 3) {
            // 检查是否有三片相同，或两片相同（需要1刀）或都不相同（需要2刀）
            bool three_same = false, two_same = false;
            for (int i = 0; i + 2 < N; i++) {
                if (A[i] == A[i + 1] && A[i + 1] == A[i + 2]) {
                    three_same = true;
                    break;
                }
            }
            if (!three_same) {
                for (int i = 0; i + 1 < N; i++) {
                    if (A[i] == A[i + 1]) {
                        two_same = true;
                        break;
                    }
                }
                if (two_same) ans = 1;
                else ans = 2;
            }
        } else {
            ans = D - 1;
        }
        
        cout << "Case #" << t << ": " << ans << endl;
    }
    
    return 0;
}
