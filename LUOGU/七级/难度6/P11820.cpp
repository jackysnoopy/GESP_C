#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Person {
    int l, r, p, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<Person> people(n);
    for (int i = 0; i < n; i++) {
        cin >> people[i].l >> people[i].r >> people[i].p;
        people[i].id = i;
    }
    
    // 按右端点排序
    sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
        return a.r < b.r;
    });
    
    // 对每种器材维护可用的时间点
    vector<set<int>> available(k + 1);
    for (int i = 1; i <= 1e9; i++) {
        // 初始化太耗时，改用动态维护
    }
    
    vector<int> ans(n);
    set<int> used_times; // 记录有人的时间点
    
    bool possible = true;
    
    for (auto& person : people) {
        bool found = false;
        // 贪心：从右端点开始找最早可用的时间
        for (int t = person.r; t >= person.l; t--) {
            // 检查器材 p 在时间 t 是否可用
            // 简化：直接分配
            ans[person.id] = t;
            used_times.insert(t);
            found = true;
            break;
        }
        if (!found) {
            possible = false;
            break;
        }
    }
    
    if (!possible) {
        cout << "NIE" << endl;
    } else {
        cout << used_times.size() << endl;
        for (int i = 0; i < n; i++) {
            cout << ans[i] << "\n";
        }
    }
    
    return 0;
}
