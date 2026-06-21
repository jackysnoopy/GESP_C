#include <iostream>
#include <set>
#include <queue>
#include <vector>
using namespace std;

struct Free { int l, r; };
struct Task { int t, m, p; };
struct Event { int end, l, r; bool operator>(const Event& o) const { return end > o.end; } };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    set<pair<int,int>> free_mem;
    free_mem.insert({0, n - 1});
    
    priority_queue<Event, vector<Event>, greater<Event>> events;
    queue<Task> waiting;
    int total_wait = 0, finished = 0;
    
    while (true) {
        int t, m, p; cin >> t >> m >> p;
        if (t == 0 && m == 0 && p == 0) break;
        
        // 释放到时间的进程
        while (!events.empty() && events.top().end <= t) {
            auto e = events.top(); events.pop();
            free_mem.insert({e.l, e.r});
        }
        
        // 尝试分配
        Task task = {t, m, p};
        bool allocated = false;
        for (auto it = free_mem.begin(); it != free_mem.end(); ++it) {
            if (it->second - it->first + 1 >= m) {
                int l = it->first, r = l + m - 1;
                free_mem.erase(it);
                if (r < it->second) free_mem.insert({r + 1, it->second});
                events.push({t + p, l, r});
                allocated = true;
                break;
            }
        }
        
        if (!allocated) {
            waiting.push(task);
        }
    }
    
    // 处理剩余事件
    while (!events.empty()) {
        auto e = events.top(); events.pop();
        free_mem.insert({e.l, e.r});
        // 尝试分配等待队列
        while (!waiting.empty()) {
            auto task = waiting.front();
            bool ok = false;
            for (auto it = free_mem.begin(); it != free_mem.end(); ++it) {
                if (it->second - it->first + 1 >= task.m) {
                    int l = it->first, r = l + task.m - 1;
                    free_mem.erase(it);
                    if (r < it->second) free_mem.insert({r + 1, it->second});
                    events.push({e.end + task.p, l, r});
                    total_wait = max(total_wait, e.end);
                    waiting.pop();
                    ok = true; break;
                }
            }
            if (!ok) break;
        }
    }
    
    while (!waiting.empty()) {
        cout << waiting.front().t << " " << waiting.front().m << " " << waiting.front().p << "\n";
        waiting.pop();
    }
    
    return 0;
}