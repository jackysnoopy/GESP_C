#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int base;
    cin >> base;
    int ma;
    cin >> ma;
    vector<int> A(ma);
    for (int i = 0; i < ma; ++i) cin >> A[i];
    int mb;
    cin >> mb;
    vector<int> B(mb);
    for (int i = 0; i < mb; ++i) cin >> B[i];
    long long va = 0, vb = 0;
    for (int x : A) va = va * base + x;
    for (int x : B) vb = vb * base + x;
    cout << va - vb << '\n';
    return 0;
}
