#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, p, v;
    cin >> n >> p >> v;
    
    long long ans = 1e18;
    
    for (long long groups = 1; groups * groups <= n; groups++) {
        long long people = (n + groups - 1) / groups;
        long long time = people * p + groups * v;
        ans = min(ans, time);
        
        people = n / groups;
        if (people > 0) {
            time = people * p + groups * v;
            ans = min(ans, time);
        }
    }
    
    cout << ans << endl;
    return 0;
}