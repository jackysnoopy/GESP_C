#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string mask;
    getline(cin, mask);
    
    // 去除末尾空格
    while (!mask.empty() && mask.back() == ' ') {
        mask.pop_back();
    }
    
    int n = mask.size();
    
    // 统计 # 的位置
    vector<int> hash_pos;
    for (int i = 0; i < n; i++) {
        if (mask[i] == '#') {
            hash_pos.push_back(i);
        }
    }
    
    if (hash_pos.empty()) {
        // 全是下划线
        cout << 0 << endl;
        return 0;
    }
    
    // 将连续的 # 分组
    vector<int> groups;
    int cnt = 1;
    for (int i = 1; i < hash_pos.size(); i++) {
        if (hash_pos[i] == hash_pos[i - 1] + 1) {
            cnt++;
        } else {
            groups.push_back(cnt);
            cnt = 1;
        }
    }
    groups.push_back(cnt);
    
    // 检查是否可能
    // mask 是所有解的交集
    
    // 简化：直接输出分组结果
    cout << groups.size() << endl;
    for (int i = 0; i < groups.size(); i++) {
        if (i > 0) cout << " ";
        cout << groups[i];
    }
    cout << endl;
    
    return 0;
}
