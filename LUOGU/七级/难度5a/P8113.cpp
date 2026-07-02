#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef long long ll;
ll simulate(vector<ll> a, ll m){
    ll sum=0, cnt=0;
    for(ll x:a){
        // current average = cnt? sum/cnt; if cnt==0 average=0
        bool rateM;
        if(cnt==0) rateM=true; // avg 0 <= x (x>=0)
        else rateM = ( (double)sum/cnt <= (double)x );
        if(rateM){ sum+=m; }
        cnt++;
    }
    return sum;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; ll m;
    if(!(cin>>n>>m)) return 0;
    vector<ll> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<ll> asc=a; sort(asc.begin(),asc.end());
    vector<ll> desc=a; sort(desc.rbegin(),desc.rend());
    ll maxSum=simulate(asc,m);
    ll minSum=simulate(desc,m);
    cout<<fixed<<setprecision(2)<<(double)maxSum/n<<" "<<(double)minSum/n<<"\n";
    return 0;
}
