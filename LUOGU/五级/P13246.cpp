#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    
    for (int t = 1; t <= T; t++) {
        int n;
        scanf("%d", &n);
        
        vector<double> naomi(n), ken(n);
        for (int i = 0; i < n; i++) scanf("%lf", &naomi[i]);
        for (int i = 0; i < n; i++) scanf("%lf", &ken[i]);
        
        sort(naomi.begin(), naomi.end());
        sort(ken.begin(), ken.end());
        
        // Deceitful War: Naomi tells Ken a fake weight
        // Optimal: Naomi uses smallest to waste Ken's largest, then wins with remaining
        int dwScore = 0;
        {
            int i = 0, j = 0;
            while (i < n && j < n) {
                if (naomi[i] > ken[j]) {
                    dwScore++;
                    i++;
                    j++;
                } else {
                    i++;
                }
            }
        }
        
        // War: Ken plays optimally (lightest block > Naomi's, or lightest if none)
        // Naomi's optimal: maximize wins against Ken's strategy
        // Standard: Ken wins n - (Naomi's wins)
        // Ken wins = number of Ken's blocks that can beat Naomi's blocks
        // Sort both ascending.
        // Ken wins: greedily match Ken's smallest winning block to Naomi's block
        int warScore = 0;
        {
            int i = 0, j = 0;
            while (i < n && j < n) {
                if (ken[j] > naomi[i]) {
                    // Ken wins this round
                    i++;
                    j++;
                } else {
                    j++;
                }
            }
            warScore = n - i; // i = number of Naomi's blocks that Ken couldn't beat
            // Wait, this counts Ken's wins. Naomi's wins = n - Ken's wins.
            // Actually, i counts how many of Naomi's blocks were beaten by Ken.
            // So Ken wins = i, Naomi wins = n - i.
            warScore = n - i;
        }
        
        printf("Case #%d: %d %d\n", t, dwScore, warScore);
    }
    
    return 0;
}
