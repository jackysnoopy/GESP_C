// UVA138 - Street Numbers (街道号码)
// 寻找n < m使得1+2+...+n = (n+1)+(n+2)+...+m
// 等价于Pell方程，前10对解
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 使用Pell方程求解
    // 方程：m^2 - n^2 = m + n，即(m-n)(m+n) = m+n
    // 简化后得到：2m^2 - 2mn - n^2 - n = 0
    // 或者使用递推关系求解
    vector<pair<long long, long long>> results;
    // 使用Pell方程的基本解递推
    long long x = 1, y = 1;
    while (results.size() < 10) {
        // 寻找满足条件的n和m
        // 使用已知的Pell方程解的递推公式
        results.push_back({x, y});
        // 递推下一个解
        long long new_x = 3 * x + 4 * y + 1;
        long long new_y = 2 * x + 3 * y + 1;
        x = new_x;
        y = new_y;
    }
    // 输出前10对解
    for (int i = 0; i < 10; i++) {
        cout << results[i].first << " " << results[i].second << "\n";
    }
    return 0;
}
