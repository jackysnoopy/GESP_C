#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Cow {
    int a, b;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<Cow> cows(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i].a >> cows[i].b;
    }
    
    // Johnson's rule: sort by a+b ascending
    sort(cows.begin(), cows.end(), [](const Cow& x, const Cow& y) {
        return x.a + x.b < y.a + y.b;
    });
    
    // Simulate the flow shop
    long long c1 = 0, c2 = 0;
    for (int i = 0; i < n; i++) {
        c1 += cows[i].a;
        c2 = max(c2, c1) + cows[i].b;
    }
    
    cout << c2 << "\n";
    
    return 0;
}
