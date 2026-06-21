#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    sort(h.begin(), h.end());
    // The cat with max happiness eats others. After eating, happiness increases by 1.
    // Cat i eats cat j (h[i] > h[j]): h[i] becomes h[i]+1, cat j vanishes.
    // We want one cat to eat all others.
    // Sort: h[0] <= h[1] <= ... <= h[n-1]
    // Strategy: smallest eats... no, bigger eats smaller.
    // Actually: the last surviving cat eats all others one by one.
    // After eating k cats, its happiness is h + k.
    // It must always have strictly greater happiness than the cat being eaten.
    // 
    // Simulate from smallest to largest:
    // Process sorted. Track how many have been eaten by cats with higher happiness.
    // A cat with happiness h[i] can eat all cats with happiness < h[i].
    // But after eating, happiness increases.
    // 
    // Key: sort ascending. Process left to right.
    // Maintain a count of "eaten" cats.
    // For each cat, it can eat all previously uneaten cats if its happiness > their happiness.
    // After eating, its happiness increases by 1 per cat eaten.
    //
    // Actually simpler: sort ascending. The surviving cat is the one with max h.
    // Before eating, it has h[n-1]. It needs to eat cats h[0]..h[n-2].
    // Sort h[0]..h[n-2] ascending. Eat them in order.
    // After eating k cats, happiness = h[n-1] + k.
    // Need h[n-1] + k > h[k] for each k (0-indexed among eaten).
    // So: h[n-1] + k > h[k] for all k = 0..n-2.
    // i.e., h[n-1] + k > h[k] for all k < n-1.
    // If n=1: trivially YES.
    // If n=2: h[1] > h[0]? Need h[1] > h[0]. If equal, h[1]+0 > h[0] fails.
    // Wait, after eating 0 cats, happiness is h[n-1]. Need h[n-1] > h[0] (eat first).
    // Then h[n-1]+1 > h[1]. Etc.
    // So condition: h[n-1] + k > h[k] for all k = 0..n-2.
    
    if (n == 1) { cout << "YES\n"; return 0; }
    bool ok = true;
    for (int k = 0; k < n - 1; k++) {
        if ((long long)h[n-1] + k <= h[k]) { ok = false; break; }
    }
    cout << (ok ? "YES\n" : "NO\n");
    return 0;
}
