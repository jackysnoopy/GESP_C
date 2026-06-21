#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        int N;
        double V, X;
        scanf("%d %lf %lf", &N, &V, &X);
        
        vector<double> R(N), C(N);
        for (int i = 0; i < N; i++) scanf("%lf %lf", &R[i], &C[i]);
        
        // Check for exact match
        bool found = false;
        for (int i = 0; i < N; i++) {
            if (fabs(C[i] - X) < 1e-9) {
                printf("Case #%d: %.10f\n", t, V / R[i]);
                found = true;
                break;
            }
        }
        if (found) continue;
        
        vector<int> hot, cold;
        for (int i = 0; i < N; i++) {
            if (C[i] > X + 1e-9) hot.push_back(i);
            else if (C[i] < X - 1e-9) cold.push_back(i);
        }
        
        if (hot.empty() || cold.empty()) {
            printf("Case #%d: IMPOSSIBLE\n", t);
            continue;
        }
        
        // Combine all cold sources
        double R_c_total = 0, RC_c_sum = 0;
        for (int c : cold) {
            R_c_total += R[c];
            RC_c_sum += R[c] * C[c];
        }
        double C_c_eff = RC_c_sum / R_c_total;
        
        // Combine all hot sources
        double R_h_total = 0, RC_h_sum = 0;
        for (int h : hot) {
            R_h_total += R[h];
            RC_h_sum += R[h] * C[h];
        }
        double C_h_eff = RC_h_sum / R_h_total;
        
        double bestTime = 1e18;
        
        // Approach 1: each hot source with all cold sources
        for (int h : hot) {
            double dC = C[h] - C_c_eff;
            if (dC < 1e-12) continue;
            double t_h = V * (X - C_c_eff) / (R[h] * dC);
            double t_c = V * (C[h] - X) / (R_c_total * dC);
            double time = max(t_h, t_c);
            if (time < bestTime) bestTime = time;
        }
        
        // Approach 2: all hot sources with each cold source
        for (int c : cold) {
            double dC = C_h_eff - C[c];
            if (dC < 1e-12) continue;
            double t_h = V * (X - C[c]) / (R_h_total * dC);
            double t_c = V * (C_h_eff - X) / (R[c] * dC);
            double time = max(t_h, t_c);
            if (time < bestTime) bestTime = time;
        }
        
        // Approach 3: all hot with all cold
        {
            double dC = C_h_eff - C_c_eff;
            if (dC > 1e-12) {
                double t_h = V * (X - C_c_eff) / (R_h_total * dC);
                double t_c = V * (C_h_eff - X) / (R_c_total * dC);
                double time = max(t_h, t_c);
                if (time < bestTime) bestTime = time;
            }
        }
        
        printf("Case #%d: %.10f\n", t, bestTime);
    }
    return 0;
}
