#include <bits/stdc++.h>
using namespace std;

bool can(int x, const vector<int>& A) {
    vector<int> B;
    for (int v : A) {
        if (v > x) B.push_back(v);
    }
    
    for (int i = 0; i < (int)B.size(); i += 2) {
        if (B[i] != B[i + 1]) return false;
    }
    return true;
}

int main() {
    
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    int maxA = *max_element(A.begin(), A.end());


    int left = 1, right = maxA, ans = maxA;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (can(mid,A)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << ans <<endl;
    return 0;
}
