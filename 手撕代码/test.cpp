// 2. ��һ�����ξ���matrix��ʾһ������1������·��0������·��ÿһ��λ��ֻҪ��Խ�磬�������������ĸ�������������Ͻǵ����½ǵ����ͨ·ֵ
// ���磬matrixΪ��
// 1 0 1 1 1
// 1 0 1 0 1
// 1 1 1 0 1
// 0 0 0 0 1
// ͨ·ֻ��һ������12��1���ɣ��������12
// ���磬matrixΪ��
// 1 1 0 1 1
// 1 1 1 1 1
// 1 1 1 1 1
// 0 0 0 0 1
// ���8

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