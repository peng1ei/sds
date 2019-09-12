// NO.0001_两数之和
// 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
// 你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

// 示例:
// 给定 nums = [2, 7, 11, 15], target = 9
// 因为 nums[0] + nums[1] = 2 + 7 = 9
// 所以返回 [0, 1]

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/two-sum
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
#include "../include/core.h"

class Solution_0001 {
public:
    // 解法一：暴力破解法
    // 时间复杂度为  O(n^2)
    // 空间复杂度为 O(1)
    vector<int> twoSum1(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i+1; j < nums.size(); ++j) {
                if ((nums[i] + nums[j]) == target) {
                    return vector<int>({i, j});
                }
            }
        }    

        return vector<int>({-1, -1});    
    }

    // 解法二：以空间换时间（使用 map）
    // 时间复杂度：O(n)
    // 空间复杂度：O(n)
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, int> mp;

        for (int i = 0; i < nums.size(); ++i) {
            int diff = target - nums[i];
            if (mp.count(diff) == 1) {
                return std::vector<int>({mp[diff], i});
            }

            mp[nums[i]] = i;
        }

        return vector<int>({-1, -1});    
    }

    void run() {
        vector<int> vec{ 3, 2, 4};
        auto result = twoSum1(vec, 6);

        std::cout << "[" << result.front() << ", " << 
            result.back() << "]" << std::endl;
    }
};