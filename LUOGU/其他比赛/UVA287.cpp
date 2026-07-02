#include <iostream>
#include <set>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        set<int> values;
        for (int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                values.insert(i);
                values.insert(n / i);
            }
        }
        
        cout << n;
        for (auto it = values.begin(); it != values.end(); ++it) {
            cout << " " << *it;
        }
        cout << endl;
    }
    return 0;
}
