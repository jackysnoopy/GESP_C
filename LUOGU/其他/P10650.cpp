#include <iostream>
#include <vector>
using namespace std;

int arr[100005], tmp_arr[100005];

long long merge_count(int l, int r) {
    if (l >= r) return 0;
    int mid = (l + r) / 2;
    long long cnt = merge_count(l, mid) + merge_count(mid + 1, r);
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) tmp_arr[k++] = arr[i++];
        else { cnt += mid - i + 1; tmp_arr[k++] = arr[j++]; }
    }
    while (i <= mid) tmp_arr[k++] = arr[i++];
    while (j <= r) tmp_arr[k++] = arr[j++];
    for (i = l; i <= r; i++) arr[i] = tmp_arr[i];
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    cout << merge_count(0, n - 1) << "\n";
    return 0;
}
