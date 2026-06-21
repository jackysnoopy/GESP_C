#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, D, M;
    cin >> N >> D >> M;
    vector<int> tasks(M);
    for (int i = 0; i < M; i++) cin >> tasks[i];
    sort(tasks.begin(), tasks.end());
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < M; i++) {
        if ((int)pq.size() < tasks[i]) {
            pq.push(tasks[i] + D);
        } else {
            int top = pq.top();
            if (top >= tasks[i]) {
                pq.pop();
                pq.push(tasks[i] + D);
            }
        }
    }
    cout << pq.size() << "\n";
    return 0;
}
