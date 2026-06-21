#include <iostream>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;
/**
 * @file FILENAME
 * @brief Brief description of the file
 * @author JackyChen
 * @date 2025-12-02
 */
bool isprime(int x){
    if(x==0||x==1) return false;
    for(int i=2;i*i<=x;i++){
        if(x%i==0) return false;
    }
    return true;
}
 int main() {
 // Type your code here
    string s;
    cin >> s;
    int a[30]={0};
    int max_char=INT_MIN,min_char=INT_MAX;
    for(int i=0;i<s.size();i++){
        a[s[i]-'a']++;
    }
    for(int i=0;i<26;i++){
        if(a[i]!=0){
            max_char=max(max_char,a[i]);
            min_char=min(min_char,a[i]);
        }
    }
    if(isprime(max_char-min_char)){
        cout<<"Lucky Word"<<endl;
        cout<<max_char-min_char<<endl;
    }else{
        cout<<"No Answer"<<endl;
        cout<<0<<endl;
    }
  return 0;
}