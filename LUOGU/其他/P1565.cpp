#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> a(n, vector<long long>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> a[i][j];
    vector<vector<long long>> sum(n+1, vector<long long>(m+1, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            sum[i+1][j+1] = sum[i][j+1]+sum[i+1][j]-sum[i][j]+a[i][j];
    long long lo = -1e18, hi = 1e18;
    while (lo < hi) {
        long long mid = (lo+hi+1)/2;
        bool found = false;
        for (int r1=0; r1<n&&!found; r1++)
            for (int r2=r1; r2<n&&!found; r2++) {
                vector<long long> cs(m,0);
                for (int j=0;j<m;j++) cs[j]=sum[r2+1][j+1]-sum[r1][j+1]-sum[r2][j]+sum[r1][j]-mid*(r2-r1+1);
                long long mn=0,cur=0;
                for(int j=0;j<m;j++){cur+=cs[j];if(cur-mn>0){found=true;break;}mn=min(mn,cur);}
            }
        if(found)lo=mid;else hi=mid-1;
    }
    long long best=0;
    for(int r1=0;r1<n;r1++)for(int r2=r1;r2<n;r2++){
        vector<long long> cs(m,0);
        for(int j=0;j<m;j++)cs[j]=sum[r2+1][j+1]-sum[r1][j+1]-sum[r2][j]+sum[r1][j]-lo*(r2-r1+1);
        long long mn=0,cur=0;
        for(int j=0;j<m;j++){cur+=cs[j];if(cur-mn>0)best=max(best,(long long)(r2-r1+1)*(j+1));mn=min(mn,cur);}
    }
    cout<<best<<endl;
    return 0;
}