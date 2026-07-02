#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int Q;
    cin >> Q;
    
    vector<long long> k(Q);
    for (int i = 0; i < Q; i++) {
        cin >> k[i];
    }
    
    // Precompute drop numbers
    vector<long long> drop_numbers;
    for (long long y = 1; y <= 1000000; y++) {
        // Calculate f(y)
        long long x = y;
        long long result = 1;
        
        while (x > 0) {
            int digit = x % 10;
            result *= (digit + 1);
            x /= 10;
        }
        
        drop_numbers.push_back(result);
    }
    
    sort(drop_numbers.begin(), drop_numbers.end());
    drop_numbers.erase(unique(drop_numbers.begin(), drop_numbers.end()), drop_numbers.end());
    
    for (int i = 0; i < Q; i++) {
        if (k[i] <= drop_numbers.size()) {
            cout << drop_numbers[k[i] - 1];
        } else {
            cout << -1;
        }
        if (i + 1 < Q) cout << " ";
    }
    cout << endl;
    
    return 0;
}