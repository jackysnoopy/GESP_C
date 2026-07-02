#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        vector<int> coeff(n + 1);
        for (int i = n; i >= 0; i--) {
            cin >> coeff[i];
        }
        
        vector<int> factors;
        for (int p = 1; p <= abs(coeff[0]); p++) {
            if (coeff[0] % p == 0) {
                int val = 0;
                for (int i = n; i >= 0; i--) {
                    val = val * p + coeff[i];
                }
                if (val == 0) {
                    factors.push_back(p);
                }
                val = 0;
                for (int i = n; i >= 0; i--) {
                    val = val * (-p) + coeff[i];
                }
                if (val == 0) {
                    factors.push_back(-p);
                }
            }
        }
        
        sort(factors.begin(), factors.end());
        factors.erase(unique(factors.begin(), factors.end()), factors.end());
        
        if (factors.empty()) {
            cout << "No integer roots" << endl;
        } else {
            for (int i = 0; i < factors.size(); i++) {
                cout << factors[i] << (i == factors.size() - 1 ? "\n" : " ");
            }
        }
    }
    return 0;
}
