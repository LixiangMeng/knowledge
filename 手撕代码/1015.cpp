#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
int bfs(int x,int y,vector<vector<int>>& nums,vector<vector<int>>& mp){
    queue<pair<int,int>> que;
    int n = nums.size();
    int m = nums[0].size();
    int cur = 1;
    que.push({x,y});
    int result = INT_MAX;
    while(!que.empty()){
        int x,y;
        pair<int,int> location = que.front();
        x = location.first;
        y = location.second;
        for(int i=0;i<4;i++){
            int nx = x+dir[i][0];
            int ny = y+dir[i][1];
            if(nx<0||ny<0||nx>=n||ny>=m){
                continue;
            }
            if(nums[nx][ny]==1){
                result = min(cur,result);
            }
            if(mp[nx][ny]!=-1){
                result = min(result,mp[nx][ny]);
            }
            que.push({nx,ny});
        } 
        cur++;
    }
    return result;
}

int main() {
    int n,m;
    cin>>n>>m;
    vector<vector<int>> nums(n,vector(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>nums[i][j];
        }
    }
    vector<vector<int>> mp(n,vector(m,-1));
    for(int i=0;i<n;i++){
        for(int j=0;i<m;j++){
            if(nums[i][j]==0){
                int result = bfs(i,j,nums,mp);
                mp[i][j] = result;
            }
        }
    }
    return 0;
}