#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double EPS = 1e-9;

int main() {
    int n;
    while (cin >> n && n) {
        vector<double> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += v[i];
        }
        
        double avg = sum / n;
        double variance = 0;
        for (int i = 0; i < n; i++) {
            variance += (v[i] - avg) * (v[i] - avg);
        }
        variance /= n;
        
        double stddev = sqrt(variance);
        cout << stddev << "\n";
    }
    return 0;
}
