​
题目链接：1. 两数之和 - 力扣（LeetCode）

题目描述：

​​​​​​​​​​​​​​​​​给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。

你可以按任意顺序返回答案。
题目思路：暴力解法很容易想到，双重for循环即可，时间复杂度是O(n*n),代码如下：
#define ll long long
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        //unordered_map<int,int>ump;
        vector<int>ans;
        for(int i=0;i<nums.size();i++){
            for(int j=i+1;j<nums.size();j++){
                if(nums[i]+nums[j]==target){
                    ans.push_back(i);
                    ans.push_back(j);
                    return ans;
                }
            }
        }
        return {};
    }
};
优化解法：我们可以枚举数组中的nums[i], 来查找哈希表中是否存在一个数x = target - nums[i], 如果存在，那么当前下标i和ump[x] 就是我们需要找的下标，如果不存在，我们把当前数nums[i] 加入哈希表即可, 时间复杂度是O(n), 当发生哈希冲突时，最坏达到O(n *n)

                                                                                                                                                                                                                     代码如下：
#define ll long long
    class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> ump;
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++)
        {
            int x = target - nums[i]; // 另外一个可能值
            if (ump.count(x))
            {
                return {i, ump[x]};
            }
            ump[nums[i]] = i; // 查找之后，存入每个数对于的下标
        }
        return {};
    }
};