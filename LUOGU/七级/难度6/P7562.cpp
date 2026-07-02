#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Event {
    int l, r, id;
    bool operator<(const Event& other) const {
        return l < other.l;
    }
};

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    vector<Event> events(n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &events[i].l, &events[i].r);
        events[i].id = i + 1;
    }
    
    sort(events.begin(), events.end());
    
    // 贪心：每次选择字典序最小的合法方案
    vector<int> result;
    multiset<int> available_end;
    int event_idx = 0;
    
    for (int i = 0; i < k; i++) {
        // 添加所有开始时间 <= 当前最早结束时间的事件
        int earliest_end = available_end.empty() ? events[event_idx].l : *available_end.begin();
        
        while (event_idx < n && events[event_idx].l <= earliest_end) {
            available_end.insert(events[event_idx].r);
            event_idx++;
        }
        
        if (available_end.empty()) {
            printf("-1\n");
            return 0;
        }
        
        // 选择字典序最小的事件
        int best_idx = -1;
        for (int j = 0; j < n; j++) {
            if (events[j].id > 0 && events[j].l >= (result.empty() ? 0 : events[result.back()-1].r)) {
                bool valid = true;
                for (int r : result) {
                    if (events[r-1].r > events[j].l) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    best_idx = j;
                    break;
                }
            }
        }
        
        if (best_idx == -1) {
            printf("-1\n");
            return 0;
        }
        
        result.push_back(best_idx + 1);
    }
    
    for (int id : result) {
        printf("%d\n", id);
    }
    
    return 0;
}