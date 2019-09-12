#include "../include/core.h"

class Solution_0027 {
public:
    // 解法一：使用循环
    // 时间复杂度为：O(n)
    // 空间复杂度为：O(1)
    int removeElement1(vector<int>& nums, int val) {
        for (int i = 0; i < nums.size(); ) {
            if (nums[i] == val) {
                nums.erase(nums.begin() + i);
                continue;
            }
            ++i;
        }

        return nums.size();
    }

    // 解法二：使用迭代器
    // 时间复杂度为：O(n)
    // 空间复杂度为：O(1)    
    int removeElement(vector<int>& nums, int val) {
        for (auto iter = nums.begin(); iter != nums.end(); ) {
            if (*iter == val) {
                nums.erase(iter);
            } else {
                ++iter;
            }
        }

        return nums.size();
    }

};