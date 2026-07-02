#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool isPalindrome(const string& s) {
    int n = s.length();
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - 1 - i]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        vector<char> chars(n);
        vector<long long> lens(n);
        
        for (int i = 0; i < n; i++) {
            cin >> chars[i] >> lens[i];
        }
        
        // 检查是否只有单一字符
        bool allSame = true;
        for (int i = 1; i < n; i++) {
            if (chars[i] != chars[0]) {
                allSame = false;
                break;
            }
        }
        
        // 计算总长度
        long long totalLen = 0;
        for (int i = 0; i < n; i++) {
            totalLen += lens[i];
        }
        
        // 如果总长度为1，且是回文，无解
        if (totalLen == 1) {
            cout << -1 << endl;
            continue;
        }
        
        // 如果全部是相同字符且长度>=2，无解
        if (allSame && totalLen >= 2) {
            cout << -1 << endl;
            continue;
        }
        
        // 如果只有一个字符且长度>=2，无解
        if (n == 1 && lens[0] >= 2) {
            cout << -1 << endl;
            continue;
        }
        
        // 贪心划分
        long long ans = 0;
        long long remaining = totalLen;
        
        // 尽量使用长度为2的非回文子段
        ans = totalLen / 2;
        
        // 检查剩余部分是否需要调整
        if (totalLen % 2 == 1) {
            // 有一个剩余字符，需要检查是否能形成合法划分
            // 如果整个字符串是回文，需要特殊处理
            if (n == 1) {
                // 单一字符，长度>=2，已经处理过
                cout << -1 << endl;
                continue;
            }
            
            // 检查是否整个字符串是回文
            string full = "";
            for (int i = 0; i < n; i++) {
                for (long long j = 0; j < lens[i]; j++) {
                    full += chars[i];
                }
            }
            
            if (isPalindrome(full)) {
                // 整个字符串是回文，需要调整划分
                // 尝试找到一个非回文的划分
                bool found = false;
                
                // 尝试不同的划分方式
                // 策略：找到一个位置，使得划分后的两个部分都不是回文
                for (int i = 0; i < n; i++) {
                    for (long long j = 1; j < lens[i]; j++) {
                        string left = full.substr(0, full.length() - j);
                        string right = full.substr(full.length() - j);
                        
                        if (!isPalindrome(left) && !isPalindrome(right)) {
                            ans = left.length() / 2 + right.length() / 2;
                            found = true;
                            break;
                        }
                    }
                    if (found) break;
                }
                
                if (!found) {
                    // 特殊情况：整个字符串是回文且无法划分
                    cout << -1 << endl;
                    continue;
                }
            }
        }
        
        cout << ans << endl;
    }
    
    return 0;
}
