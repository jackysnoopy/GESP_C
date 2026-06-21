#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string breed;
    cin >> breed;
    vector<int> e(n);
    for (int i = 0; i < n; i++) cin >> e[i];
    // For each pair (i,j), check if they can be leaders
    // Leader i must cover all of breed i OR the other leader j
    // Leader j must cover all of breed j OR the other leader i
    // Compute: for each cow, what's the rightmost position of its breed?
    // And what's the position of the other potential leader?
    // 
    // For cow i to be a valid leader:
    // Either e[i] >= last_of_breed[i], or e[i] >= some position of other leader
    // 
    // Approach: for each cow i, compute last_g[i] = last Guernsey position >= i
    // and last_h[i] = last Holstein position >= i
    // Then for pair (i,j): i valid if e[i]>=last_of_i's_breed or e[i]>=j
    // j valid if e[j]>=last_of_j's_breed or e[j]>=i
    
    vector<int> lastG(n), lastH(n);
    int lg = -1, lh = -1;
    for (int i = n-1; i >= 0; i--) {
        if (breed[i] == 'G') lg = i;
        else lh = i;
        lastG[i] = lg;
        lastH[i] = lh;
    }
    vector<int> firstG(n), firstH(n);
    lg = -1; lh = -1;
    for (int i = 0; i < n; i++) {
        if (breed[i] == 'G') lg = i;
        else lh = i;
        firstG[i] = lg;
        firstH[i] = lh;
    }
    // For Guernsey leader i: covers all G if e[i] >= lastG[0]
    // For Holstein leader j: covers all H if e[j] >= lastH[0]
    // 
    // Brute force for small n (but n up to 10^5)
    // Precompute: for each Guernsey cow, does it cover all G?
    // And for each Holstein cow, does it cover all H?
    int lastAllG = lastG[0], lastAllH = lastH[0];
    vector<bool> coverAllG(n, false), coverAllH(n, false);
    for (int i = 0; i < n; i++) {
        if (breed[i] == 'G') coverAllG[i] = (e[i] >= lastAllG);
        if (breed[i] == 'H') coverAllH[i] = (e[i] >= lastAllH);
    }
    
    long long ans = 0;
    // Count pairs (g, h) where g is Guernsey, h is Holstein
    // g valid if coverAllG[g] or e[g] >= h (covers the other leader)
    // h valid if coverAllH[h] or e[h] >= g
    
    // For each G cow g:
    // If coverAllG[g]: any H cow h where coverAllH[h] or e[h]>=g
    // If not coverAllG[g]: need e[g]>=h, and coverAllH[h] or e[h]>=g
    
    // Count all H cows that cover all H
    int cntCoverAllH = 0;
    for (int i = 0; i < n; i++) if (breed[i]=='H' && coverAllH[i]) cntCoverAllH++;
    
    // For each G cow g, count valid H partners
    for (int i = 0; i < n; i++) {
        if (breed[i] != 'G') continue;
        long long cnt = 0;
        if (coverAllG[i]) {
            // All H cows are valid partners
            cnt = n / 2; // approximate, need exact count
            // Actually count all H cows
            cnt = 0;
            for (int j = 0; j < n; j++) {
                if (breed[j] == 'H' && (coverAllH[j] || e[j] >= i)) cnt++;
            }
        } else {
            // Need e[i] >= h's position
            for (int j = 0; j < n; j++) {
                if (breed[j] == 'H' && j <= e[i]-1 && (coverAllH[j] || e[j] >= i)) cnt++;
            }
        }
        ans += cnt;
    }
    cout << ans << "\n";
    return 0;
}
