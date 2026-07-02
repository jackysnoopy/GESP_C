#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<long long> fib;
    fib.push_back(1);
    fib.push_back(2);
    while (fib.back() < 1e17) {
        fib.push_back(fib[fib.size()-1] + fib[fib.size()-2]);
    }
    
    int p;
    cin >> p;
    while (p--) {
        long long k;
        cin >> k;
        
        int ans = 0;
        for (int i = fib.size() - 1; i >= 0 && k > 0; i--) {
            if (k >= fib[i]) {
                k -= fib[i];
                ans++;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
