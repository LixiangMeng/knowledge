#include<iostream>
#include<vector>
using namespace std;

//判断数组是否有序
bool isSorted(vector<int>& nums){
    for(int i=0;i<nums.size()-1;i++){
        if(nums[i]>nums[i+1]){
            return false;
        }
    }
    return true;
}

//实现二分查找
int binarySearch(vector<int>& nums,int target){
    //判断该数组是否有序
    if(!isSorted(nums)){
        return -2;
    }
    int left = 0;
    int right = nums.size()-1;
    while(left<=right){
        int mid = (left+right)/2;
        if(nums[mid]==target){
            return mid;
        }
        if(nums[mid]<target){
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
int main(){
    int n;
    int k;
    cin>>n>>k;
    vector<int> nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    int result = binarySearch(nums,k);
    if(result==-1){
        cout<<"未找到目标值"<<endl;
    } else if(result==-2){
        cout<<"这个数组不是有序的"<<endl;
    } else {
        cout<<"目标值在位置"<<k<<endl;
    }
}