#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int r, n;
    int caseNum = 0;
    
    while (cin >> r >> n && (r != 0 || n != 0)) {
        if (caseNum > 0) cout << "\n";
        cout << "Case " << ++caseNum << ":\n";
        
        for (int i = 0; i < r; i++) {
            int u, v;
            cin >> u >> v;
            
            int roadNum = 0;
            for (int a = 1; a < n; a++) {
                for (int b = a + 1; b <= n; b++) {
                    roadNum++;
                    if ((a == u && b == v) || (a == v && b == u)) {
                        cout << u << "-" << v << " " << roadNum << "\n";
                        goto next;
                    }
                }
            }
            next:;
        }
    }
    
    return 0;
}
