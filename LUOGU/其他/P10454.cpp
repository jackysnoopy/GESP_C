#include <iostream>
#include <vector>
using namespace std;

int merge_sort(vector<int>& a, int l, int r) {
    if (l >= r) return 0;
    int mid = (l + r) / 2;
    int ans = merge_sort(a, l, mid) + merge_sort(a, mid + 1, r);
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
    
    int n;
    while (cin >> n) {
        int size = n * n;
        vector<int> a, b;
        
        for (int i = 0; i < size; i++) {
            int x;
            cin >> x;
            if (x != 0) a.push_back(x);
        }
        for (int i = 0; i < size; i++) {
            int x;
            cin >> x;
            if (x != 0) b.push_back(x);
        }
        
        int inv_a = merge_sort(a, 0, a.size() - 1);
        int inv_b = merge_sort(b, 0, b.size() - 1);
        
        cout << ((inv_a & 1) == (inv_b & 1) ? "TAK" : "NIE") << "\n";
    }
    
    return 0;
}