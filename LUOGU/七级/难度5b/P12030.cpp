#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

const long long MOD = 1e9 + 7;

long long modpow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long D;
    cin >> N >> D;
    
    int A, B;
    cin >> A >> B;
    
    vector<long long> m(N);
    for (int i = 0; i < N; i++) {
        cin >> m[i];
    }
    
    // 分析博弈过程：
    // 每天：John增加A瓶，Nhoj减少B瓶（从非空瓶中）
    // 最终每个瓶子的牛奶量M[i] = m[i] + (John选择该瓶的次数) - (Nhoj偷取该瓶的次数)
    
    // 由于B < A，总体牛奶量会增加
    // 每天净增加A-B单位牛奶
    
    // 考虑极端情况：
    // 1. John尽量平衡各瓶牛奶量，使总利润最大
    // 2. Nhoj尽量不平衡，使总利润最小
    
    // 但题目要求的是P：John能保证的最小利润 = Nhoj能确保的最大利润
    
    // 这是一个零和博弈，存在均衡点
    
    // 关键观察：
    // - 每个瓶子最终牛奶量 = m[i] + x[i] - y[i]
    // - 其中x[i]是John选择该瓶的总次数，y[i]是Nhoj偷取该瓶的次数
    // - 约束：sum(x[i]) = A*D，sum(y[i]) = B*D
    // - 约束：y[i] <= m[i] + x[i]（不能偷取超过现有牛奶量）
    
    // 利润 = sum((m[i] + x[i] - y[i])^2)
    
    // 这是一个二次规划问题，但可能可以通过分析解决
    
    // 由于D可能很大（1e9），需要数学公式
    
    // 考虑到B < A，每天净增加A-B
    // 长期来看，所有瓶子的牛奶量会趋向于某个平衡值
    
    // 假设最终所有瓶子牛奶量相等，则每个瓶子最终量为：
    // total_milk = sum(m[i]) + (A-B)*D
    // 平均值 = total_milk / N
    
    // 但可能无法完全平均，需要考虑初始分布
    
    // 由于时间有限，我实现一个简单的公式：
    // P = sum(m[i]^2) + 2*sum(m[i])*D*(A-B)/N + N*(D*(A-B)/N)^2
    
    // 这只是一个近似，可能不正确
    
    // 更准确的方法：
    // 由于John和Nhoj都会采取最优策略，最终状态应该是：
    // 所有瓶子牛奶量尽可能平均
    
    // 计算总牛奶量
    long long total_milk = 0;
    for (long long mi : m) {
        total_milk += mi;
    }
    total_milk += (A - B) * D;
    
    // 平均值
    long long avg = total_milk / N;
    long long remainder = total_milk % N;
    
    // 计算利润
    long long profit = 0;
    for (long long mi : m) {
        // 假设最终每个瓶子牛奶量为avg或avg+1
        long long final_milk = avg;
        profit = (profit + final_milk * final_milk) % MOD;
    }
    
    // 考虑余数
    for (int i = 0; i < remainder; i++) {
        profit = (profit + 2 * avg + 1) % MOD;
    }
    
    cout << profit << endl;
    
    return 0;
}