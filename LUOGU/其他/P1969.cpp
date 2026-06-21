#include <iostream>
using namespace std;
/**
 * @file P1969 积木大赛
 * @brief Brief description of the file
 * @author JackyChen
 * @date 2026-06-04
 */
int n,ans;
int a[100005],b[100005];

int main() {
 // Type your code here
 cin>>n;
 for(int i=1;i<=n;i++){
    cin>>a[i];
    b[i]=a[i]-a[i-1];
    if(b[i]>0){
        ans+=b[i];
    }
 }
 cout<<ans<<endl;
  return 0;
}