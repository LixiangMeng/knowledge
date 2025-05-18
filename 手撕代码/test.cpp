// 2. 用一个整形矩阵matrix表示一个网格，1代表有路，0代表无路，每一个位置只要不越界，都有上下左右四个方向，求从最左上角到右下角的最短通路值
// 例如，matrix为：
// 1 0 1 1 1
// 1 0 1 0 1
// 1 1 1 0 1
// 0 0 0 0 1
// 通路只有一条，由12个1构成，所以输出12
// 例如，matrix为：
// 1 1 0 1 1
// 1 1 1 1 1
// 1 1 1 1 1
// 0 0 0 0 1
// 输出8

#include <iostream>
#include <vector>
using namespace std;
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int result = INT_MAX/2;
void dfs(int n,int m,int row,int col,vector<vector<int>>& nums,vector<vector<int>>& flag,int sum){
    if(row==n-1&&col==m-1){
        if(sum<result){
            result = sum;
        }
        return ;
    }
    for(int i=0;i<4;i++){
        int x = dir[i][0]+row;
        int y = dir[i][1]+col;
        if(x>=n||y>=m||x<0||y<0){
            continue;
        }
        if(nums[x][y]==0){
            continue;
        }
        if(flag[x][y]==1){
            continue;
        }
        flag[x][y]=1;
        dfs(n,m,x,y,nums,flag,sum+1);
        flag[x][y]=0;
    }
}
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> nums(n+1,vector<int>(n+1));
    vector<vector<int>> flag(n+1,vector<int>(n+1));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>nums[i][j];
        }
    }
    if(nums[0][0]==0||nums[n-1][m-1]==0){
        cout<<0<<endl;
        return 0;
    }
    flag[0][0]=1;
    dfs(n,m,0,0,nums,flag,1);
    cout<<result<<endl;
}