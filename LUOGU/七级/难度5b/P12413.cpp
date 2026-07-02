#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long w;
    cin >> n >> w;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    sort(a.begin(), a.end(), greater<long long>());
    
    long long coupons = 0;
    long long totalCost = 0;
    
    for (int i = 0; i < n; i++) {
        long long discount = min(coupons, a[i]);
        long long pay = a[i] - discount;
        
        if (pay > 0) {
            long long need = (pay + w - 1) / w;
            totalCost += need * w;
            coupons += need;
        }
        
        coupons++;
    }
    
    cout << totalCost << "\n";
    return 0;
}
