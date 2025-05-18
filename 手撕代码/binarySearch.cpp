#include<iostream>
#include<vector>
using namespace std;

//�ж������Ƿ�����
bool isSorted(vector<int>& nums){
    for(int i=0;i<nums.size()-1;i++){
        if(nums[i]>nums[i+1]){
            return false;
        }
    }
    return true;
}

//ʵ�ֶ��ֲ���
int binarySearch(vector<int>& nums,int target){
    //�жϸ������Ƿ�����
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
        cout<<"δ�ҵ�Ŀ��ֵ"<<endl;
    } else if(result==-2){
        cout<<"������鲻�������"<<endl;
    } else {
        cout<<"Ŀ��ֵ��λ��"<<k<<endl;
    }
}