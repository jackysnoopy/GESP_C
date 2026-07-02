#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long K;
    cin >> n >> K;
    
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    
    // 贪心算法：从左到右，每次选择能放到当前位置的最小数字
    for (int i = 0; i < n && K > 0; i++) {
        // 找到从i开始，能在K次交换内移动到位置i的最小数字
        int min_val = p[i];
        int min_pos = i;
        
        // 检查后面的数字，找到能移动到位置i的最小数字
        for (int j = i + 1; j < n && j - i <= K; j++) {
            if (p[j] < min_val) {
                min_val = p[j];
                min_pos = j;
            }
        }
        
        // 如果找到了更小的数字，就把它移动到位置i
        if (min_pos != i) {
            // 计算需要多少次交换
            long long swaps = min_pos - i;
            if (swaps <= K) {
                // 执行交换，将min_pos位置的数字移动到位置i
                int temp = p[min_pos];
                for (int j = min_pos; j > i; j--) {
                    p[j] = p[j - 1];
                }
                p[i] = temp;
                K -= swaps;
            }
        }
    }
    
    // 输出结果
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << p[i];
    }
    cout << endl;
    
    return 0;
}