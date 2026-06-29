#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.length() / 3;
    
    // 计算当前权值
    int weight = 1;
    for (int i = 1; i < (int)s.length(); i++) {
        if (s[i] != s[i - 1]) weight++;
    }
    
    if (weight >= 2 * n) {
        cout << 0 << endl;
        return 0;
    }
    
    vector<int> ops;
    
    // 尝试在每个三元组中制造差异
    for (int i = 0; i < n && (int)ops.size() < n; i++) {
        int pos = i * 3;
        if (s[pos] == s[pos + 1] && s[pos + 1] == s[pos + 2]) {
            // 三个相同，翻转中间两个
            ops.push_back(pos + 1);
            s[pos + 1] = (s[pos + 1] == '0') ? '1' : '0';
            s[pos + 2] = (s[pos + 2] == '0') ? '1' : '0';
        }
    }
    
    cout << ops.size() << endl;
    for (int i = 0; i < (int)ops.size(); i++) {
        cout << ops[i] << (i + 1 == (int)ops.size() ? '\n' : ' ');
    }
    
    return 0;
}
