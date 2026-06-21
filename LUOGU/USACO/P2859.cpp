#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Cow {
    int start, end, id;
};

struct Stall {
    int end, idx;
    bool operator>(const Stall& other) const {
        return end > other.end;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    vector<Cow> cows(N);
    for (int i = 0; i < N; i++) {
        cin >> cows[i].start >> cows[i].end;
        cows[i].id = i;
    }
    
    sort(cows.begin(), cows.end(), [](const Cow& a, const Cow& b) {
        return a.start < b.start;
    });
    
    priority_queue<Stall, vector<Stall>, greater<Stall>> pq;
    vector<int> ans(N);
    int cnt = 0;
    
    for (const auto& cow : cows) {
        if (!pq.empty() && pq.top().end < cow.start) {
            ans[cow.id] = pq.top().idx;
            pq.pop();
            pq.push({cow.end, ans[cow.id]});
        } else {
            ans[cow.id] = ++cnt;
            pq.push({cow.end, cnt});
        }
    }
    
    cout << cnt << "\n";
    for (int x : ans) cout << x << "\n";
    
    return 0;
}