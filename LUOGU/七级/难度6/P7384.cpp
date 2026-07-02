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
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // 贪心：将所有非零数按最高位分组
    // 每组内的数按位或结果等于该组的"代表"
    // 要最小化按位或总和，需要让0单独分组
    
    // 统计每个最高位的非零数个数
    int cnt[64] = {};
    int zeroCnt = 0;
    
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            zeroCnt++;
        } else {
            int hb = 63 - __builtin_clzll(a[i]);
            cnt[hb]++;
        }
    }
    
    // 每个非零数需要单独一组才能最小化按位或
    // 但如果同一组内有多个数，按位或会更大
    // 所以最优方案：每个非零数一组，0可以任意分组
    // 但0可以和非零数同组而不改变结果
    
    int nonZero = n - zeroCnt;
    int groups = nonZero; // 每个非零数一组
    
    // 0可以附加到已有的组中，不会增加组数
    // 所以答案就是非零数的个数
    cout << max(1, groups) << endl;
    return 0;
}
