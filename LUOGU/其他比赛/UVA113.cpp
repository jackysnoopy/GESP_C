#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

typedef long long ll;

struct Matrix {
    ll mat[2][2];
    Matrix() {
        mat[0][0] = mat[0][1] = mat[1][0] = 1;
        mat[1][1] = 0;
    }
    Matrix(ll a, ll b, ll c, ll d) {
        mat[0][0] = a; mat[0][1] = b;
        mat[1][0] = c; mat[1][1] = d;
    }
};

Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix result(0, 0, 0, 0);
    result.mat[0][0] = a.mat[0][0] * b.mat[0][0] + a.mat[0][1] * b.mat[1][0];
    result.mat[0][1] = a.mat[0][0] * b.mat[0][1] + a.mat[0][1] * b.mat[1][1];
    result.mat[1][0] = a.mat[1][0] * b.mat[0][0] + a.mat[1][1] * b.mat[1][0];
    result.mat[1][1] = a.mat[1][0] * b.mat[0][1] + a.mat[1][1] * b.mat[1][1];
    return result;
}

Matrix matrixPower(Matrix base, ll exp) {
    Matrix result(1, 0, 0, 1);
    while (exp > 0) {
        if (exp & 1) {
            result = multiply(result, base);
        }
        base = multiply(base, base);
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    while (cin >> n) {
        if (n == 1) {
            cout << "2\n";
            continue;
        }
        
        Matrix base;
        Matrix result = matrixPower(base, n);
        
        ll fn = result.mat[0][0];
        ll fn1 = result.mat[0][1];
        
        double phi = (1.0 + sqrt(5.0)) / 2.0;
        double ans = fn * phi + fn1;
        
        cout << (ll)round(ans) << "\n";
    }
    
    return 0;
}
