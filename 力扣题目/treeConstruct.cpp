#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct treeNode{
    int val;
    treeNode *left,*right;
    treeNode(int x):val(x),left(nullptr),right(nullptr){}
};
void dfs(treeNode* root,int num0,int num1,int& result){
    if(!root){
        return;
    }
    if(root->val==0){
        num0++;
    } else if(root->val==1){
        num1++;
    }
    if(!root->left&&!root->right){
        if(num1-num0==1){
            result++;
        }
        return ;
    }
    dfs(root->left,num0,num1,result);
    dfs(root->right,num0,num1,result);
}
int main(){
    int n;
    cin>>n;
    vector<int> nums(n+1,0);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    if(nums.size()==0){
        cout<<0<<endl;
        return 0;
    }
    queue<treeNode*> que;
    treeNode *root = new treeNode(nums[0]);
    que.push(root);
    int index = 0;
    while(!que.empty()){
        treeNode* tmp = que.front();
        que.pop();
        if(index*2+1<n&&nums[index*2+1]!=-1){
            tmp->left = new treeNode(nums[index*2+1]);
            que.push(tmp->left);
        }
        if(index*2+2<n&&nums[index*2+2]!=-1){
            tmp->right = new treeNode(nums[index*2+2]);
            que.push(tmp->right);
        }
        index+=1;
    }
    int result = 0;
    dfs(root,0,0,result);
    cout<<result<<endl;
    
}