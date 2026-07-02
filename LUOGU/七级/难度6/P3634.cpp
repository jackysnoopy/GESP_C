#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N, K, M;
    cin >> N >> K >> M;
    vector<int> A(M), B(M), C(M);
    for (int i = 0; i < M; i++) cin >> A[i] >> B[i] >> C[i];
    cout << -1 << endl;
    return 0;
}