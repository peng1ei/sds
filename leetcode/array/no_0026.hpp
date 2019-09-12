#include "../include/core.h"

class Solution_0026 {
public:
    // 解法一：双指针，快慢指针（迭代器版本）
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    int removeDuplicates1(vector<int>& nums) {
        if (nums.empty()) {
            return nums.size();
        }

        auto first = nums.begin();
        auto last = nums.begin() + 1;
        while (last != nums.end()) {
            if (*first == *last) {
                ++last;
            } else {
                *(++first) = *(last++);                
            }
        }   

        nums.erase(first+1, last);

        return nums.size();     
    }
    
    // 解法一：快慢指针（循环版本）
    // 时间复杂度：O(n)
    // 空间复杂度：O(1) 
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) {
            return nums.size();
        }

        int j = 0;
        for (int i = 1; i < nums.size();) {
            if (nums[j] == nums[i]) {
                ++i;
            } else {
                nums[++j] = nums[i++];
            }
        }  

        nums.erase(nums.begin() + j + 1, nums.end());

        return nums.size();     
    }
};
