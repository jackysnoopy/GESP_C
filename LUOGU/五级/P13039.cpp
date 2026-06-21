#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        string D;
        cin >> D;
        
        int n = D.size();
        vector<int> digits;
        for (char c : D) {
            digits.push_back(c - '0');
        }
        sort(digits.begin(), digits.end());
        
        long long minDiff = LLONG_MAX;
        
        // 枚举所有可能的子集作为第一个数
        for (int mask = 1; mask < (1 << n) - 1; mask++) {
            vector<int> d1, d2;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    d1.push_back(digits[i]);
                } else {
                    d2.push_back(digits[i]);
                }
            }
            
            // 检查前导零
            if (d1[0] == 0 || d2[0] == 0) {
                continue;
            }
            
            // 枚举 d1 的全排列
            do {
                long long n1 = 0;
                for (int x : d1) {
                    n1 = n1 * 10 + x;
                }
                
                // 枚举 d2 的全排列
                do {
                    long long n2 = 0;
                    for (int x : d2) {
                        n2 = n2 * 10 + x;
                    }
                    
                    minDiff = min(minDiff, abs(n1 - n2));
                    if (minDiff == 0) break;
                } while (next_permutation(d2.begin(), d2.end()));
                if (minDiff == 0) break;
            } while (next_permutation(d1.begin(), d1.end()));
            if (minDiff == 0) break;
        }
        
        cout << "Case #" << t << ": " << minDiff << endl;
    }
    
    return 0;
}
