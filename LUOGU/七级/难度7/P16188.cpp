#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int seed;
    cin >> seed;
    
    // 2048问题
    // 简化版本：输出基本操作
    
    // 简单策略：交替向左和向下移动
    for (int i = 0; i < 1000; i++) {
        if (i % 2 == 0) {
            cout << "L\n";
        } else {
            cout << "D\n";
        }
    }
    
    return 0;
}
