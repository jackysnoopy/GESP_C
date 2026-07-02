#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int maxStamps;
    while (cin >> maxStamps && maxStamps != 0) {
        int n;
        cin >> n;
        
        int best[12];
        int bestStamps = 0;
        int bestSize = 0;
        
        for (int s = 1; s <= n; s++) {
            int cover[201] = {0};
            cover[0] = 0;
            for (int v = 1; v <= 200; v++) cover[v] = 999;
            
            vector<int> stamps = {s};
            for (int k = 1; k < maxStamps; k++) {
                int bestVal = -1, bestReach = cover[0];
                for (int v = s + 1; v <= 200; v++) {
                    if (cover[v] < 999 && v > bestVal) {
                        bestVal = v;
                    }
                }
                if (bestVal == -1) break;
                
                int maxCov = 0;
                bestVal = stamps.back() + 1;
                for (int v = stamps.back() + 1; v <= 200; v++) {
                    int tmp[201];
                    for (int i = 0; i <= 200; i++) tmp[i] = cover[i];
                    for (int j = 1; j <= maxStamps - k; j++) {
                        for (int p = 200; p >= v; p--) {
                            if (tmp[p - v] + j < tmp[p])
                                tmp[p] = tmp[p - v] + j;
                        }
                    }
                    int reach = 0;
                    for (int p = 1; p <= n; p++) {
                        if (tmp[p] <= maxStamps - k) reach = p;
                        else break;
                    }
                    if (reach > maxCov) {
                        maxCov = reach;
                        bestVal = v;
                    }
                }
                stamps.push_back(bestVal);
            }
            
            int cover2[201];
            for (int i = 0; i <= 200; i++) cover2[i] = 999;
            cover2[0] = 0;
            for (int s_val : stamps) {
                for (int j = s_val; j <= 200; j++) {
                    if (cover2[j - s_val] + 1 < cover2[j])
                        cover2[j] = cover2[j - s_val] + 1;
                }
            }
            
            int reach = 0;
            for (int p = 1; p <= n; p++) {
                if (cover2[p] <= maxStamps) reach = p;
                else break;
            }
            
            if (reach > bestStamps || (reach == bestStamps && stamps.size() < bestSize)) {
                bestStamps = reach;
                bestSize = stamps.size();
                for (int i = 0; i < (int)stamps.size(); i++)
                    best[i] = stamps[i];
            }
        }
        
        cout << "max coverage = " << bestStamps << " : ";
        for (int i = bestSize - 1; i >= 0; i--) {
            cout << best[i];
            if (i > 0) cout << " ";
        }
        cout << endl;
    }
    return 0;
}
