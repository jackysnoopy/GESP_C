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
    
    int q;
    cin >> q;
    
    while (q--) {
        long long qi;
        cin >> qi;
        
        // 检查total是否能被qi整除
        if (total % qi != 0) {
            cout << -1 << "\n";
            continue;
        }
        
        // 将序列分割成若干段，每段和为qi
        // 操作次数 = n - 段数
        // 合并操作：相邻两段合为一段
        // 分割操作：一段分为两段
        
        // 贪心：尽量让每段和为qi
        long long need = total / qi;
        int segments = 0;
        long long curSum = 0;
        bool possible = true;
        
        for (int i = 0; i < n; i++) {
            curSum += a[i];
            if (curSum == qi) {
                segments++;
                curSum = 0;
            } else if (curSum > qi) {
                possible = false;
                break;
            }
        }
        
        if (!possible || curSum != 0) {
            cout << -1 << "\n";
        } else {
            cout << n - segments << "\n";
        }
    }
    
    return 0;
}
