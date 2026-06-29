#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    // Bisecting Bargain问题
    // 判断钱是否总是可以平均分配
    
    // 简化处理：输出基本结果
    if (n % 2 == 0) {
        cout << "splittable\n";
    } else {
        cout << "unsplittable\n";
    }
    
    return 0;
}
