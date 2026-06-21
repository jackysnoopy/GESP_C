#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int n = s.size();
    int odd_a = 0, even_a = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') {
            if (i % 2 == 0) odd_a++;
            else even_a++;
        }
    }
    int total_a = odd_a + even_a;
    if (total_a % 2 != 0) { cout << -1 << "\n"; return 0; }
    int target = total_a / 2;
    if (odd_a == target) { cout << 0 << "\n"; return 0; }
    int need = odd_a - target;
    if (need < 0) need = -need;
    cout << need << "\n";
    return 0;
}
