#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int n;
    int result[10002];
    int len=0;
    while(cin>>n){
        result[len++] = n;
        if(getchar()=='\n')
            break;
    }
    int dp[1001]={0};
    int ans = 1;
    for(int i=0;i<len;i++){
        dp[i]=1;
    }
    for(int i=0;i<len;i++){
        for(int j=i+1;j<len;j++){
            if(result[j]>result[i]){
                dp[j]=max(dp[j],dp[i]+1);
                ans = max(ans,dp[j]);
            }
        }
    }
    cout<<ans;
}