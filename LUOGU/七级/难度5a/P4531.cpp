#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
long long s;
vector<int> formula, cartoon;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m >> s;
    formula.resize(n);
    cartoon.resize(m);
    
    for (int i = 0; i < n; i++) cin >> formula[i];
    for (int i = 0; i < m; i++) cin >> cartoon[i];
    
    sort(formula.rbegin(), formula.rend());
    sort(cartoon.rbegin(), cartoon.rend());
    
    int maxCount = 0;
    long long minArea = s;
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i + j == 0) continue;
            if (i > n || j > m) continue;
            
            long long area = 0;
            if (i > 0) area += (long long)formula[i-1] * 50;
            if (j > 0) area += (long long)cartoon[j-1] * 50;
            
            if (area <= s) {
                if (i + j > maxCount) {
                    maxCount = i + j;
                    minArea = area;
                } else if (i + j == maxCount) {
                    minArea = min(minArea, area);
                }
            }
        }
    }
    
    cout << maxCount << " " << minArea << endl;
    return 0;
}