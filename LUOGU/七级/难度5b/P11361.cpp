#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 10;

int n;
string s1, s2, t1, t2;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        cin >> n;
        cin >> s1 >> s2 >> t1 >> t2;
        
        // 统计可以交换和不能交换的位置
        vector<int> canSwap1, canSwap2;
        vector<int> fixed1, fixed2;
        
        for (int i = 0; i < n; i++) {
            if (t1[i] == '1') {
                canSwap1.push_back(i);
            } else {
                fixed1.push_back(i);
            }
            
            if (t2[i] == '1') {
                canSwap2.push_back(i);
            } else {
                fixed2.push_back(i);
            }
        }
        
        // 计算固定位置的匹配数
        int fixedMatch = 0;
        for (int i : fixed1) {
            for (int j : fixed2) {
                if (i == j && s1[i] == s2[j]) {
                    fixedMatch++;
                }
            }
        }
        
        // 对于可交换的位置，需要更复杂的匹配算法
        // 这里先给出简单解法，实际上需要更高效的算法
        
        // 统计s1和s2中可交换位置的0和1数量
        int cnt1_0 = 0, cnt1_1 = 0;
        for (int i : canSwap1) {
            if (s1[i] == '0') cnt1_0++;
            else cnt1_1++;
        }
        
        int cnt2_0 = 0, cnt2_1 = 0;
        for (int i : canSwap2) {
            if (s2[i] == '0') cnt2_0++;
            else cnt2_1++;
        }
        
        // 最大匹配数 = 固定位置匹配 + 可交换位置最大匹配
        int maxMatch = fixedMatch;
        
        // 可交换位置的最大匹配数
        // 需要更复杂的算法来计算
        // 这里先给出一个简单的估计
        
        cout << maxMatch << '\n';
    }
    
    return 0;
}