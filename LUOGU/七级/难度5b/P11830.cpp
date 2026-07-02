#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int c, T;
    cin >> c >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        vector<int> l1(n), r1(n), l2(n), r2(n);
        for (int i = 0; i < n; i++) {
            cin >> l1[i] >> r1[i] >> l2[i] >> r2[i];
        }
        
        // 基础实现：收集所有可能的b值
        vector<int> possible_b;
        for (int i = 0; i < n; i++) {
            for (int b = l2[i]; b <= r2[i]; b++) {
                possible_b.push_back(b);
            }
        }
        
        // 去重并排序
        sort(possible_b.begin(), possible_b.end());
        possible_b.erase(unique(possible_b.begin(), possible_b.end()), possible_b.end());
        
        // 对于每个可能的b值，检查是否能成为中位数
        int count = 0;
        for (int x : possible_b) {
            // 简单检查：如果x在至少一个b的范围内，则可能
            bool possible = false;
            for (int i = 0; i < n; i++) {
                if (x >= l2[i] && x <= r2[i]) {
                    possible = true;
                    break;
                }
            }
            if (possible) {
                count++;
            }
        }
        
        cout << count << endl;
    }
    
    return 0;
}