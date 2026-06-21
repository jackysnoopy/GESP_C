#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int left = 0, right = n - 1;
    while (left < n && a[left] == 0) left++;
    while (right >= 0 && a[right] == 0) right--;
    
    if (left > right) {
        cout << 0 << endl;
    } else {
        cout << right - left + 1 << endl;
    }
    
    return 0;
}
