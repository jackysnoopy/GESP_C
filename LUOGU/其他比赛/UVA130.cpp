// UVA130 - Roman Roulette (罗马轮盘赌)
// 约瑟夫问题变种：两人同时移除
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    while (cin >> n >> k && (n || k)) {
        vector<int> v(n);
        for (int i = 0; i < n; i++) v[i] = i + 1;
        int pos = 0;
        while (v.size() > 1) {
            // 从当前位置开始数k个人，移除第k个
            int kill = (pos + k - 1) % v.size();
            v.erase(v.begin() + kill);
            // 被移除的人的下一个人也移除（杀人者也死）
            if (v.size() > 1) {
                int killer = kill % v.size();
                v.erase(v.begin() + killer);
            }
            pos = kill % v.size();
        }
        cout << v[0] << endl;
    }
    return 0;
}
