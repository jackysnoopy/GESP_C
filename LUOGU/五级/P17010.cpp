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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // 按降序排序，大的数字放前面
    sort(a.begin(), a.end(), greater<int>());
    
    long long total = 0;
    long long prefixSum = 0;
    
    for (int i = 0; i < n; i++) {
        prefixSum += a[i];
        total += prefixSum;
    }
    
    cout << total << endl;
    
    return 0;
}
