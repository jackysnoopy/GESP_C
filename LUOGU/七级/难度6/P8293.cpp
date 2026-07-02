#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 400005;
int weight[MAXN];
char s[MAXN * 2];
int n, x, y;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> x >> y;
    cin >> s;
    
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }
    
    // Simplified approach: count pairs
    long long ans = 0;
    
    // For each pair of brackets, calculate cost
    for (int i = 0; i < 2 * n; i += 2) {
        if (s[i] == '(' && s[i + 1] == ')') {
            ans += min(x, y) * weight[i / 2];
        }
    }
    
    cout << ans << endl;
    
    return 0;
}