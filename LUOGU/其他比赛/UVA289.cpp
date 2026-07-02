#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        vector<double> costs(n);
        double total = 0;
        for (int i = 0; i < n; i++) {
            cin >> costs[i];
            total += costs[i];
        }
        
        double avg = total / n;
        double up = 0, down = 0;
        for (int i = 0; i < n; i++) {
            int rounded = (int)(costs[i] * 100 + 0.5) / 100 * 100;
            double diff = costs[i] - rounded / 100.0;
            if (diff > 0) up += diff;
            else down -= diff;
        }
        
        printf("$%.2f\n", max(up, down));
    }
    return 0;
}
