#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

const int MAXN = 100005;

int total[256];
int left_cnt[256];

int main() {
    string s;
    cin >> s;
    int n = s.size();
    
    memset(total, 0, sizeof(total));
    for (char c : s) {
        total[(int)c]++;
    }
    
    memset(left_cnt, 0, sizeof(left_cnt));
    stack<int> st;
    string ans;
    
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        int idx = (int)c;
        if (left_cnt[idx] < total[idx] / 2) {
            ans += '(';
            left_cnt[idx]++;
            st.push(i);
        } else {
            if (st.empty() || s[st.top()] != c) {
                cout << -1 << endl;
                return 0;
            }
            ans += ')';
            st.pop();
        }
    }
    
    if (!st.empty()) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    
    return 0;
}