#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) { cin >> a[i]; sum += a[i]; }
    vector<long long> v(n);
    for (int i = 0; i < n; i++) v[i] = a[i];
    long long curSum = sum;
    for (int iter = 0; iter < 200; iter++) {
        int minI = 0;
        for (int i = 1; i < n; i++) if (v[i] < v[minI]) minI = i;
        long long minV = v[minI];
        long long secMin = minV; int secMinI = minI;
        for (int i = 0; i < n; i++) if (i != minI && (secMinI == minI || v[i] < secMin)) { secMin = v[i]; secMinI = i; }
        long long bestBenefit = -1; int bestI = -1; long long bestNew = -1;
        for (int i = 0; i < n; i++) {
            if (v[i] <= 1) continue;
            long long newVal = v[i] / 2;
            long long reduction = v[i] - newVal;
            long long dblCost = (i != minI) ? minV : secMin;
            long long benefit = reduction - dblCost;
            if (benefit > bestBenefit || (benefit == bestBenefit && benefit >= 0 && newVal < bestNew)) {
                bestBenefit = benefit; bestI = i; bestNew = newVal;
            }
        }
        if (bestBenefit < 0) {
            bool found = false;
            for (int i = 0; i < n; i++) if (v[i] > 1 && v[i] / 2 < minV) { found = true; break; }
            if (!found) break;
            bestBenefit = -1; bestI = -1; bestNew = -1;
            for (int i = 0; i < n; i++) {
                if (v[i] <= 1) continue;
                long long newVal = v[i] / 2;
                if (newVal < minV) {
                    long long reduction = v[i] - newVal;
                    long long dblCost = (i != minI) ? minV : secMin;
                    long long benefit = reduction - dblCost;
                    if (benefit > bestBenefit || (benefit == bestBenefit && newVal < bestNew)) {
                        bestBenefit = benefit; bestI = i; bestNew = newVal;
                    }
                }
            }
            if (bestI == -1) break;
        }
        int dblI = (bestI != minI) ? minI : secMinI;
        long long oldH = v[bestI], oldD = v[dblI];
        v[bestI] = oldH / 2; v[dblI] = oldD * 2;
        curSum = curSum - oldH + v[bestI] - oldD + v[dblI];
    }
    cout << curSum << "\n";
    return 0;
}
