#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// P1106: 删数问题
// Given a number as string, remove k digits to make the remaining number smallest.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int k;
    cin >> s >> k;
    
    int n = s.size();
    if (k >= n) {
        cout << "0\n";
        return 0;
    }
    
    stack<char> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && k > 0 && st.top() > s[i]) {
            st.pop();
            k--;
        }
        st.push(s[i]);
    }
    while (k > 0 && !st.empty()) { st.pop(); k--; }
    
    string result = "";
    while (!st.empty()) {
        result = st.top() + result;
        st.pop();
    }
    
    // Remove leading zeros
    int start = 0;
    while (start < (int)result.size() && result[start] == '0') start++;
    
    if (start == (int)result.size()) cout << "0\n";
    else cout << result.substr(start) << "\n";
    return 0;
}
