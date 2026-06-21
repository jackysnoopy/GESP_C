#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Item {
    int time, level;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<Item> mach(n), task(m);
        for (int i = 0; i < n; i++) cin >> mach[i].time >> mach[i].level;
        for (int i = 0; i < m; i++) cin >> task[i].time >> task[i].level;
        
        sort(mach.begin(), mach.end(), [](const Item& a, const Item& b) {
            if (a.time != b.time) return a.time > b.time;
            return a.level > b.level;
        });
        sort(task.begin(), task.end(), [](const Item& a, const Item& b) {
            if (a.time != b.time) return a.time > b.time;
            return a.level > b.level;
        });
        
        multiset<int> levels;
        long long profit = 0;
        int cnt = 0, j = 0;
        
        for (int i = 0; i < n; i++) {
            while (j < m && task[j].time >= mach[i].time) {
                levels.insert(task[j].level);
                j++;
            }
            auto it = levels.lower_bound(mach[i].level);
            if (it != levels.end()) {
                cnt++;
                profit += 500 * mach[i].time + 2 * mach[i].level;
                levels.erase(it);
            }
        }
        
        cout << cnt << " " << profit << "\n";
    }
    return 0;
}