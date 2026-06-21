#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000000];
int b[1000000];
signed main() {
	int n;
	cin >> n;
	int i, j, k;
	for (i = 0; i < n; i++) {
		cin >> a[i];
	}
	int m;
	cin >> m;
	for (i = 1; i <= m; i++) {
		cin >> k;
		b[i] = a[k];
		int ans = 0;
		for (j = 1;j<=i; j++) {
			if (b[j] > b[i]) {
				swap(b[i], b[j]);
				ans++;
			}
		}
		cout << ans << endl;
	}
}
