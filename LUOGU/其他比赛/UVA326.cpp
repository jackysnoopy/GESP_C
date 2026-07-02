#include <iostream>
#include <string>
using namespace std;

int main() {
    int p, q;
    while (cin >> p >> q && (p || q)) {
        int a = 0, b = 1, c = 1, d = 0;
        string path;
        while (true) {
            int mediant_num = a + c;
            int mediant_den = b + d;
            if (p == mediant_num && q == mediant_den) break;
            if ((long long)p * mediant_den < (long long)q * mediant_num) {
                path += 'L';
                c = mediant_num;
                d = mediant_den;
            } else {
                path += 'R';
                a = mediant_num;
                b = mediant_den;
            }
        }
        cout << p << "/" << q << " = ";
        for (char ch : path) cout << ch;
        cout << endl;
    }
    return 0;
}
