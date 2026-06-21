#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, L;
        cin >> N >> L;
        
        vector<int> C(L);
        int sum = 0;
        for (int i = 0; i < L; i++) {
            cin >> C[i];
            sum += C[i];
        }
        
        int remaining = N - sum;
        
        // 计算每个语言的当前百分比和四舍五入后的值
        int totalRounded = 0;
        for (int i = 0; i < L; i++) {
            double percent = (double)C[i] * 100.0 / N;
            int rounded = (int)(percent + 0.5);
            totalRounded += rounded;
        }
        
        // 尝试将剩余的人分配给语言，使得四舍五入后的值增加
        // 策略：优先分配给那些小数部分接近 0.5 的语言
        
        vector<int> current = C;
        int maxTotal = totalRounded;
        
        for (int i = 0; i < remaining; i++) {
            // 找到能增加最多四舍五入值的语言
            int bestLang = -1;
            int bestGain = -1;
            
            // 检查已有的语言
            for (int j = 0; j < L; j++) {
                double newPercent = (double)(current[j] + 1) * 100.0 / N;
                int newRounded = (int)(newPercent + 0.5);
                double oldPercent = (double)current[j] * 100.0 / N;
                int oldRounded = (int)(oldPercent + 0.5);
                int gain = newRounded - oldRounded;
                
                if (gain > bestGain) {
                    bestGain = gain;
                    bestLang = j;
                }
            }
            
            // 检查创建新语言
            double newPercent = 100.0 / N;
            int newRounded = (int)(newPercent + 0.5);
            if (newRounded > bestGain) {
                bestGain = newRounded;
                bestLang = L;
            }
            
            if (bestLang == L) {
                current.push_back(1);
                L++;
                maxTotal += bestGain;
            } else if (bestGain > 0) {
                current[bestLang]++;
                maxTotal += bestGain;
            }
        }
        
        cout << "Case #" << t << ": " << maxTotal << endl;
    }
    
    return 0;
}
