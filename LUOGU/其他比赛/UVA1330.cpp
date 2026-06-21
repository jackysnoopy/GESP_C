#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vector<int> h(m + 2, 0);
        int ans = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= m; j++) {
                char c; cin >> c;
                if (c == 'F') h[j]++;
                else h[j] = 0;
            }
            
            stack<int> st;
            st.push(0);
            for (int j = 1; j <= m + 1; j++) {
                while (h[j] < h[st.top()]) {
                    int height = h[st.top()]; st.pop();
                    ans = max(ans, height * (j - st.top() - 1));
                }
                st.push(j);
            }
        }
        
        cout << ans * 3 << "\n";
    }
    return 0;
}