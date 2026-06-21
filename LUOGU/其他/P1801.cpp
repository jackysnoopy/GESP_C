#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m, n; cin >> m >> n;
    vector<int> a(m), u(n);
    for (int i = 0; i < m; i++) cin >> a[i];
    for (int i = 0; i < n; i++) { cin >> u[i]; u[i]--; }
    
    priority_queue<int> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;
    
    int i = 0, k = 0;
    for (int idx = 0; idx < m; idx++) {
        max_heap.push(a[idx]);
        
        while (k < n && u[k] == idx) {
            while ((int)max_heap.size() > k + 1) {
                min_heap.push(max_heap.top());
                max_heap.pop();
            }
            while (!min_heap.empty() && max_heap.top() > min_heap.top()) {
                int a = max_heap.top(); max_heap.pop();
                int b = min_heap.top(); min_heap.pop();
                max_heap.push(b); min_heap.push(a);
            }
            cout << max_heap.top() << "\n";
            k++;
        }
    }
    return 0;
}