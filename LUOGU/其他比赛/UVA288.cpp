#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        vector<int> data(n);
        for (int i = 0; i < n; i++) {
            cin >> data[i];
        }
        
        int total = 0;
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = 0; j <= i; j++) {
                sum += data[j];
            }
            total += sum;
        }
        
        cout << total << endl;
    }
    return 0;
}
