#include <bits/stdc++.h>
using namespace std;

int n, p[100005];

vector < int > prime;
vector < int > a[100005];

void fjzyz(int x)
{
    int t = sqrt(x);
    for (int i = 2; i <= t; i++)
    {
        int cnt = 0;
        while (x % i == 0)
        {
            cnt++;
            x /= i;
        }
        if (p[i] == 0 && cnt > 0) a[i].push_back(cnt);
    }
    if (x > 1) a[x].push_back(1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(0);
    cin >> n;
    p[1] = 1;
    for (int i = 2; i <= 316; i++)
        if (p[i] == 0)
        {
            for (int j = i * i; j <= 100000; j += i)
                p[j] = 1;
        }
    for (int i = 1; i <= 100000; i++)
        if (p[i] == 0) prime.push_back(i);
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        fjzyz(x);
    }
    int ans = 0;
    for (auto i : prime)
        if (!a[i].empty())
        {
            sort(a[i].begin(), a[i].end());
            int k = (n + 1) / 2;
            k -= n - (int)a[i].size();
            for (auto j : a[i])
                ans += abs(j - (k >= 0 ? a[i][k - 1] : 0));
            ans += (n - a[i].size()) * (k >= 0 ? a[i][k - 1] : 0);
        }
    cout << ans << endl;
    return 0;
}
