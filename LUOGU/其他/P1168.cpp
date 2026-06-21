#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    priority_queue<int> max_heap;  // 大根堆，放较小的一半
    priority_queue<int, vector<int>, greater<int>> min_heap;  // 小根堆
    
    for (int i = 1; i <= N; i++) {
        int x;
        cin >> x;
        
        if (max_heap.empty() || x <= max_heap.top())
            max_heap.push(x);
        else
            min_heap.push(x);
        
        // 调整平衡
        if (max_heap.size() > min_heap.size() + 1) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        }
        if (min_heap.size() > max_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
        
        if (i % 2 == 1)
            cout << max_heap.top() << "\n";
    }
    
    return 0;
}