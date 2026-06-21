#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, b, x, y, m;
    cin >> a >> b >> x >> y >> m;
    
    int ans = 0;
    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= b; j++) {
            int total_time = i * x + j * y;
            if (total_time <= m) {
                ans = max(ans, i + j);
            }
        }
    }
    
    cout << ans << endl;
    return 0;
}
