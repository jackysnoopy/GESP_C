#include<bits/stdc++.h>  
using namespace std;
bool zs(int a){
	if(a==1)return 0;
	for(int i=2;i<=sqrt(a);i++){
		if(a%i==0)return 0;
	}
	return 1;
}
int main(){
    int t;
    cin>>t;
    int h;
    while(t){
    	t--;
    	cin>>h;
    	if(zs(h)){cout<<1<<endl;continue;}
    	for(int i=1;i>=1;i++){
    		h-=pow(2,i-1);
    		if(h<0){cout<<-1<<endl;break;}
    		if(h==0){cout<<i<<endl;break;}
    		if(h>0&&zs(h)){cout<<i+1<<endl;break;}
		}
	}
    return 0;
}
