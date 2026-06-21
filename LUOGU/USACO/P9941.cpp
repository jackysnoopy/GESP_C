#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    int odd = 0, even = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] % 2) odd++;
        else even++;
    }
    // Groups alternate: even sum, odd sum, even sum, odd sum, ...
    // A group with even sum needs at least 1 even number OR an even count of odd numbers.
    // A group with odd sum needs at least 1 odd number.
    // For max groups: use as few elements per group as possible.
    // Group 1 (even): 1 even, or 2 odds
    // Group 2 (odd): 1 odd
    // Group 3 (even): 1 even, or 2 odds
    // ...
    // Greedy: alternate, use minimum elements.
    // Start with even group.
    // Even group: use 1 even if available, else 2 odds.
    // Odd group: use 1 odd.
    int groups = 0;
    bool needEven = true; // first group needs even sum
    while (true) {
        if (needEven) {
            if (even > 0) { even--; groups++; needEven = false; }
            else if (odd >= 2) { odd -= 2; groups++; needEven = false; }
            else break;
        } else {
            if (odd > 0) { odd--; groups++; needEven = true; }
            else break;
        }
    }
    cout << groups << "\n";
    return 0;
}
