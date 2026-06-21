#include <bits/stdc++.h>
using namespace std;
constexpr int N=1e6+5;
int a[N];
int main(){
    cin.tie(0)->sync_with_stdio(0);
	int n,L,R;
    cin>>n;
    L=0,R=n-1;
	for(int i=0;i<n;++i) cin>>a[i];
    sort(a,a+n);
    for(int bit=1<<30;bit;bit>>=1){
        if((a[L]&bit)||!(a[R]&bit)) continue;  // 这一位全部相同
        if((a[R]&bit)&&!(a[R-1]&bit)){  // 只有1个1
            int t=a[R]^=bit,i;
            for(i=R-1;i>=L&&a[i]>t;--i) a[i+1]=a[i];
            a[i+1]=t;
        }else{  // 1的个数多于1
            int l=L,r=R,mid;
            while(l<r){
                mid=l+r>>1;
                if(a[mid]&bit) r=mid;
                else l=mid+1;
            }
            L=l;
        }
        if(R-L<=1) break;
    }
    assert(L<R);
    cout<<(a[L]&a[R]);
	return 0;
}
