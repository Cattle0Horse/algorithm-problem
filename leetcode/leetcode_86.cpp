/**
 * @file leetcode_86.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/partition-list/
 * @version 0.1
 * @date 2024-07-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef OY_LOCAL
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* dummy = new ListNode(-1, head);
        auto last_less = dummy;
        ListNode* last_greater_eq = nullptr;
        ListNode* first_greater_eq = nullptr;
        for (auto cur = head; cur != nullptr; cur = cur->next) {
            if (cur->val < x) {
                last_less->next = cur;
                last_less = last_less->next;
                if (dummy == head) {
                    dummy->next = last_less;
                }
            } else {
                if (last_greater_eq == nullptr) {
                    last_greater_eq = cur;
                } else {
                    last_greater_eq->next = cur;
                    last_greater_eq = last_greater_eq->next;
                }
                if (first_greater_eq == nullptr) {
                    first_greater_eq = cur;
                }
            }
        }
        if (last_greater_eq != nullptr) {
            last_greater_eq->next = nullptr;
        }
        last_less->next = first_greater_eq;
        return dummy->next;
    }
};

#ifdef OY_LOCAL
int main() {
    //
}
#endif