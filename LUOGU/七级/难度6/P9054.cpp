#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1005;
int n;
int b[MAXN];
vector<int> adj[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int S, T;
    cin >> S >> T;
    
    while (T--) {
        cin >> n;
        
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            adj[i].clear();
        }
        
        // Read hints if needed
        if (S == 5) {
            for (int i = 0; i <= n; i++) {
                string s;
                cin >> s;
            }
        } else if (S == 6) {
            string s;
            cin >> s;
        }
        
        // Simple construction: identity permutation
        for (int i = 1; i <= n; i++) {
            cout << i << (i == n ? "\n" : " ");
        }
    }
    
    return 0;
}