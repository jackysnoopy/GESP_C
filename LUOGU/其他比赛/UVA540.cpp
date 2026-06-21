#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t, cas = 0;
    while (cin >> t && t) {
        cout << "Scenario #" << ++cas << "\n";
        map<int, int> team_of;
        for (int i = 0; i < t; i++) {
            int n; cin >> n;
            while (n--) { int x; cin >> x; team_of[x] = i; }
        }
        
        queue<int> main_q;
        vector<queue<int>> team_q(t);
        vector<bool> in_main(t, false);
        
        string op;
        while (cin >> op && op != "STOP") {
            if (op == "ENQUEUE") {
                int x; cin >> x;
                int tid = team_of[x];
                team_q[tid].push(x);
                if (!in_main[tid]) {
                    main_q.push(tid);
                    in_main[tid] = true;
                }
            } else {
                int tid = main_q.front();
                cout << team_q[tid].front() << "\n";
                team_q[tid].pop();
                if (team_q[tid].empty()) {
                    main_q.pop();
                    in_main[tid] = false;
                }
            }
        }
        cout << "\n";
    }
    return 0;
}