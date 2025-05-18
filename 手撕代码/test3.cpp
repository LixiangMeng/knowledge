#include<iostream>
#include<vector>
using namespace std;
void quicksort(vector<int>&nums,int start,int end){
    int flag = nums[start];
    int left = start;
    int right = end;
    if(start<end){
        while(left<right){
            while(left<right&&nums[right]>=flag){
                right--;
            }
            nums[left] = nums[right];
            while(left<right&&nums[left]<=flag){
                left++;
            }
            nums[right] = nums[left];
        }
        nums[left] = flag;
        quicksort(nums,start,left-1);
        quicksort(nums,left+1,end);
    }
    return;
}
int main(){
    vector<int> nums = {2,1,6,8,2,3};
    quicksort(nums,0,nums.size()-1);
    for(auto& num:nums){
        cout<<num<<",";
    }
}