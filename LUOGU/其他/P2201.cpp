#include <iostream>
#include <stack>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int q; cin >> q;
    stack<int> left, right;
    vector<int> pre(1, 0), max_pre(1, INT_MIN);
    int idx = 0;
    
    while (q--) {
        char op; cin >> op;
        if (op == 'I') {
            int x; cin >> x;
            left.push(x);
            idx++;
            int sum = pre.back() + x;
            pre.push_back(sum);
            max_pre.push_back(max(max_pre.back(), sum));
        } else if (op == 'D') {
            if (!left.empty()) {
                left.pop();
                pre.pop_back();
                max_pre.pop_back();
                idx--;
            }
        } else if (op == 'L') {
            if (!left.empty()) {
                right.push(left.top());
                left.pop();
                pre.pop_back();
                max_pre.pop_back();
                idx--;
            }
        } else if (op == 'R') {
            if (!right.empty()) {
                left.push(right.top());
                right.pop();
                idx++;
                int sum = pre.back() + left.top();
                pre.push_back(sum);
                max_pre.push_back(max(max_pre.back(), sum));
            }
        } else if (op == 'Q') {
            int k; cin >> k;
            cout << max_pre[k] << "\n";
        }
    }
    return 0;
}