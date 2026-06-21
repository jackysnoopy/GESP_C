#include <iostream>
#include <vector>
using namespace std;

long long merge_sort(vector<int>& a, int l, int r) {
    if (l >= r) return 0;
    int mid = (l + r) / 2;
    long long ans = merge_sort(a, l, mid) + merge_sort(a, mid + 1, r);
    
    vector<int> tmp;
    int i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp.push_back(a[i++]);
        else {
            tmp.push_back(a[j++]);
            ans += mid - i + 1;
        }
    }
    while (i <= mid) tmp.push_back(a[i++]);
    while (j <= r) tmp.push_back(a[j++]);
    for (int k = 0; k < (int)tmp.size(); k++)
        a[l + k] = tmp[k];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        int N;
        cin >> N;
        if (N == 0) break;
        vector<int> a(N);
        for (int i = 0; i < N; i++) cin >> a[i];
        cout << merge_sort(a, 0, N - 1) << "\n";
    }
    
    return 0;
}