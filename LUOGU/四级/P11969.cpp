#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long t;
    int n;
    cin >> t >> n;
    
    vector<int> a(n);
    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    
    // 如果操作次数足够多，先手可以完全排序
    // 排序一个排列最多需要n-1次交换，先手每次操作排一个错位对
    // 后手每次操作破坏位1，但先手可以修复
    // 当 t >= 2*(n-1) 时先手有足够操作完成排序
    if (t >= 2LL * (n - 1)) {
        for (int i = 1; i <= n; i++) {
            cout << i << (i < n ? " " : "\n");
        }
        return 0;
    }
    
    // t不够大时的博弈分析
    if (t % 2 == 1) {
        // t是奇数：先手最后操作，可以确保位1=正确值
        // 先手第1次操作排第一个错位对，后续操作在位1上和后手拉锯
        // 最终位1=1（先手最后修复），排好的错位对保留
        for (int i = 0; i < n; i++) {
            if (a[i] != i + 1) {
                swap(a[i], a[pos[i + 1]]);
                break;
            }
        }
    } else {
        // t是偶数：后手最后操作，后手会把位1换成最大值n
        // 先手排一个不涉及位1和位n所在位置的错位对
        int max_pos = pos[n];
        int swap_pos = -1;
        for (int i = 1; i < n; i++) {
            if (a[i] != i + 1 && i != max_pos && pos[i + 1] != 0) {
                swap_pos = i;
                break;
            }
        }
        if (swap_pos != -1) {
            swap(a[swap_pos], a[pos[swap_pos + 1]]);
        }
        // 后手把位1换成最大值
        if (max_pos != 0) {
            swap(a[0], a[max_pos]);
        }
    }
    
    for (int i = 0; i < n; i++) {
        cout << a[i] << (i < n - 1 ? " " : "\n");
    }
    
    return 0;
}
