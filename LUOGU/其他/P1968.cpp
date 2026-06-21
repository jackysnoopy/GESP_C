#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<double> rates(n);
    for (int i = 0; i < n; i++) cin >> rates[i];
    // Start with 100 USD
    // Each day: can exchange all USD to EUR (rate) or all EUR to USD (1/rate)
    // Maximize USD at end
    double usd = 100.0, eur = 0.0;
    for (int i = 0; i < n; i++) {
        double newUsd = max(usd, eur / rates[i]);
        double newEur = max(eur, usd * rates[i]);
        usd = newUsd;
        eur = newEur;
    }
    printf("%.2f\n", usd);
    return 0;
}
