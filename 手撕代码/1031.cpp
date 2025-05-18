// 给定一个整数数组 A，返回两个数字的索引，使它们相加到特定目标 B。每个数组只有一个解决方案，同一个元素不能使用两次。
// 1.要求时间复杂度为 O(N)
// 2.开发语言不限
// 3.不需要写标准输入


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
