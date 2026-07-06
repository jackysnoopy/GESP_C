#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long s;
    string t;
    cin >> n >> s >> t;
    
    vector<char> st;
    for (char c : t) {
        if (c == 'U' && !st.empty() && st.back() != 'U') {
            st.pop_back();
        } else {
            st.push_back(c);
        }
    }
    
    long long cur = s;
    for (char op : st) {
        if (op == 'L') {
            cur = cur * 2;
        } else if (op == 'R') {
            cur = cur * 2 + 1;
        } else {
            if (cur > 1) cur /= 2;
        }
    }
    
    cout << cur << endl;
    return 0;
}
