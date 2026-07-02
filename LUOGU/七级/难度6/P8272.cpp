#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Event {
    int type;
    int t, x, n;
    bool operator<(const Event& other) const {
        return t < other.t || (t == other.t && type < other.type);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    vector<Event> events(N);
    for (int i = 0; i < N; i++) {
        cin >> events[i].type >> events[i].t >> events[i].x >> events[i].n;
    }
    
    sort(events.begin(), events.end());
    
    long long ans = 0;
    priority_queue<int> cows; // max-heap for cow positions
    
    for (const auto& e : events) {
        if (e.type == 1) {
            // Add cows
            for (int i = 0; i < e.n; i++) {
                cows.push(e.x);
            }
        } else {
            // Apples fall - greedy matching
            vector<int> remaining;
            int caught = 0;
            
            while (!cows.empty() && caught < e.n) {
                int cow_pos = cows.top();
                cows.pop();
                
                // Check if cow can reach apple
                if (abs(cow_pos - e.x) <= e.t) {
                    caught++;
                } else {
                    remaining.push_back(cow_pos);
                }
            }
            
            ans += caught;
            
            // Put back unmatched cows
            for (int pos : remaining) {
                cows.push(pos);
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}