#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k;
    cin>>n>>k;
    vector<vector<long long>> a(k,vector<long long>(n));
    for(int i=0;i<k;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];
    vector<long long> b(n);
    for(int j=0;j<n;j++){
        vector<long long> vals;
        for(int i=0;i<k;i++) vals.push_back(a[i][j]);
        sort(vals.begin(),vals.end());
        b[j]=vals[k/2];
    }
    for(int j=0;j<n;j++){
        if(j) cout<<" ";
        cout<<b[j];
    }
    cout<<"\n";
    return 0;
}
