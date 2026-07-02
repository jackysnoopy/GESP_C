#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<long long> sorted_l, sorted_r;
int n;

long long compute_cost(long long m) {
    int n_L = sorted_l.end() - upper_bound(sorted_l.begin(), sorted_l.end(), m);
    int n_R = lower_bound(sorted_r.begin(), sorted_r.end(), m) - sorted_r.begin();
    int n_M = n - n_L - n_R;

    long long T = 0;
    int idx = 0;
    int i = n - n_L;
    int j = 0;
    int k = 0;

    while (i < n || j < n_R || k < n_M) {
        long long val_L = (i < n) ? sorted_l[i] : LLONG_MAX;
        long long val_M = (k < n_M) ? m : LLONG_MAX;
        long long val_R = (j < n_R) ? sorted_r[j] : LLONG_MAX;

        long long val;
        if (val_L <= val_M && val_L <= val_R) {
            val = val_L;
            i++;
        } else if (val_M <= val_L && val_M <= val_R) {
            val = val_M;
            k++;
        } else {
            val = val_R;
            j++;
        }

        long long coeff = 2LL * (idx + 1) - n - 1;
        T += val * coeff;
        idx++;
    }

    return 2 * T;
}

int main() {
    cin >> n;
    vector<long long> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }
    sorted_l = l;
    sorted_r = r;
    sort(sorted_l.begin(), sorted_l.end());
    sort(sorted_r.begin(), sorted_r.end());

    long long low = 0, high = 1000000000;
    while (high - low > 2) {
        long long mid1 = low + (high - low) / 3;
        long long mid2 = high - (high - low) / 3;
        long long cost1 = compute_cost(mid1);
        long long cost2 = compute_cost(mid2);
        if (cost1 < cost2) {
            high = mid2 - 1;
        } else {
            low = mid1 + 1;
        }
    }

    long long min_cost = LLONG_MAX;
    for (long long m = low; m <= high; m++) {
        long long cost = compute_cost(m);
        if (cost < min_cost) {
            min_cost = cost;
        }
    }

    cout << min_cost << endl;
    return 0;
}