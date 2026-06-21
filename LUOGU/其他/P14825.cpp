#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Brute force problem: simulate operations until can't operate.
    // Operation: if a[i] == a[i+1], replace both with a[i]+1.
    // Keep doing until no adjacent equal pair.
    
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < (int)a.size() - 1; i++) {
            if (a[i] == a[i + 1]) {
                a[i] = a[i] + 1;
                a.erase(a.begin() + i + 1);
                changed = true;
                break;
            }
        }
    }
    
    cout << a.size() << endl;
    for (int i = 0; i < (int)a.size(); i++) {
        if (i > 0) cout << " ";
        cout << a[i];
    }
    cout << endl;
    return 0;
}
