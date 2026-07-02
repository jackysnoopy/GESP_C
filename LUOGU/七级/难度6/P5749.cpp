#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(2*n);
    for (int i = 0; i < 2*n; i++) {
        cin >> a[i];
    }
    vector<int> target_seq;
    stack<int> st;
    for (int i = 0; i < 2*n; i++) {
        int x = a[i];
        if (x < 0) {
            if (!st.empty() && st.top() > 0 && -x == st.top()) {
                int right = st.top();
                st.pop();
                target_seq.push_back(x);
                target_seq.push_back(right);
            } else {
                st.push(x);
            }
        } else {
            if (!st.empty() && st.top() < 0 && x == -st.top()) {
                int left = st.top();
                st.pop();
                target_seq.push_back(left);
                target_seq.push_back(x);
            } else {
                st.push(x);
            }
        }
    }
    map<int, queue<int>> pos_queue;
    for (int i = 0; i < 2*n; i++) {
        pos_queue[target_seq[i]].push(i);
    }
    vector<int> target_pos(2*n);
    for (int i = 0; i < 2*n; i++) {
        int x = a[i];
        target_pos[i] = pos_queue[x].front();
        pos_queue[x].pop();
    }
    vector<int> bit(2*n+1, 0);
    auto update = [&](int idx, int delta) {
        idx++;
        while (idx < (int)bit.size()) {
            bit[idx] += delta;
            idx += idx & -idx;
        }
    };
    auto query = [&](int idx) {
        idx++;
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= idx & -idx;
        }
        return sum;
    };
    long long inversions = 0;
    for (int i = 0; i < 2*n; i++) {
        int t = target_pos[i];
        inversions += i - query(t);
        update(t, 1);
    }
    cout << inversions << "\n";
    return 0;
}