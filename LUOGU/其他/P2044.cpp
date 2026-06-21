#include <iostream>
using namespace std;

long long m, a, c, X0, n, g;

struct Mat {
    long long v[2][2];
    Mat() { v[0][0]=v[0][1]=v[1][0]=v[1][1]=0; }
};

Mat mul(Mat A, Mat B) {
    Mat C;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                C.v[i][j] = (C.v[i][j] + A.v[i][k] * B.v[k][j]) % m;
    return C;
}

Mat power(Mat A, long long p) {
    Mat R;
    R.v[0][0] = R.v[1][1] = 1;
    while (p > 0) {
        if (p & 1) R = mul(R, A);
        A = mul(A, A);
        p >>= 1;
    }
    return R;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> a >> c >> X0 >> n >> g;
    if (n == 0) { cout << X0 % g << "\n"; return 0; }
    // X_{k+1} = a*X_k + c (mod m)
    // [X_{k+1}]   [a c] [X_k]
    // [1      ] = [0 1] [1  ]
    Mat T;
    T.v[0][0] = a; T.v[0][1] = c;
    T.v[1][0] = 0; T.v[1][1] = 1;
    Mat R = power(T, n);
    long long Xn = (R.v[0][0] * X0 % m + R.v[0][1]) % m;
    cout << ((Xn % g) + g) % g << "\n";
    return 0;
}
