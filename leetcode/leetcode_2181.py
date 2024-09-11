"""
https://leetcode.cn/problems/merge-nodes-in-between-zeros/description
2181. 合并零之间的节点
"""

# Definition for singly-linked list.
from typing import Optional


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def mergeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:
        tail = head = head.next
        while tail and tail.next:
            if tail.next.val == 0:
                tail.next = tail.next.next
                tail = tail.next
            else:
                tail.val += tail.next.val
                tail.next = tail.next.next
        return head
