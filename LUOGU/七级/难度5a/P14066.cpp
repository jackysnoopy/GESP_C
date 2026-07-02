#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // 基础实现：简单检查
    // 统计每组的最小需求
    int min1 = 0, min2 = 0, min3 = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > min1) min1 = a[i];
        if (a[i] > min2) min2 = a[i];
        if (a[i] > min3) min3 = a[i];
    }
    
    // 简单检查：如果每组的需求都满足
    if (min1 <= n && min2 <= n && min3 <= n) {
        cout << "YES" << endl;
        // 简单分组：按顺序分配
        string s(n, '1');
        for (int i = n/3; i < 2*n/3; i++) {
            s[i] = '2';
        }
        for (int i = 2*n/3; i < n; i++) {
            s[i] = '3';
        }
        cout << s << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}