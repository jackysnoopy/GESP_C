#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        int n; cin >> n;
        if (n == 0) break;
        vector<long long> h(n + 2, 0);
        for (int i = 1; i <= n; i++) cin >> h[i];
        
        stack<int> st;
        st.push(0);
        long long ans = 0;
        for (int i = 1; i <= n + 1; i++) {
            while (h[i] < h[st.top()]) {
                long long height = h[st.top()]; st.pop();
                long long width = i - st.top() - 1;
                ans = max(ans, height * width);
            }
            st.push(i);
        }
        cout << ans << "\n";
    }
    return 0;
}