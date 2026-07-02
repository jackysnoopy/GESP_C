#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, p;
    cin >> n >> p;
    
    vector<int> k(p);
    for (int i = 0; i < p; i++) cin >> k[i];
    
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    
    // 按位贪心：从高位到低位，尝试设为1
    long long ans = 0;
    
    for (int bit = 30; bit >= 0; bit--) {
        long long tryAns = ans | (1LL << bit);
        bool ok = true;
        
        // 检查是否可能使表达式结果 >= tryAns
        // 表达式 = (OR of group1) & (OR of group2) & ... & (OR of groupP)
        // 要使结果 >= tryAns，每个子表达式的OR结果在tryAns为1的位上必须为1
        
        // 对于tryAns中每个为1的bit，每个子表达式中至少有一个变量在该bit上可以为1
        for (int grp = 0; grp < p; grp++) {
            int start = 0;
            for (int j = 0; j < grp; j++) start += k[j];
            
            bool grpOk = false;
            for (int j = 0; j < k[grp]; j++) {
                int idx = start + j;
                // 检查变量idx能否在tryAns为1的位上都为1
                // 即对于tryAns中每个为1的bit，a[idx]或b[idx]在该bit上有1
                bool varOk = true;
                for (int bt = 30; bt >= 0; bt--) {
                    if ((tryAns >> bt) & 1) {
                        // 需要这个变量在bt位上可以为1
                        // 即[a[idx], b[idx]]中存在值在bt位上为1
                        long long mask = 1LL << bt;
                        if ((a[idx] & mask) || (b[idx] & mask)) {
                            // 可以
                        } else {
                            // 检查是否所有值在bt位上都是0
                            bool canBeOne = false;
                            for (long long v = a[idx]; v <= b[idx]; v++) {
                                if (v & mask) { canBeOne = true; break; }
                            }
                            if (!canBeOne) { varOk = false; break; }
                        }
                    }
                }
                if (varOk) { grpOk = true; break; }
            }
            if (!grpOk) { ok = false; break; }
        }
        
        if (ok) ans = tryAns;
    }
    
    cout << ans << endl;
    return 0;
}
