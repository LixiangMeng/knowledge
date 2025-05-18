#include<iostream>
#include<vector>
using namespace std;
void quickSort(int start, int end, vector<int>& nums){
    int left = start;
    int right = end;
    int mid = nums[left];
    if(start<end){
        while(left<right){
            while(left<right&&nums[right]>=mid){
                right--;
            }
            nums[left] = nums[right];
            while(left<right&&nums[left]<=mid){
                left++;
            }
            nums[right] = nums[left];
        }
        nums[left] = mid;
        quickSort(start,left-1,nums);
        quickSort(left+1,end,nums);
    }
    return ;
}
int main(){
    vector<int> nums = {1,3,2,5,4,2,3,1};
    quickSort(0,nums.size()-1,nums);
    for(auto &num:nums){
        cout<<num<<",";
    }
    return 0;
}