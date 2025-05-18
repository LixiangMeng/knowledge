// ����һ���������� A�������������ֵ�������ʹ������ӵ��ض�Ŀ�� B��ÿ������ֻ��һ�����������ͬһ��Ԫ�ز���ʹ�����Ρ�
// 1.Ҫ��ʱ�临�Ӷ�Ϊ O(N)
// 2.�������Բ���
// 3.����Ҫд��׼����


// class Solution {
// public:
//     std::vector<int> twoSum(const std::vector<int>& nums, int target) {
//         // TODO
//     }
// };

// // e.g.
// Solution().twoSum({ 2, 7, 11, 15 }, 9); // output: 0, 1

#include <vector>
#include<iostream>
#include<unordered_map>
using namespace std;
int main(){
    vector<int> nums = {2,7,11,15};
    int target = 9;
    unordered_map<int,int> mp;
    for(int i=0;i<nums.size();i++){
        int cur = nums[i];
        int diff = target - nums[i];
        auto it = mp.find(diff);
        if(it!=mp.end()){
            cout<<it->second<<","<<i<<endl;
        }
        mp[cur]=i;
    }
    return -1;
}
