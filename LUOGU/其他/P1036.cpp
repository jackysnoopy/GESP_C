#include <iostream>
using namespace std;
/**
 * @file P1036 [NOIP 2002 普及组] 选数
 * @brief Brief description of the file
 * @author JackyChen
 * @date 2025-12-02
 */
int ans[21],nums[21];
int n,k,cnt=0;

bool isprime(int x){
    if(n==0||n==1) return false;
    for(int i=2;i*i<=x;i++){
        if(x%i==0) return false;
    }
    return true;
}

void dfs(int start,int step){
    if(step==k+1){
        int sum=0;
        for(int i=1;i<=k;i++){
            sum+=ans[i];
        }
        if(isprime(sum)){
            cnt++;
        }
        return;
    }
    for(int i=start;i<=n;i++){
        ans[step]=nums[i];
        dfs(i+1,step+1);

    }
}
 int main() {
 // Type your code here
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    dfs(1,1);
    cout<<cnt<<endl;
  return 0;
}