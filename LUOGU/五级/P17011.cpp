#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    
    // 按降序排序
    sort(v.begin(), v.end(), greater<int>());
    
    int maxSum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (gcd(v[i], v[j]) == 1) {
                maxSum = max(maxSum, v[i] + v[j]);
                break; // 找到第一个互质的就停止，因为已排序
            }
        }
    }
    
    cout << maxSum << endl;
    
    return 0;
}
