#include <iostream>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    map<int, int> marks;
    long long total = 0;
    
    for (int i = 0; i < n; i++) {
        int x, a;
        cin >> x >> a;
        marks[x] += a;
        total += a;
        
        if (total <= k) {
            cout << m << "\n";
        } else {
            int left = 0, right = m;
            long long cur = total;
            
            for (auto it = marks.begin(); it != marks.end(); ++it) {
                if (cur - it->second > k) {
                    cur -= it->second;
                    left = it->first + 1;
                } else {
                    break;
                }
            }
            
            cout << right - left << "\n";
        }
    }
    
    return 0;
}
