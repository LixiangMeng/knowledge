#include<iostream>
#include<string>
using namespace std;
int main(){
    int map[100][100]={0};
    int n=0,m=0;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>map[i][j];
        }
    }
    int k=0;
    int num=0;
    int result[10002]={0};
    while(num<n*m){
        for(int i=k;i<m-k;i++){
            result[num++]=map[k][i];
            //cout<<map[k][i]<<",";
        }
        if(num>=n*m) break;
        for(int j=k+1;j<n-k;j++){
            result[num++]=map[j][m-k-1];
            //cout<<map[j][m-k-1]<<",";
        }
        if(num>=n*m) break;
        for(int i=m-k-2;i>=k;i--){
            result[num++]=map[n-k-1][i];
            //cout<<map[n-k-1][i]<<",";
        }
        if(num>=n*m) break;
        for(int j=n-k-2;j>k;j--){
            result[num++]=map[j][k];
            //cout<<map[j][k]<<",";
        }
        if(num>=n*m) break;
        k++;
    }
    for(int i=0;i<num;i++){
        cout<<result[i]<<" ";
    }

}